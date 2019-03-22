//=============================================================================
//
// エネミー処理 [enemy.cpp]
// Author :	 権頭 啓太
//
//=============================================================================
#include "enemy.h"
#include "player.h"
#include "camera.h"
#include "meshfield.h"
#include "meshwall.h"
#include "particle.h"
#include "physics.h"
#include "input.h"
#include "shadow.h"
#include "sound.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	ENEMY_MODEL		"data/ENEMY/enemy_bar.x"							// 読み込むモデル名

#define	VIEW_ANGLE		(D3DXToRadian(45.0f))							// ビュー平面の視野角
#define	VIEW_ASPECT		((float)SCREEN_WIDTH / (float)SCREEN_HEIGHT)	// ビュー平面のアスペクト比	
#define	ENEMY_MOVE		(3.0f)											// 移動量
#define	ENEMY_ROTATE	(D3DX_PI * 0.02f)								// 回転量
#define ENEMY_LOST_Y	(-200.0f)

#define ENEMY_LABEL	"Enemy"
//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void EnemyHoming(void);
void EnemySanten(void);
void EnemyQuaternion(void);
void EnemyBlow(void);


//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9	pD3DTextureEnemy;		// テクスチャへのポインタ
LPD3DXMESH			pD3DXMeshEnemy;		// メッシュ情報へのポインタ
LPD3DXBUFFER		pD3DXBuffMatEnemy;	// マテリアル情報へのポインタ
DWORD				nNumMatEnemy;			// マテリアル情報の数



ENEMY				enemy[ENEMY_MAX];


D3DXMATRIX			enemy_mtxWorld;				// ワールドマトリックス
D3DXMATRIX			mtxWorld_body;

static LPDIRECTSOUNDBUFFER8		g_pSE;						// SE用バッファ


//D3DLIGHT9			aLight[NUM_LIGHT];	// ライト情報

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitEnemy(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	ENEMY *enemy = GetEnemy(0);

	for (int i = 0; i < ENEMY_MAX; i++, enemy++)
	{
		int j = rand() % 800;
		if (j % 2 == 0)
		{
			j = j * (-1);
		}
		// 位置・回転・スケールの初期設定
		enemy->posEnemy = D3DXVECTOR3((float)j, 200.0f, 1.5f*(i));
		enemy->rotEnemy = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		enemy->sclEnemy = D3DXVECTOR3(1.0f, 1.0f,1.0f);


		enemy->moveEnemy = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		enemy->oldEnemy = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		enemy->rotEnemy = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		enemy->rotDestEnemy = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		enemy->Dest = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

		D3DXQuaternionIdentity(&enemy->Quaternion);

		enemy->bUse = true;
		enemy->blown = false;


		pD3DTextureEnemy = NULL;
		pD3DXMeshEnemy = NULL;
		pD3DXBuffMatEnemy = NULL;
		nNumMatEnemy = 0;




	}

	// Xファイルの読み込み
	if (FAILED(D3DXLoadMeshFromX(ENEMY_MODEL,				// 読み込むモデルファイル名(Xファイル)
		D3DXMESH_SYSTEMMEM,		// メッシュの作成オプションを指定
		pDevice,				// IDirect3DDevice9インターフェイスへのポインタ
		NULL,					// 隣接性データを含むバッファへのポインタ
		&pD3DXBuffMatEnemy,	// マテリアルデータを含むバッファへのポインタ
		NULL,					// エフェクトインスタンスの配列を含むバッファへのポインタ
		&nNumMatEnemy,		// D3DXMATERIAL構造体の数
		&pD3DXMeshEnemy)))	// ID3DXMeshインターフェイスへのポインタのアドレス

	{
		return E_FAIL;
	}
	//　音関係

	g_pSE = LoadSound(SE_HIT);



#if 0
	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,					// デバイスへのポインタ
		TEXTURE_FILENAME,		// ファイルの名前
		&pD3DTextureEnemy);	// 読み込むメモリー
#endif

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
	void UninitEnemy(void)
	{
		if (pD3DTextureEnemy != NULL)
		{// テクスチャの開放
			pD3DTextureEnemy->Release();
			pD3DTextureEnemy = NULL;
		}

		if (pD3DXMeshEnemy != NULL)
		{// メッシュの開放
			pD3DXMeshEnemy->Release();
			pD3DXMeshEnemy = NULL;
		}

		if (pD3DXBuffMatEnemy != NULL)
		{// マテリアルの開放
			pD3DXBuffMatEnemy->Release();
			pD3DXBuffMatEnemy = NULL;
		}
		if (g_pSE != NULL)
		{	// テクスチャの開放
			g_pSE->Release();
			g_pSE = NULL;
		}

	}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateEnemy(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	PLAYER *player = GetPlayer();
	ENEMY *enemy = GetEnemy(0);
	D3DXVECTOR3 move(0.0f, 0.0f, 0.0f);
	
	//ホーミング
	EnemyHoming();
	//三転測量
	EnemySanten();
	//クォータニオン
	EnemyQuaternion();
	//吹き飛び
	EnemyBlow();



}

