//=============================================================================
//
// メッシュ地面の処理 [meshfield.h]
// Author : 権頭　啓太
//
//=============================================================================
#ifndef _MESHFIELD_H_
#define _MESHFIELD_H_

#include "main.h"
#include "enemy.h"

#define	TEXTURE_FIELD	"data/TEXTURE/wall.png"		// 読み込むテクスチャファイル名

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitMeshField(D3DXVECTOR3 pos, D3DXVECTOR3 rot,
	int NumBlockX, int NumBlockZ, float BlockSizeX, float BlockSizeZ);
void UninitMeshField(void);
void UpdateMeshField(void);
void DrawMeshField(void);


FLOAT Hitfield(D3DXVECTOR3 pos);
FLOAT Hitfield_Enemy(ENEMY *enemy);
LPDIRECT3DVERTEXBUFFER9 GetMeshFieldVtx(void);

#endif
