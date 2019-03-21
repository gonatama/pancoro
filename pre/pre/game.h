//=============================================================================
//
// ゲーム画面処理 [game.h]
// Author : 権頭　啓太
//
//=============================================================================
#ifndef _GAME_H_
#define _GAME_H_

#include "main.h"

#define FILED_TIP_X			(30)
#define FILED_TIP_Z			(150)
#define FILED_SIZE_X		(100.0f)
#define FILED_SIZE_Z		(100.0f)
#define WALL_X				(16000.0f)
#define WALL_Y				(16000.0f)
#define WALL_POS_X			(600.0f)
#define WALL_POS_Y			(1000.0f)
#define WALL_POS_Z			(6000.0f)

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitGame(void);
void UninitGame(void);
void UpdateGame(void);
void DrawGame(void);

#endif