void EnemyHoming()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	PLAYER *player = GetPlayer();
	ENEMY *enemy = GetEnemy(0);
	D3DXVECTOR3 move(0.0f, 0.0f, 0.0f);

	for (int i = 0; i < ENEMY_MAX; i++, enemy++)
	{
		int rand_rot;
		rand_rot = rand() % 360;
		if ((enemy->blown == false) && (enemy->bUse == true))
		{
			//homing
			if (rand_rot % 7 == 0)
			{
				homing(enemy);
			}
			enemy->posEnemy.x += enemy->moveEnemy.x;
			enemy->posEnemy.z += enemy->moveEnemy.z;
		}
	}
}

void EnemySanten(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	PLAYER *player = GetPlayer();
	ENEMY *enemy = GetEnemy(0);
	D3DXVECTOR3 move(0.0f, 0.0f, 0.0f);

	for (int i = 0; i < ENEMY_MAX; i++, enemy++)
	{

		int rand_rot;
		rand_rot = rand() % 360;
		if ((enemy->blown == false) && (enemy->bUse == true))
		{

			//三点測量
			FLOAT height = Hitfield_Enemy(enemy);
			enemy->posEnemy.y = height;
		}
	}
}

void EnemyQuaternion(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	PLAYER *player = GetPlayer();
	ENEMY *enemy = GetEnemy(0);
	D3DXVECTOR3 move(0.0f, 0.0f, 0.0f);

	for (int i = 0; i < ENEMY_MAX; i++, enemy++)
	{

		int rand_rot;
		rand_rot = rand() % 360;
		if ((enemy->blown == false) && (enemy->bUse == true))
		{
			/************************************************************************************
			**　姿勢制御
			*************************************************************************************/
			if (enemy->ground == true)
			{

				D3DXVECTOR3 vx, nvx;
				D3DXQUATERNION quat;
				float len, angle;

				D3DXVec3Cross(&vx, &D3DXVECTOR3(0.0f, 1.0f, 0.0f), &enemy->Dest);

				len = D3DXVec3Length(&vx);
				D3DXVec3Normalize(&nvx, &vx);

				angle = asinf(len);

				D3DXQuaternionIdentity(&quat);
				D3DXQuaternionRotationAxis(&quat, &nvx, angle);
				D3DXQuaternionSlerp(&enemy->Quaternion, &enemy->Quaternion, &quat, 0.05f);
			}

		}
	}
}

void EnemyBlow(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	PLAYER *player = GetPlayer();
	ENEMY *enemy = GetEnemy(0);
	D3DXVECTOR3 move(0.0f, 0.0f, 0.0f);

	for (int i = 0; i < ENEMY_MAX; i++, enemy++)
	{
		int rand_rot;
		rand_rot = rand() % 360;
		//blow
		if ((enemy->blown == true) && (enemy->bUse == true))
		{		
			Gravity(enemy);
			enemy->moveEnemy.y += 2.0f;

			enemy->posEnemy.x += enemy->moveEnemy.x;
			enemy->posEnemy.y += enemy->moveEnemy.y;
			enemy->posEnemy.z += enemy->moveEnemy.z;

			enemy->rotEnemy.x += rand_rot;
			enemy->rotEnemy.y += rand_rot;
			enemy->rotEnemy.z += rand_rot;


			D3DXVECTOR3		vec = enemy->moveEnemy - enemy->oldEnemy;
			float			len = D3DXVec3Length(&vec);
			if (len > 0.1f)
			{	// ビルボードとの当たり判定

				if (hitCheckWall(enemy->posEnemy, enemy->oldEnemy) != 0)
				{
					// 当たっているので元の位置に戻す
					enemy->blown = false;
					enemy->bUse = false;
				}
			}
		}
		if (enemy->posEnemy.y < ENEMY_LOST_Y)
		{
			enemy->blown = false;
			enemy->bUse = false;
			PlaySound(g_pSE, E_DS8_FLAG_NONE);

		}

	}
}


