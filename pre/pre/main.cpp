//=============================================================================
//
// メイン処理 [main.cpp]
// Author : 権頭　啓太
//
//=============================================================================
#include "main.h"
#include "input.h"
#include "camera.h"
#include "title.h"
#include "title_model.h"
#include "game.h"
#include "light.h"
#include "result.h"
#include "fade.h"
#include "sound.h"
#include "player.h"
#include "debugproc.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define CLASS_NAME		"AppClass"			// ウインドウのクラス名
#define WINDOW_NAME		"ぱんころ"		// ウインドウのキャプション名

//*****************************************************************************
// 構造体定義
//*****************************************************************************

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);
void Uninit(void);
void Update(void);
void Draw(void);
#ifdef _DEBUG
void DrawFPS(void);
#endif

//*****************************************************************************
// グローバル変数:
//*****************************************************************************
LPDIRECT3D9			g_pD3D = NULL;			// Direct3D オブジェクト
LPDIRECT3DDEVICE9	g_pD3DDevice = NULL;	// Deviceオブジェクト(描画に必要)
#ifdef _DEBUG
LPD3DXFONT			g_pD3DXFont = NULL;		// フォントへのポインタ
int					g_nCountFPS;			// FPSカウンタ
#endif
MODE				g_mode = MODE_TITLE;	// モード

static LPDIRECTSOUNDBUFFER8			g_pSE;						// SE用バッファ
bool	music;
//=============================================================================
// メイン関数
//=============================================================================
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);	// 無くても良いけど、警告が出る（未使用宣言）
	UNREFERENCED_PARAMETER(lpCmdLine);		// 無くても良いけど、警告が出る（未使用宣言）

	DWORD dwExecLastTime;
	DWORD dwFPSLastTime;
	DWORD dwCurrentTime;
	DWORD dwFrameCount;

	WNDCLASSEX wcex =
	{
		sizeof(WNDCLASSEX),
		CS_CLASSDC,
		WndProc,
		0,
		0,
		hInstance,
		NULL,
		LoadCursor(NULL, IDC_ARROW),
		(HBRUSH)(COLOR_WINDOW + 1),
		NULL,
		CLASS_NAME,
		NULL
	};
	HWND hWnd;
	MSG msg;
	
	// ウィンドウクラスの登録
	RegisterClassEx(&wcex);

	// ウィンドウの作成
	hWnd = CreateWindow(CLASS_NAME,
						WINDOW_NAME,
						WS_OVERLAPPEDWINDOW,
						CW_USEDEFAULT,
						CW_USEDEFAULT,
						SCREEN_WIDTH + GetSystemMetrics(SM_CXDLGFRAME) * 2,
						SCREEN_HEIGHT + GetSystemMetrics(SM_CXDLGFRAME) * 2 + GetSystemMetrics(SM_CYCAPTION),
						NULL,
						NULL,
						hInstance,
						NULL);

	// 初期化処理(ウィンドウを作成してから行う)
	if(FAILED(Init(hInstance, hWnd, true)))
	{
		return -1;
	}

	//フレームカウント初期化
	timeBeginPeriod(1);				// 分解能を設定
	dwExecLastTime = 
	dwFPSLastTime = timeGetTime();
	dwCurrentTime =
	dwFrameCount = 0;

	// ウインドウの表示(初期化処理の後に呼ばないと駄目)
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);
	
	// メッセージループ
	while(1)
	{
        if(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if(msg.message == WM_QUIT)
			{// PostQuitMessage()が呼ばれたらループ終了
				break;
			}
			else
			{
				// メッセージの翻訳とディスパッチ
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
        }
		else
		{
			dwCurrentTime = timeGetTime();
			if((dwCurrentTime - dwFPSLastTime) >= 500)	// 0.5秒ごとに実行
			{
#ifdef _DEBUG
				g_nCountFPS = dwFrameCount * 1000 / (dwCurrentTime - dwFPSLastTime);
#endif
				dwFPSLastTime = dwCurrentTime;
				dwFrameCount = 0;
			}

			if((dwCurrentTime - dwExecLastTime) >= (1000 / 60))
			{
				dwExecLastTime = dwCurrentTime;

				// 更新処理
				Update();

				// 描画処理
				Draw();

				dwFrameCount++;
			}
		}
	}
	
	// ウィンドウクラスの登録を解除
	UnregisterClass(CLASS_NAME, wcex.hInstance);

	// 終了処理
	Uninit();

	timeEndPeriod(1);				// 分解能を戻す

	return (int)msg.wParam;
}

