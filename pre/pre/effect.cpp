//=============================================================================
//
// エフェクト処理 [effect.cpp]
// Author : AKIRA TANAKA
//
//=============================================================================
#include "effect.h"
#include "input.h"
#include "camera.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	TEXTURE_EFFECT			"data/TEXTURE/effect000.jpg"	// 読み込むテクスチャファイル名
#define	VALUE_MOVE_BULLET		(2.0f)							// 移動速度

#define	MAX_EFFECT				(4096)							// エフェクト最大数

//*****************************************************************************
// 構造体定義
//*****************************************************************************
typedef struct
{
	D3DXVECTOR3 pos;		// 位置
	D3DXVECTOR3 rot;		// 回転
	D3DXVECTOR3 scale;		// スケール
	D3DXVECTOR3 move;		// 移動量
	D3DXCOLOR col;			// 色
	float fSizeX;			// 幅
	float fSizeY;			// 高さ
	int Timer;				// タイマー
	float DecAlpha;		// 減衰値
	bool bUse;				// 使用しているかどうか
} EFFECT;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT MakeVertexEffect(LPDIRECT3DDEVICE9 pDevice);
void SetVertexEffect(int nIdxEffect, float fSizeX, float fSizeY);
void SetColorEffect(int nIdxEffect, D3DXCOLOR col);

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9		D3DTextureEffect = NULL;		// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 D3DVtxBuffEffect = NULL;		// 頂点バッファインターフェースへのポインタ

D3DXMATRIX				mtxWorldEffect;				// ワールドマトリックス

