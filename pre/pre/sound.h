//=============================================================================
//
// サウンド処理 [sound.h]
// Author : 権頭　啓太
//
//=============================================================================
#ifndef ___SOUND_H___
#define ___SOUND_H___

#include "main.h"
#include <windows.h>
#include <tchar.h>
#include <dsound.h>
#include <mmsystem.h>

// マクロ定義
enum
{	// サウンド通しナンバー
	BGM_00,
	SE_EXPLOSION,
	SE_HIT,
	FIRE_START,
	ENTER,
	SOUND_MAX
};

enum
{	// 再生用フラグ
	E_DS8_FLAG_NONE,
	E_DS8_FLAG_LOOP,	// DSBPLAY_LOOPING=1
	E_DS8_FLAG_MAX
};

HRESULT					InitSound(HWND hWnd);	// 初期化
void					UninitSound();			// 後片付け
LPDIRECTSOUNDBUFFER8	LoadSound(int no);	// サウンドのロード
void					PlaySound(LPDIRECTSOUNDBUFFER8 pBuffer, int flag = 0);	// 音ごとに再生
bool					IsPlaying(LPDIRECTSOUNDBUFFER8 pBuffer);					// 再生中かどうか

#endif