//=============================================================================
// プロシージャ
//=============================================================================
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{

	switch(uMsg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_KEYDOWN:
		switch(wParam)
		{
		case VK_ESCAPE:					// [ESC]キーが押された
			DestroyWindow(hWnd);		// ウィンドウを破棄するよう指示する
			break;
		}
		break;

	default:
		break;
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	D3DPRESENT_PARAMETERS d3dpp;
    D3DDISPLAYMODE d3ddm;

	// Direct3Dオブジェクトの作成
	g_pD3D = Direct3DCreate9(D3D_SDK_VERSION);
	if(g_pD3D == NULL)
	{
		return E_FAIL;
	}

	// 現在のディスプレイモードを取得
    if(FAILED(g_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
	{
		return E_FAIL;
	}

	// デバイスのプレゼンテーションパラメータの設定
	ZeroMemory( &d3dpp, sizeof(d3dpp) );						// ワークをゼロクリア
	d3dpp.BackBufferCount			= 1;
	d3dpp.BackBufferWidth			= SCREEN_WIDTH;				// ゲーム画面サイズ(幅)
	d3dpp.BackBufferHeight			= SCREEN_HEIGHT;			// ゲーム画面サイズ(高さ)
	d3dpp.BackBufferFormat			= d3ddm.Format;				// カラーモードの指定
	d3dpp.SwapEffect				= D3DSWAPEFFECT_DISCARD;	// 映像信号に同期してフリップする
	d3dpp.Windowed					= bWindow;					// ウィンドウモード
	d3dpp.EnableAutoDepthStencil	= TRUE;						// デプスバッファ（Ｚバッファ）とステンシルバッファを作成
	d3dpp.AutoDepthStencilFormat	= D3DFMT_D16;				// デプスバッファとして16bitを使う

	if(bWindow)
	{// ウィンドウモード
		d3dpp.FullScreen_RefreshRateInHz = 0;								// リフレッシュレート
		d3dpp.PresentationInterval       = D3DPRESENT_INTERVAL_IMMEDIATE;	// インターバル
	}
	else
	{// フルスクリーンモード
		d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;			// リフレッシュレート
		d3dpp.PresentationInterval       = D3DPRESENT_INTERVAL_DEFAULT;		// インターバル
	}

	// デバイスの生成
	// ディスプレイアダプタを表すためのデバイスを作成
	// 描画と頂点処理をハードウェアで行なう
	if(FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT, 
									D3DDEVTYPE_HAL, 
									hWnd, 
									D3DCREATE_HARDWARE_VERTEXPROCESSING, 
									&d3dpp, &g_pD3DDevice)))
	{
		// 上記の設定が失敗したら
		// 描画をハードウェアで行い、頂点処理はCPUで行なう
		if(FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT, 
										D3DDEVTYPE_HAL, 
										hWnd, 
										D3DCREATE_SOFTWARE_VERTEXPROCESSING, 
										&d3dpp, &g_pD3DDevice)))
		{
			// 上記の設定が失敗したら
			// 描画と頂点処理をCPUで行なう
			if(FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT, 
											D3DDEVTYPE_REF,
											hWnd, 
											D3DCREATE_SOFTWARE_VERTEXPROCESSING, 
											&d3dpp, &g_pD3DDevice)))
			{
				// 初期化失敗
				return E_FAIL;
			}
		}
	}

	// レンダリングステートパラメータの設定
    g_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);				// 裏面をカリング
	g_pD3DDevice->SetRenderState(D3DRS_ZENABLE, TRUE);						// Zバッファを使用
	g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);				// αブレンドを行う
	g_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);		// αソースカラーの指定
	g_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);	// αデスティネーションカラーの指定

	// サンプラーステートパラメータの設定
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);	// テクスチャアドレッシング方法(U値)を設定
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);	// テクスチャアドレッシング方法(V値)を設定
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);	// テクスチャ縮小フィルタモードを設定
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);	// テクスチャ拡大フィルタモードを設定

	// テクスチャステージステートパラメータの設定
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);		// アルファブレンディング処理
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);		// 最初のアルファ引数
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CURRENT);		// ２番目のアルファ引数

#ifdef _DEBUG
	// 情報表示用フォントを設定
	D3DXCreateFont(g_pD3DDevice, 18, 0, 0, 0, FALSE, SHIFTJIS_CHARSET,
					OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, "Terminal", &g_pD3DXFont);
