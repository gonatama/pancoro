//=============================================================================
//
// メッシュ地面の処理 [meshfield.cpp]
// Author : 権頭　啓太
//
//=============================================================================
#include "meshfield.h"
#include "input.h"
#include "player.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	LOOP_MAX		(10000)		// フラクタルの演算数

#define FIELD_DIFFERENCE		(1.5)
//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9 D3DTextureField;			// テクスチャ読み込み場所
LPDIRECT3DVERTEXBUFFER9 D3DVtxBuffField;		// 頂点バッファインターフェースへのポインタ
LPDIRECT3DINDEXBUFFER9 D3DIdxBuffField;		// インデックスバッファインターフェースへのポインタ

D3DXMATRIX mtxWorldField;						// ワールドマトリックス
D3DXVECTOR3 posField;							// ポリゴン表示位置の中心座標
D3DXVECTOR3 rotField;							// ポリゴンの回転角

int NumBlockXField, NumBlockZField;		// ブロック数
int NumVertexField;							// 総頂点数	
int NumVertexIndexField;						// 総インデックス数
int NumPolygonField;							// 総ポリゴン数
int count=0;
float BlockSizeXField, BlockSizeZField;	// ブロックサイズ
float Xrand, Zrand, Rrand;
float valField;
float xMax, zMax, rMax;

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitMeshField(D3DXVECTOR3 pos, D3DXVECTOR3 rot,
	int nNumBlockX, int nNumBlockZ, float fBlockSizeX, float fBlockSizeZ)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	xMax = (fBlockSizeX * nNumBlockX) / 2;
	zMax = (fBlockSizeX * nNumBlockX) / 2;
	rMax = 100;

	valField = (fBlockSizeX * nNumBlockX);

	// ポリゴン表示位置の中心座標を設定
	posField = pos;

	rotField = rot;

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,					// デバイスへのポインタ
		TEXTURE_FIELD,		// ファイルの名前
		&D3DTextureField);	// 読み込むメモリー

