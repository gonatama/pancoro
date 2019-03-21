//=============================================================================
//
// �G�t�F�N�g���� [effect.h]
// Author : AKIRA TANAKA
//
//=============================================================================
#ifndef _EFFECT_H_
#define _EFFECT_H_

#include "main.h"


#define	EFFECT_SIZE_X			(50.0f)							// �r���{�[�h�̕�
#define	EFFECT_SIZE_Y			(50.0f)							// �r���{�[�h�̍���

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitEffect(void);
void UninitEffect(void);
void UpdateEffect(void);
void DrawEffect(void);

int SetEffect(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXCOLOR col, float fSizeX, float fSizeY, int nTimer);

#endif
