//=============================================================================
//
// カメラ処理 [camera.cpp]
// Author : 権頭　啓太
//
//=============================================================================
#include "camera.h"
#include "player.h"
#include "input.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	VIEW_ANGLE			(D3DXToRadian(60.0f))	// 視野角
#define	VIEW_NEAR_Z			(10.0f)					// ビュー平面のNearZ値
#define	VIEW_FAR_Z			(6000.0f)				// ビュー平面のFarZ値
#define	VALUE_MOVE_CAMERA	(2.0f)					// カメラの移動量
#define	VALUE_ROTATE_CAMERA	(D3DX_PI * 0.01f)		// カメラの回転量


#define LENGTH_MAX			(600.0f)
#define LENGTH_MIN			(50.0f)

#define	INTERVAL_CAMERA_R	(40.0f)					// モデルの視線の先までの距離
#define	RATE_CHASE_CAMERA_P	(0.35f)					// カメラの視点への補正係数
#define	RATE_CHASE_CAMERA_R	(0.20f)					// カメラの注視点への補正係数

#define	CHASE_HEIGHT_P		(65.0f)					// 追跡時の視点の高さ
#define	CHASE_HEIGHT_R		(10.0f)					// 追跡時の注視点の高さ

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************


//*****************************************************************************
// グローバル変数
//*****************************************************************************
D3DXVECTOR3		g_posCameraP;				// カメラの視点
D3DXVECTOR3		g_posCameraR;				// カメラの注視点
D3DXVECTOR3		g_posCameraU;				// カメラの上方向
D3DXVECTOR3		g_posCameraPDest;			// カメラの視点の目的位置
D3DXVECTOR3		g_posCameraRDest;			// カメラの注視点の目的位置


D3DXVECTOR3		rotCamera;				// カメラの回転
float			g_fLengthIntervalCamera;	// カメラの視点と注視点の距離
float			g_fLengthIntervalPlayer;	// プレイヤーと注視点の距離
D3DXMATRIX		g_mtxView;					// ビューマトリックス
D3DXMATRIX		g_mtxProjection;			// プロジェクションマトリックス

float			stick;
//=============================================================================
// カメラの初期化
//=============================================================================
HRESULT InitCamera(void)
{


	g_posCameraP = D3DXVECTOR3(0.0f, 10.0f, -300.0f);
	g_posCameraR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_posCameraU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	g_posCameraPDest = D3DXVECTOR3(0.0f, 100.0f, -200.0f);
	g_posCameraRDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	rotCamera = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	float vx,vz;
	vx = g_posCameraP.x - g_posCameraR.x;
	vz = g_posCameraP.z - g_posCameraR.z;
	g_fLengthIntervalCamera = sqrtf(vx * vx + vz * vz);
	g_fLengthIntervalPlayer = INTERVAL_CAMERA_R;

	return S_OK;
}

//=============================================================================
// カメラの終了処理
//=============================================================================
void UninitCamera(void)
{
}

//=============================================================================
// カメラの更新処理
//=============================================================================
void UpdateCamera(void)
{
	D3DXVECTOR3 posPlayer;
	D3DXVECTOR3 rotPlayer;
	D3DXVECTOR3 movePlayer;
	float fLength;

	// モデルの位置取得
	posPlayer = GetPositionPlayer();

	// モデルの目的の向き取得
	rotPlayer = GetRotationPlayer();

	// モデルの移動量取得
	movePlayer = GetMovePlayer();


	stick=GetStickPosHeigth();
	if ((GetKeyboardPress(DIK_X)) || (stick < -0.1f))
	{
		// 接近
		g_fLengthIntervalCamera -= VALUE_MOVE_CAMERA * 2-(stick*10);
		if (g_fLengthIntervalCamera <= LENGTH_MIN)
		{
			g_fLengthIntervalCamera = LENGTH_MIN;
		}
	}
	else if ((GetKeyboardPress(DIK_C)) || (stick > 0.1f))
	{
		// 離脱
		g_fLengthIntervalCamera += VALUE_MOVE_CAMERA * 2+(stick*10);
		if (g_fLengthIntervalCamera >= LENGTH_MAX)
		{
			g_fLengthIntervalCamera = LENGTH_MAX;
		}

	}

	

		// 視点の目的位置
		fLength = sqrtf(movePlayer.x *  movePlayer.x + movePlayer.z *  movePlayer.z) * 6.0f;
		g_posCameraPDest.x = posPlayer.x - (float)sinf(rotCamera.y) *  g_fLengthIntervalCamera - (float)sin(rotPlayer.y) * fLength;
		g_posCameraPDest.y = posPlayer.y + CHASE_HEIGHT_P;
		g_posCameraPDest.z = posPlayer.z - (float)cosf(rotCamera.y) * g_fLengthIntervalCamera - (float)cos(rotPlayer.y) * fLength;

		// 注視点の目的位置
		fLength = g_fLengthIntervalPlayer + sqrtf(movePlayer.x * movePlayer.x + movePlayer.z * movePlayer.z) * 6.0f;
		g_posCameraRDest.x = posPlayer.x - (float)sin(rotPlayer.y) * fLength;
		g_posCameraRDest.y = posPlayer.y - CHASE_HEIGHT_R;
		g_posCameraRDest.z = posPlayer.z - (float)cos(rotPlayer.y) * fLength;

		// 視点の補正
		g_posCameraP.x += (g_posCameraPDest.x - g_posCameraP.x) * RATE_CHASE_CAMERA_P;
		g_posCameraP.y += (g_posCameraPDest.y - g_posCameraP.y) * RATE_CHASE_CAMERA_P;
		g_posCameraP.z += (g_posCameraPDest.z - g_posCameraP.z) * RATE_CHASE_CAMERA_P;

		// 注視点の補正
		g_posCameraR.x += (g_posCameraRDest.x - g_posCameraR.x) * RATE_CHASE_CAMERA_R;
		g_posCameraR.y += (g_posCameraRDest.y - g_posCameraR.y) * RATE_CHASE_CAMERA_R;
		g_posCameraR.z += (g_posCameraRDest.z - g_posCameraR.z) * RATE_CHASE_CAMERA_R;
	


}

//=============================================================================
// カメラの設定処理
//=============================================================================
void SetCamera(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ビューマトリックスの初期化
	D3DXMatrixIdentity(&g_mtxView);

	// ビューマトリックスの作成
	D3DXMatrixLookAtLH(&g_mtxView, 
						&g_posCameraP,		// カメラの視点
						&g_posCameraR,		// カメラの注視点
						&g_posCameraU);		// カメラの上方向

	// ビューマトリックスの設定
	pDevice->SetTransform(D3DTS_VIEW, &g_mtxView);


	// プロジェクションマトリックスの初期化
	D3DXMatrixIdentity(&g_mtxProjection);

	// プロジェクションマトリックスの作成
	D3DXMatrixPerspectiveFovLH(&g_mtxProjection,
								VIEW_ANGLE,										// 視野角
								((float)SCREEN_WIDTH / (float)SCREEN_HEIGHT),	// アスペクト比
								VIEW_NEAR_Z,									// ビュー平面のNearZ値
								VIEW_FAR_Z);									// ビュー平面のFarZ値

	// プロジェクションマトリックスの設定
	pDevice->SetTransform(D3DTS_PROJECTION, &g_mtxProjection);
}

//=============================================================================
// カメラの向きの取得
//=============================================================================
D3DXVECTOR3 GetRotCamera(void)
{
	return rotCamera;
}

//=============================================================================
// ビューマトリックスの取得
//=============================================================================
D3DXMATRIX GetMtxView(void)
{
	return g_mtxView;
}

