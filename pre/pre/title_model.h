//=============================================================================
//
// タイトル画面処理 [title.h]
// Author : 権頭　啓太
//
//=============================================================================
#ifndef _TITLE_MODEL_H_
#define _TITLE_MODEL_H_

#include "main.h"

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************

HRESULT InitTitle_Model(void);
void UninitTitle_Model(void);
void UpdateTitle_Model(void);
void DrawTitle_Model(void);

void Gravity_title(void);
void Jump_title(void);
void Repeling_title(void);


#endif
#pragma once