// ブロック数の設定
	NumBlockXField = nNumBlockX;
	NumBlockZField = nNumBlockZ;

	// 頂点数の設定
	NumVertexField = (nNumBlockX + 1) * (nNumBlockZ + 1);

	// インデックス数の設定
	NumVertexIndexField = (nNumBlockX + 1) * 2 * nNumBlockZ + (nNumBlockZ - 1) * 2;

	// ポリゴン数の設定
	NumPolygonField = nNumBlockX * nNumBlockZ * 2 + (nNumBlockZ - 1) * 4;

	// ブロックサイズの設定
	BlockSizeXField = fBlockSizeX;
	BlockSizeZField = fBlockSizeZ;

	// オブジェクトの頂点バッファを生成
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * NumVertexField,	// 頂点データ用に確保するバッファサイズ(バイト単位)
		D3DUSAGE_WRITEONLY,					// 頂点バッファの使用法　
		FVF_VERTEX_3D,						// 使用する頂点フォーマット
		D3DPOOL_MANAGED,					// リソースのバッファを保持するメモリクラスを指定
		&D3DVtxBuffField,				// 頂点バッファインターフェースへのポインタ
		NULL)))								// NULLに設定
	{
		return E_FAIL;
	}

	// オブジェクトのインデックスバッファを生成
	if (FAILED(pDevice->CreateIndexBuffer(sizeof(WORD) * NumVertexIndexField,		// 頂点データ用に確保するバッファサイズ(バイト単位)
		D3DUSAGE_WRITEONLY,					// 頂点バッファの使用法　
		D3DFMT_INDEX16,						// 使用するインデックスフォーマット
		D3DPOOL_MANAGED,					// リソースのバッファを保持するメモリクラスを指定
		&D3DIdxBuffField,				// インデックスバッファインターフェースへのポインタ
		NULL)))								// NULLに設定
	{
		return E_FAIL;
	}

	{//頂点バッファの中身を埋める
		VERTEX_3D *pVtx;
#if 0
		const float texSizeX = 1.0f / NumBlockX;
		const float texSizeZ = 1.0f / NumBlockZ;
#else
		const float texSizeX = 1.0f;
		const float texSizeZ = 1.0f;
#endif

		// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
		D3DVtxBuffField->Lock(0, 0, (void**)&pVtx, 0);

		for (int CntVtxZ = 0; CntVtxZ < (NumBlockZField + 1); CntVtxZ++)
		{
			for (int CntVtxX = 0; CntVtxX < (NumBlockXField + 1); CntVtxX++)
			{
				// 頂点座標の設定
				pVtx[CntVtxZ * (NumBlockXField + 1) + CntVtxX].vtx.x = -(NumBlockXField / 2.0f) * BlockSizeXField + CntVtxX * BlockSizeXField;
				pVtx[CntVtxZ * (NumBlockXField + 1) + CntVtxX].vtx.y = 0.0f;// rand() % ;
				pVtx[CntVtxZ * (NumBlockXField + 1) + CntVtxX].vtx.z = (NumBlockZField / 2.0f) * BlockSizeZField - CntVtxZ * BlockSizeZField;

				// 法線の設定
				pVtx[CntVtxZ * (NumBlockXField + 1) + CntVtxX].nor = D3DXVECTOR3(0.0f, 1.0, 0.0f);

				// 反射光の設定
				pVtx[CntVtxZ * (NumBlockXField + 1) + CntVtxX].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

				// テクスチャ座標の設定
				pVtx[CntVtxZ * (NumBlockXField + 1) + CntVtxX].tex.x = texSizeX * CntVtxX;
				pVtx[CntVtxZ * (NumBlockXField + 1) + CntVtxX].tex.y = texSizeZ * CntVtxZ;
			}
		}

		// 頂点データをアンロックする
		D3DVtxBuffField->Unlock();
	}

	{//インデックスバッファの中身を埋める
		WORD *Idx;

		// インデックスデータの範囲をロックし、頂点バッファへのポインタを取得
		D3DIdxBuffField->Lock(0, 0, (void**)&Idx, 0);

		int CntIdx = 0;
		for (int CntVtxZ = 0; CntVtxZ < NumBlockZField; CntVtxZ++)
		{
			if (CntVtxZ > 0)
			{// 縮退ポリゴンのためのダブりの設定
				Idx[CntIdx] = (CntVtxZ + 1) * (NumBlockXField + 1);
				CntIdx++;
			}

			for (int nCntVtxX = 0; nCntVtxX < (NumBlockXField + 1); nCntVtxX++)
			{
				Idx[CntIdx] = (CntVtxZ + 1) * (NumBlockXField + 1) + nCntVtxX;
				CntIdx++;
				Idx[CntIdx] = CntVtxZ * (NumBlockXField + 1) + nCntVtxX;
				CntIdx++;
			}

			if (CntVtxZ < (NumBlockZField - 1))
			{// 縮退ポリゴンのためのダブりの設定
				Idx[CntIdx] = CntVtxZ * (NumBlockXField + 1) + NumBlockXField;
				CntIdx++;
			}
		}

		// インデックスデータをアンロックする
		D3DIdxBuffField->Unlock();
	}

	for (int i = 0; i < LOOP_MAX; i++)
	{



		Xrand = (float)(rand() % (int)(valField)) - xMax;
		Zrand = (float)(rand() % (int)(valField)) - zMax;
		Rrand = (float)(rand() % 200 * (D3DX_PI)) / 10.0f;

		D3DXVECTOR3 vecRand, vecMesh, cross;
		D3DXVECTOR3 tmp;
		VERTEX_3D	*Vtx;
		D3DVtxBuffField->Lock(0, 0, (void**)&Vtx, 0);


		vecRand.x = cosf(Rrand);
		vecRand.z = sinf(Rrand);
		vecRand.y = 0.0f;

		for (int z = 0; z < (NumBlockZField + 1); z++)
		{
			for (int x = 0; x < (NumBlockXField + 1); x++)
			{
				tmp.x = Vtx[z*(NumBlockXField + 1) + x].vtx.x;
				tmp.z = Vtx[z*(NumBlockXField + 1) + x].vtx.z;

				vecMesh.x = tmp.x - Xrand;
				vecMesh.z = tmp.z - Zrand;
				vecMesh.y = 0.0f;

				D3DXVec3Cross(&cross, &vecRand, &vecMesh);

				if (cross.y > 0.0f)
				{
					Vtx[z*(NumBlockXField + 1) + x].vtx.y += FIELD_DIFFERENCE;
				}
				else
				{
					Vtx[z*(NumBlockXField + 1) + x].vtx.y -= FIELD_DIFFERENCE;

				}

			}

		}

		D3DIdxBuffField->Unlock();

		//}
	}

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitMeshField(void)
{
	if (D3DVtxBuffField)
	{// 頂点バッファの開放
		D3DVtxBuffField->Release();
		D3DVtxBuffField = NULL;
	}

	if (D3DIdxBuffField)
	{// インデックスバッファの開放
		D3DIdxBuffField->Release();
		D3DIdxBuffField = NULL;
	}

	if (D3DTextureField)
	{// テクスチャの開放
		D3DTextureField->Release();
		D3DTextureField = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateMeshField(void)
{


}

//=============================================================================
// 描画処理
//=============================================================================
void DrawMeshField(void)
{
	LPDIRECT3DDEVICE9 Device = GetDevice();

	D3DXMATRIX mtxRot, mtxTranslate;

	// ワールドマトリックスの初期化
	D3DXMatrixIdentity(&mtxWorldField);

	// 回転を反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, rotField.y, rotField.x, rotField.z);
	D3DXMatrixMultiply(&mtxWorldField, &mtxWorldField, &mtxRot);

	// 移動を反映
	D3DXMatrixTranslation(&mtxTranslate, posField.x, posField.y, posField.z);
	D3DXMatrixMultiply(&mtxWorldField, &mtxWorldField, &mtxTranslate);

	// ワールドマトリックスの設定
	Device->SetTransform(D3DTS_WORLD, &mtxWorldField);

	// 頂点バッファをレンダリングパイプラインに設定
	Device->SetStreamSource(0, D3DVtxBuffField, 0, sizeof(VERTEX_3D));

	// インデックスバッファをレンダリングパイプラインに設定
	Device->SetIndices(D3DIdxBuffField);

	// 頂点フォーマットの設定
	Device->SetFVF(FVF_VERTEX_3D);

	// テクスチャの設定
	Device->SetTexture(0, D3DTextureField);

	// ポリゴンの描画
	Device->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, NumVertexField, 0, NumPolygonField);
}

/*************************************************************************
*三点測量
**************************************************************************/
FLOAT Hitfield(D3DXVECTOR3 pos)
{
	//頂点バッファの中身を埋める
	VERTEX_3D *pVtx;
	PLAYER *player = GetPlayer();
	D3DXVECTOR3 cross;
	D3DXVECTOR3 vec1, vec2, vec3;
	float pos_high, fx, fz;


	fx = (float)(NumBlockXField / 2.0 + (pos.x / BlockSizeXField));
	fz = (float)(NumBlockZField / 2.0 - (pos.z / BlockSizeZField));

	int x = (int)floorf(fx);
	int z = (int)floorf(fz);

	int vtx0, vtx1, vtx2, vtx3;

	vtx0 = z * (NumBlockXField + 1) + x;
	vtx1 = vtx0 + 1;
	vtx2 = vtx1 + NumBlockXField;
	vtx3 = vtx2 + 1;


	//頂点データの範囲をロックし、頂点バッファへのポインタを取得
	D3DVtxBuffField->Lock(0, 0, (void**)&pVtx, 0);


	if (fx - x > fz - z)
	{

		vec1 = pVtx[vtx1].vtx - pVtx[vtx0].vtx;
		vec2 = pVtx[vtx3].vtx - pVtx[vtx0].vtx;

		D3DXVec3Cross(&cross, &vec1, &vec2);
	}
	else
	{
		vec1 = pVtx[vtx3].vtx - pVtx[vtx0].vtx;
		vec2 = pVtx[vtx2].vtx - pVtx[vtx0].vtx;

		D3DXVec3Cross(&cross, &vec1, &vec2);

	}

	pos_high = pVtx[vtx0].vtx.y - (cross.x*(pos.x - pVtx[vtx0].vtx.x) + cross.z*(pos.z - pVtx[vtx0].vtx.z)) / cross.y;

	
	D3DXVec3Normalize(&vec3,&cross);
	player->Dest = vec3;
	pos_high += PLAYER_SIZE_Y;


	// 頂点データをアンロックする
	D3DVtxBuffField->Unlock();

	return (pos_high);

}

/*************************************************************************
*三点測量 *ENEMY
**************************************************************************/
FLOAT Hitfield_Enemy(ENEMY *enemy)
{
	//頂点バッファの中身を埋める
	VERTEX_3D *pVtx;
	D3DXVECTOR3 cross;
	D3DXVECTOR3 vec1, vec2,vec3;
	float pos_high, fx, fz;


	fx = (float)(NumBlockXField / 2.0 + (enemy->posEnemy.x / BlockSizeXField));
	fz = (float)(NumBlockZField / 2.0 - (enemy->posEnemy.z / BlockSizeZField));

	int x = (int)floorf(fx);
	int z = (int)floorf(fz);

	int vtx0, vtx1, vtx2, vtx3;

	vtx0 = z * (NumBlockXField + 1) + x;
	vtx1 = vtx0 + 1;
	vtx2 = vtx1 + NumBlockXField;
	vtx3 = vtx2 + 1;


	//頂点データの範囲をロックし、頂点バッファへのポインタを取得
	D3DVtxBuffField->Lock(0, 0, (void**)&pVtx, 0);


	if (fx - x > fz - z)
	{

		vec1 = pVtx[vtx1].vtx - pVtx[vtx0].vtx;
		vec2 = pVtx[vtx3].vtx - pVtx[vtx0].vtx;

		D3DXVec3Cross(&cross, &vec1, &vec2);
	}
	else
	{
		vec1 = pVtx[vtx3].vtx - pVtx[vtx0].vtx;
		vec2 = pVtx[vtx2].vtx - pVtx[vtx0].vtx;

		D3DXVec3Cross(&cross, &vec1, &vec2);

	}

	pos_high = pVtx[vtx0].vtx.y - (cross.x*(enemy->posEnemy.x - pVtx[vtx0].vtx.x) + cross.z*(enemy->posEnemy.z - pVtx[vtx0].vtx.z)) / cross.y;

	D3DXVec3Normalize(&vec3, &cross);

	enemy->Dest = vec3;

	pos_high = pos_high + ENEMY_SIZE_Y;


	// 頂点データをアンロックする
	D3DVtxBuffField->Unlock();

	return (pos_high);

}

//頂点バッファ取得処理
LPDIRECT3DVERTEXBUFFER9 GetMeshFieldVtx(void)
{
	return D3DVtxBuffField;
}


