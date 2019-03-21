/*****************************************************************
** 物理系の処理[physics.cpp]
** Author : 権頭　啓太
*****************************************************************/
#include "input.h"
#include "physics.h"
#include "meshfield.h"
/***********************************
*グローバル変数
************************************/

float vel = 0.0f;

/*********************************
*重力(player)
**********************************/
void Gravity(PLAYER *player)
{

		vel -= GRAVITY * UNIT_TIME;
		player->pos.y += 0.5f * vel * UNIT_TIME;

}
/*********************************
*ジャンプ(player)
*********************************/
void Jump(PLAYER *player)
{
	player->ground = false;
	vel += player->jumpspeed;

}
/********************************
*反発
*********************************/
void Repelling(PLAYER *player)
{
	vel = vel * REPELLING;
}


/*********************************
*重力(enemy)
**********************************/
void Gravity(ENEMY *enemy)
{

	enemy->vel -= GRAVITY * UNIT_TIME;
	enemy->moveEnemy.y += 0.5f * enemy->vel * UNIT_TIME;

}

/********************************
*反発
*********************************/
void Repelling(ENEMY *enemy)
{
	enemy->vel = enemy->vel * REPELLING;
}

/************************************
*SetVel
* Velを0に戻す。
*************************************/
void SetVel(void)
{
	vel = 0;
}


float Getvel(void)
{
	return vel;
}