EFFECT					Effect[MAX_EFFECT];			// 弾ワーク

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitEffect(void)
{
	LPDIRECT3DDEVICE9 Device = GetDevice();

	// 頂点情報の作成
	MakeVertexEffect(Device);

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(Device,					// デバイスへのポインタ
								TEXTURE_EFFECT,			// ファイルの名前
								&D3DTextureEffect);	// 読み込むメモリー

	for(int CntEffect = 0; CntEffect < MAX_EFFECT; CntEffect++)
	{
		Effect[CntEffect].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		Effect[CntEffect].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		Effect[CntEffect].scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
		Effect[CntEffect].move = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
		Effect[CntEffect].fSizeX = EFFECT_SIZE_X;
		Effect[CntEffect].fSizeY = EFFECT_SIZE_Y;
		Effect[CntEffect].Timer = 0;
		Effect[CntEffect].bUse = false;
	}

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitEffect(void)
{
	if(D3DTextureEffect != NULL)
	{// テクスチャの開放
		D3DTextureEffect->Release();
		D3DTextureEffect = NULL;
	}

	if(D3DVtxBuffEffect != NULL)
	{// 頂点バッファの開放
		D3DVtxBuffEffect->Release();
		D3DVtxBuffEffect = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateEffect(void)
{
	D3DXVECTOR3 rotCamera;

	// カメラの回転を取得
	rotCamera = GetRotCamera();

	for(int CntEffect = 0; CntEffect < MAX_EFFECT; CntEffect++)
	{
		if(Effect[CntEffect].bUse)
		{
			Effect[CntEffect].pos.x += Effect[CntEffect].move.x;
			Effect[CntEffect].pos.z += Effect[CntEffect].move.z;
			Effect[CntEffect].pos.y += Effect[CntEffect].move.y;

			Effect[CntEffect].col.a -= Effect[CntEffect].DecAlpha;
			if(Effect[CntEffect].col.a <= 0.0f)
			{
				Effect[CntEffect].col.a = 0.0f;
			}
			SetColorEffect(CntEffect,
							D3DXCOLOR(Effect[CntEffect].col.r,Effect[CntEffect].col.b,
										Effect[CntEffect].col.b, Effect[CntEffect].col.a));

			Effect[CntEffect].Timer--;
			if(Effect[CntEffect].Timer <= 0)
			{
				Effect[CntEffect].bUse = false;
			}
		}
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawEffect(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxView,mtxScale,mtxTranslate;
	//pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_REVSUBTRACT);		// 結果 = 転送先(DEST) - 転送元(SRC)
	//pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	//pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
	//pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);

	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);		// αソースカラーの指定
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);			// αデスティネーションカラーの指定
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);			// Z比較なし



//	pDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);	// アルファブレンディング処理
//	pDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);	// 最初のアルファ引数
//	pDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CURRENT);	// ２番目のアルファ引数

	for(int CntEffect = 0; CntEffect < MAX_EFFECT; CntEffect++)
	{
		if(Effect[CntEffect].bUse)
		{
			// ワールドマトリックスの初期化
			D3DXMatrixIdentity(&mtxWorldEffect);

			// ビューマトリックスを取得
			mtxView = GetMtxView();

			mtxWorldEffect._11 = mtxView._11;
			mtxWorldEffect._12 = mtxView._21;
			mtxWorldEffect._13 = mtxView._31;
			mtxWorldEffect._21 = mtxView._12;
			mtxWorldEffect._22 = mtxView._22;
			mtxWorldEffect._23 = mtxView._32;
			mtxWorldEffect._31 = mtxView._13;
			mtxWorldEffect._32 = mtxView._23;
			mtxWorldEffect._33 = mtxView._33;

			// スケールを反映
			D3DXMatrixScaling(&mtxScale, Effect[CntEffect].scale.x, Effect[CntEffect].scale.y, Effect[CntEffect].scale.z);
			D3DXMatrixMultiply(&mtxWorldEffect, &mtxWorldEffect, &mtxScale);

			// 移動を反映
			D3DXMatrixTranslation(&mtxTranslate, Effect[CntEffect].pos.x, Effect[CntEffect].pos.y, Effect[CntEffect].pos.z);
			D3DXMatrixMultiply(&mtxWorldEffect, &mtxWorldEffect, &mtxTranslate);

			// ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &mtxWorldEffect);

			pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

			// 頂点バッファをデバイスのデータストリームにバインド
			pDevice->SetStreamSource(0, D3DVtxBuffEffect, 0, sizeof(VERTEX_3D));

			// 頂点フォーマットの設定
			pDevice->SetFVF(FVF_VERTEX_3D);

			// テクスチャの設定
			pDevice->SetTexture(0, D3DTextureEffect);

			// ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, (CntEffect * 4), NUM_POLYGON);

			pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
		}
	}

	//pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);				// 結果 = 転送元(SRC) + 転送先(DEST)
	//pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	//pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	//pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);		// αソースカラーの指定
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);	// αデスティネーションカラーの指定
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);				// Z比較あり

//	pDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_SELECTARG1);
//	pDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
//	pDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CURRENT);
}

//=============================================================================
// 頂点情報の作成
//=============================================================================
HRESULT MakeVertexEffect(LPDIRECT3DDEVICE9 pDevice)
{
	// オブジェクトの頂点バッファを生成
    if( FAILED( pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * NUM_VERTEX * MAX_EFFECT,	// 頂点データ用に確保するバッファサイズ(バイト単位)
												D3DUSAGE_WRITEONLY,							// 頂点バッファの使用法　
												FVF_VERTEX_3D,								// 使用する頂点フォーマット
												D3DPOOL_MANAGED,							// リソースのバッファを保持するメモリクラスを指定
												&D3DVtxBuffEffect,						// 頂点バッファインターフェースへのポインタ
												NULL)))										// NULLに設定
	{
        return E_FAIL;
	}

	{//頂点バッファの中身を埋める
		VERTEX_3D *pVtx;

		// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
		D3DVtxBuffEffect->Lock(0, 0, (void**)&pVtx, 0);

		for(int CntEffect = 0; CntEffect < MAX_EFFECT; CntEffect++, pVtx += 4)
		{
			// 頂点座標の設定
			pVtx[0].vtx = D3DXVECTOR3(-EFFECT_SIZE_X / 2, -EFFECT_SIZE_Y / 2, 0.0f);
			pVtx[1].vtx = D3DXVECTOR3(EFFECT_SIZE_X / 2, -EFFECT_SIZE_Y / 2, 0.0f);
			pVtx[2].vtx = D3DXVECTOR3(-EFFECT_SIZE_X / 2, EFFECT_SIZE_Y / 2, 0.0f);
			pVtx[3].vtx = D3DXVECTOR3(EFFECT_SIZE_X / 2, EFFECT_SIZE_Y / 2, 0.0f);

			// 法線の設定
			pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
			pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
			pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
			pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

			// 反射光の設定
			pVtx[0].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[1].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[2].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[3].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			// テクスチャ座標の設定
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
		}

		// 頂点データをアンロックする
		D3DVtxBuffEffect->Unlock();
	}

	return S_OK;
}