#endif
	// 入力処理の初期化
	InitInput(hInstance, hWnd);

	InitCamera();

	InitLight();

	// フェードの初期化
	InitFade();

	// サウンドの初期化
	InitSound(hWnd);

	if (music == false)
	{
		g_pSE = LoadSound(BGM_00);

		music = true;

	}
	


	// 最初はタイトル画面に
	SetMode(MODE_TITLE);

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void Uninit(void)
{
#ifdef _DEBUG
	if(g_pD3DXFont != NULL)
	{// 情報表示用フォントの開放
		g_pD3DXFont->Release();
		g_pD3DXFont = NULL;
	}
#endif

	if(g_pD3DDevice != NULL)
	{// デバイスの開放
		g_pD3DDevice->Release();
		g_pD3DDevice = NULL;
	}

	if(g_pD3D != NULL)
	{// Direct3Dオブジェクトの開放
		g_pD3D->Release();
		g_pD3D = NULL;
	}
	if (g_pSE != NULL)
	{	// テクスチャの開放
		g_pSE->Release();
		g_pSE = NULL;
	}



	// フェードの終了処理
	UninitFade();

	// サウンドの終了処理
	UninitSound();

	// 入力処理の終了処理
	UninitInput();

}

//=============================================================================
// 更新処理
//=============================================================================
void Update(void)
{

	// 入力更新
	UpdateInput();

	switch(g_mode)
	{
	case MODE_TITLE:		// タイトル画面の更新
		UpdateLight();
		UpdateTitle_Model();	
		UpdateTitle();

		break;

	case MODE_GAME:			// ゲーム画面の更新
		UpdateGame();
		break;

	case MODE_RESULT:		// リザルト画面の更新
		UpdateResult();
		break;
	}

	// フェード処理の更新
	UpdateFade();
}

//=============================================================================
// 描画処理
//=============================================================================
void Draw(void)
{
	// バックバッファ＆Ｚバッファのクリア
	g_pD3DDevice->Clear(0, NULL, (D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER), D3DCOLOR_RGBA(255, 255, 255, 255), 1.0f, 0);

	// Direct3Dによる描画の開始
	if(SUCCEEDED(g_pD3DDevice->BeginScene()))
	{
		switch(g_mode)
		{
		case MODE_TITLE:		// タイトル画面の描画
			SetCamera();
			DrawTitle_Model();
			DrawTitle();
			break;

		case MODE_GAME:			// ゲーム画面の描画
			DrawGame();
			break;

		case MODE_RESULT:		// リザルト画面の描画
			DrawResult();
			break;
		}

		// フェード描画
		DrawFade();

#ifdef _DEBUG
		// デバッグ表示
		DrawFPS();
#endif


		// Direct3Dによる描画の終了
		g_pD3DDevice->EndScene();
	}

	// バックバッファとフロントバッファの入れ替え
	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}

//=============================================================================
// デバイスの取得
//=============================================================================
LPDIRECT3DDEVICE9 GetDevice(void)
{
	return g_pD3DDevice;
}

//=============================================================================
// モードの設定
//=============================================================================
void SetMode(MODE mode)
{
	g_mode = mode;

	// BGM再生
	PlaySound(g_pSE, E_DS8_FLAG_LOOP);

	switch(g_mode)
	{
	case MODE_TITLE:
		// リザルト画面の終了処理
		UninitResult();

		//SetCamera();
		InitCamera();

		InitLight();

		// タイトル画面の初期化
		InitTitle();
		InitTitle_Model();

		break;

	case MODE_GAME:
		// タイトル画面の終了処理
		UninitTitle();
		UninitTitle_Model();
		// ゲーム画面の初期化
		InitGame();

		break;

	case MODE_RESULT:
		// ゲーム画面の終了処理
		UninitGame();

		// リザルト画面の初期化
		InitResult();

		break;
	}
}

//=============================================================================
// モードの取得
//=============================================================================
MODE GetMode(void)
{
	return g_mode;
}

#ifdef _DEBUG

//=============================================================================
// デバッグ表示
//=============================================================================
void DrawFPS(void)
{
	
	RECT rect = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
	PLAYER *player = GetPlayer();
	char str[256];

	wsprintf(str, "FPS:%d\n", g_nCountFPS);

	// テキスト描画
	g_pD3DXFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));

	//wsprintf(str, _T("player->air:%s\n"), player->air ? "true" : "false");		//第一引数に(str)というバッファにg_nCountFPSを吐き出す。下３行がワンセット。													//rextのトップに+16
	//rect.top = 60;
	//g_pD3DXFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));		//画面表示

	//wsprintf(str, _T("player->drop:%s\n"), player->drop ? "true" : "false");		//第一引数に(str)というバッファにg_nCountFPSを吐き出す。下３行がワンセット。													//rextのトップに+16
	//rect.top = 80;
	//g_pD3DXFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));		//画面表示

	//wsprintf(str, _T("player->graund:%s\n"), player->ground ? "true" : "false");		//第一引数に(str)というバッファにg_nCountFPSを吐き出す。下３行がワンセット。													//rextのトップに+16
	//rect.top = 100;
	//g_pD3DXFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));		//画面表示
	
}
#endif
