//=============================================================================
//
// ゲーム画面処理 [game.cpp]
// Author :権頭　啓太
//
//=============================================================================
#include "game.h"
#include "light.h"
#include "camera.h"
#include "meshfield.h"
#include "meshwall.h"
#include "enemy.h"
#include "player.h"
#include "physics.h"
#include "shadow.h"
#include "effect.h"
#include "particle.h"
#include "explosion.h"
#include "life.h"
#include "timer.h"
#include "score.h"
#include "sound.h"
#include "debugproc.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define GAMESCRNR_LABEL		"GameScene"

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************

//*****************************************************************************
// グローバル変数
//*****************************************************************************

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitGame(void)
{
	// ライトの初期化
	InitLight();

	// カメラの初期化
	InitCamera();

	// 地面の初期化
	InitMeshField(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), FILED_TIP_X, FILED_TIP_Z, FILED_SIZE_X, FILED_SIZE_Z);

	// 壁の初期化
	InitMeshWall(D3DXVECTOR3(0.0f, -WALL_POS_Y, WALL_POS_Z), D3DXVECTOR3(0.0f, 0.0f, 0.0f),
									D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 1, 1, WALL_X, WALL_Y);
	InitMeshWall(D3DXVECTOR3(-WALL_POS_X, -WALL_POS_Y, 0.0f), D3DXVECTOR3(0.0f, -D3DX_PI * 0.50f, 0.0f),
									D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 1, 1, WALL_X, WALL_Y);
	InitMeshWall(D3DXVECTOR3(WALL_POS_X, -WALL_POS_Y, 0.0f), D3DXVECTOR3(0.0f, D3DX_PI * 0.50f, 0.0f),
									D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 1, 1, WALL_X, WALL_Y);
	InitMeshWall(D3DXVECTOR3(0.0f, -WALL_POS_Y, WALL_POS_Z), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f),
									D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 1, 1, WALL_X, WALL_Y);

	// 壁(裏側用)
	InitMeshWall(D3DXVECTOR3(0.0f, -WALL_POS_Y, WALL_POS_Z), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f),
									D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.25f), 1, 1, WALL_X, WALL_Y);
	InitMeshWall(D3DXVECTOR3(-WALL_POS_X, -WALL_POS_Y, 0.0f), D3DXVECTOR3(0.0f, D3DX_PI * 0.50f, 0.0f),
									D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.25f), 1, 1, WALL_X, WALL_Y);
	InitMeshWall(D3DXVECTOR3(WALL_POS_X, -WALL_POS_Y, 0.0f), D3DXVECTOR3(0.0f, -D3DX_PI * 0.50f, 0.0f),
									D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.25f), 1, 1, WALL_X, WALL_Y);
	InitMeshWall(D3DXVECTOR3(0.0f, -WALL_POS_Y, -WALL_POS_Z), D3DXVECTOR3(0.0f, 0.0f, 0.0f),
									D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.25f), 1, 1, WALL_X, WALL_Y);

	// 影の初期化
	InitShadow();

	InitEnemy();
	// プレイヤーの初期化
	InitPlayer();

	InitParticle();

	// 爆発の初期化
	InitExplosion();


	// ライフの初期化
	InitLife();

	// タイマーの初期化
	InitTimer();

	ResetTimer(60);

	// スコアの初期化
	InitScore();

	InitDebugProc();


	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitGame(void)
{
	// ライトの終了処理
	UninitLight();

	// カメラの終了処理
	UninitCamera();

	// 地面の終了処理
	UninitMeshField();

	// 壁の終了処理
	UninitMeshWall();

	// 影の終了処理
	UninitShadow();

	// エネミーの終了処理
	UninitEnemy();

	// プレイヤーの終了処理
	UninitPlayer();

	//パーティクルの終了処理
	UninitParticle();

	// 爆発の終了処理
	UninitExplosion();


	// ライフの終了処理
	UninitLife();

	// タイマーの終了処理
	UninitTimer();

	// スコアの終了処理
	UninitScore();

	UninitDebugProc();
	// BGM停止
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateGame(void)
{
	// カメラ更新
	UpdateCamera();

	// 地面処理の更新
	UpdateMeshField();

	//// 壁処理の更新
	UpdateMeshWall();

	// 影処理の更新
	UpdateShadow();

	// プレイヤー処理の更新
	UpdateEnemy();


	// プレイヤー処理の更新
	UpdatePlayer();


	// パーティクルの更新処理
	UpdateParticle();

	// 爆発処理の更新
	UpdateExplosion();


	// ライフ処理の更新
	UpdateLife();

	// タイマー処理の更新
	UpdateTimer();

	// スコア処理の更新
	UpdateScore();

	UpdateDebugProc();
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawGame(void)
{
	// カメラの設定
	SetCamera();

	// 地面処理の描画
	DrawMeshField();

	// 影処理の描画
	DrawShadow();

	// エネミー処理の更新
	DrawEnemy();

	// プレイヤー処理の描画
	DrawPlayer();

	//　パーティクルの描画処理
	DrawParticle();

	//// 壁処理の描画
	DrawMeshWall();

	// 爆発処理の描画
	DrawExplosion();
	

	// ライフ処理の描画
	DrawLife();

	// タイマー処理の描画
	DrawTimer();

	// スコア処理の描画
	DrawScore();

	DrawDebugProc();

}