//=============================================================================
// 描画処理
//=============================================================================
void DrawEnemy(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxScl, mtxRot, mtxTranslate ,quatMatrixs, shadowMatrix;
	D3DXMATERIAL *pD3DXMat;
	D3DMATERIAL9 matDef;
	ENEMY *enemy = GetEnemy(0);

	for (int i = 0; i < ENEMY_MAX; i++, enemy++)
	{
		if (enemy->bUse)
		{
			// ワールドマトリックスの初期化
			D3DXMatrixIdentity(&enemy_mtxWorld);

			// スケールを反映
			D3DXMatrixScaling(&mtxScl, enemy->sclEnemy.x, enemy->sclEnemy.y, enemy->sclEnemy.z);
			D3DXMatrixMultiply(&enemy_mtxWorld, &enemy_mtxWorld, &mtxScl);

			// 回転を反映
			D3DXMatrixRotationYawPitchRoll(&mtxRot, enemy->rotEnemy.y, enemy->rotEnemy.x, enemy->rotEnemy.z);
			D3DXMatrixMultiply(&enemy_mtxWorld, &enemy_mtxWorld, &mtxRot);

			//クォータニオン→マトリクス
			D3DXMatrixRotationQuaternion(&quatMatrixs, &enemy->Quaternion);
			D3DXMatrixMultiply(&enemy_mtxWorld, &enemy_mtxWorld, &quatMatrixs);

			// 移動を反映
			D3DXMatrixTranslation(&mtxTranslate, enemy->posEnemy.x, enemy->posEnemy.y, enemy->posEnemy.z);
			D3DXMatrixMultiply(&enemy_mtxWorld, &enemy_mtxWorld, &mtxTranslate);



			// ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &enemy_mtxWorld);

			// 現在のマテリアルを取得
			pDevice->GetMaterial(&matDef);

			// マテリアル情報に対するポインタを取得
			pD3DXMat = (D3DXMATERIAL*)pD3DXBuffMatEnemy->GetBufferPointer();

			for (int nCntMat = 0; nCntMat < (int)nNumMatEnemy; nCntMat++)
			{
				// マテリアルの設定
				pDevice->SetMaterial(&pD3DXMat[nCntMat].MatD3D);

				// テクスチャの設定
				pDevice->SetTexture(0, pD3DTextureEnemy);

				// 描画
				pD3DXMeshEnemy->DrawSubset(nCntMat);
			}

			//mtxWorld_body = enemy_mtxWorld;

			//DrawEnemy_Head();

			// マテリアルをデフォルトに戻す
			pDevice->SetMaterial(&matDef);
		}
	}
}


/**********************************************************************************
** GetEnemy
***********************************************************************************/
ENEMY	*GetEnemy(int pno)
{
	return &enemy[pno];
}

//=============================================================================
// 位置取得
//=============================================================================
D3DXVECTOR3 GetPositionModel(void)
{
	return enemy->posEnemy;
}

//=============================================================================
// 向き取得
//=============================================================================
D3DXVECTOR3 GetRotationModel(void)
{
	return enemy->rotEnemy;
}

//=============================================================================
// 目的の向き取得
//=============================================================================
D3DXVECTOR3 GetRotationDestModel(void)
{
	return enemy->rotDestEnemy;
}


/*********************************************************************************
**ホーミング
************************************************************************************/
void homing(ENEMY *enemy)
{
	D3DXVECTOR3 gap,pos;
	float dot;
	D3DXVECTOR3 cross;

	pos=GetPositionPlayer();

	gap = (pos - enemy->posEnemy);
	D3DXVec3Normalize(&gap, &gap);
	//内積
	dot = (enemy->posEnemy.x * pos.x) + (enemy->posEnemy.y *pos.y) + (enemy->posEnemy.z * pos.z);
	dot = acosf(dot);

	//外積
	cross.x = (enemy->posEnemy.y * pos.z) - (enemy->posEnemy.z * pos.y);
	cross.y = (enemy->posEnemy.z * pos.x) - (enemy->posEnemy.x - pos.z);
	cross.z = (enemy->posEnemy.x * pos.y) - (enemy->posEnemy.y - pos.x);


	if (cross < 0)
	{
		cross = -cross;
	}

	enemy->rotDestEnemy = gap;



	enemy->moveEnemy = gap * ENEMY_MOVE;




}

//*******************************************************************************
//**
//*******************************************************************************
D3DXMATRIX *GeEnemytMatrix(void)
{
	return &mtxWorld_body;
}

/******************************************************************************
**
******************************************************************************/
void DeleteEnemy(int nIdxEnemy)
{
	if (nIdxEnemy >= 0 && nIdxEnemy < ENEMY_MAX)
	{
		enemy[nIdxEnemy].blown = true;
	}
}


