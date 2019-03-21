//=============================================================================
//
// ���b�V���n�ʂ̏��� [meshfield.h]
// Author : �����@�[��
//
//=============================================================================
#ifndef _MESHFIELD_H_
#define _MESHFIELD_H_

#include "main.h"
#include "enemy.h"

#define	TEXTURE_FIELD	"data/TEXTURE/wall.png"		// �ǂݍ��ރe�N�X�`���t�@�C����

//*****************************************************************************
// �v���g�^�C�v�錾
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