//=============================================================================
// 頂点座標の設定
//=============================================================================
void SetVertexEffect(int nIdxEffect, float fSizeX, float fSizeY)
{
	{//頂点バッファの中身を埋める
		VERTEX_3D *pVtx;

		// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
		D3DVtxBuffEffect->Lock(0, 0, (void**)&pVtx, 0);

		pVtx += (nIdxEffect * 4);

		// 頂点座標の設定
		pVtx[0].vtx = D3DXVECTOR3(-fSizeX / 2, -fSizeY / 2, 0.0f);
		pVtx[1].vtx = D3DXVECTOR3(-fSizeX / 2, fSizeY / 2, 0.0f);
		pVtx[2].vtx = D3DXVECTOR3(fSizeX / 2, -fSizeY / 2, 0.0f);
		pVtx[3].vtx = D3DXVECTOR3(fSizeX / 2, fSizeY / 2, 0.0f);

		// 頂点データをアンロックする
		D3DVtxBuffEffect->Unlock();
	}
}

//=============================================================================
// 頂点カラーの設定
//=============================================================================
void SetColorEffect(int nIdxEffect, D3DXCOLOR col)
{
	{//頂点バッファの中身を埋める
		VERTEX_3D *pVtx;

		// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
		D3DVtxBuffEffect->Lock(0, 0, (void**)&pVtx, 0);

		pVtx += (nIdxEffect * 4);

		// 頂点座標の設定
		pVtx[0].diffuse =
		pVtx[1].diffuse =
		pVtx[2].diffuse =
		pVtx[3].diffuse = col;

		// 頂点データをアンロックする
		D3DVtxBuffEffect->Unlock();
	}
}
//=============================================================================
// エフェクトの設定
//=============================================================================
int SetEffect(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXCOLOR col, float fSizeX, float fSizeY, int nTimer)
{
	int nIdxEffect = -1;

	for(int CntEffect = 0; CntEffect < MAX_EFFECT; CntEffect++)
	{
		if(!Effect[CntEffect].bUse)
		{
			Effect[CntEffect].pos = pos;
			Effect[CntEffect].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			Effect[CntEffect].scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
			Effect[CntEffect].move = move;
			Effect[CntEffect].col = col;
			Effect[CntEffect].fSizeX = fSizeX;
			Effect[CntEffect].fSizeY = fSizeY;
			Effect[CntEffect].Timer = nTimer;
			Effect[CntEffect].DecAlpha = col.a / nTimer;
			Effect[CntEffect].bUse = true;

			// 頂点座標の設定
			SetVertexEffect(CntEffect, fSizeX, fSizeY);

			// 頂点カラーの設定
			SetColorEffect(CntEffect,
							D3DXCOLOR(Effect[CntEffect].col.r,Effect[CntEffect].col.b,
										Effect[CntEffect].col.b, Effect[CntEffect].col.a));

			nIdxEffect = CntEffect;

			break;
		}
	}

	return nIdxEffect;
}
