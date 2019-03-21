//=============================================================================
//
// �Q�[����ʏ��� [game.cpp]
// Author :�����@�[��
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
// �}�N����`
//*****************************************************************************
#define GAMESCRNR_LABEL		"GameScene"

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************

//=============================================================================
// ����������
//=============================================================================
HRESULT InitGame(void)
{
	// ���C�g�̏�����
	InitLight();

	// �J�����̏�����
	InitCamera();

	// �n�ʂ̏�����
	InitMeshField(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), FILED_TIP_X, FILED_TIP_Z, FILED_SIZE_X, FILED_SIZE_Z);

	// �ǂ̏�����
	InitMeshWall(D3DXVECTOR3(0.0f, -WALL_POS_Y, WALL_POS_Z), D3DXVECTOR3(0.0f, 0.0f, 0.0f),
									D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 1, 1, WALL_X, WALL_Y);
	InitMeshWall(D3DXVECTOR3(-WALL_POS_X, -WALL_POS_Y, 0.0f), D3DXVECTOR3(0.0f, -D3DX_PI * 0.50f, 0.0f),
									D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 1, 1, WALL_X, WALL_Y);
	InitMeshWall(D3DXVECTOR3(WALL_POS_X, -WALL_POS_Y, 0.0f), D3DXVECTOR3(0.0f, D3DX_PI * 0.50f, 0.0f),
									D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 1, 1, WALL_X, WALL_Y);
	InitMeshWall(D3DXVECTOR3(0.0f, -WALL_POS_Y, WALL_POS_Z), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f),
									D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 1, 1, WALL_X, WALL_Y);

	// ��(�����p)
	InitMeshWall(D3DXVECTOR3(0.0f, -WALL_POS_Y, WALL_POS_Z), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f),
									D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.25f), 1, 1, WALL_X, WALL_Y);
	InitMeshWall(D3DXVECTOR3(-WALL_POS_X, -WALL_POS_Y, 0.0f), D3DXVECTOR3(0.0f, D3DX_PI * 0.50f, 0.0f),
									D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.25f), 1, 1, WALL_X, WALL_Y);
	InitMeshWall(D3DXVECTOR3(WALL_POS_X, -WALL_POS_Y, 0.0f), D3DXVECTOR3(0.0f, -D3DX_PI * 0.50f, 0.0f),
									D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.25f), 1, 1, WALL_X, WALL_Y);
	InitMeshWall(D3DXVECTOR3(0.0f, -WALL_POS_Y, -WALL_POS_Z), D3DXVECTOR3(0.0f, 0.0f, 0.0f),
									D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.25f), 1, 1, WALL_X, WALL_Y);

	// �e�̏�����
	InitShadow();

	InitEnemy();
	// �v���C���[�̏�����
	InitPlayer();

	InitParticle();

	// �����̏�����
	InitExplosion();


	// ���C�t�̏�����
	InitLife();

	// �^�C�}�[�̏�����
	InitTimer();

	ResetTimer(60);

	// �X�R�A�̏�����
	InitScore();

	InitDebugProc();


	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitGame(void)
{
	// ���C�g�̏I������
	UninitLight();

	// �J�����̏I������
	UninitCamera();

	// �n�ʂ̏I������
	UninitMeshField();

	// �ǂ̏I������
	UninitMeshWall();

	// �e�̏I������
	UninitShadow();

	// �G�l�~�[�̏I������
	UninitEnemy();

	// �v���C���[�̏I������
	UninitPlayer();

	//�p�[�e�B�N���̏I������
	UninitParticle();

	// �����̏I������
	UninitExplosion();


	// ���C�t�̏I������
	UninitLife();

	// �^�C�}�[�̏I������
	UninitTimer();

	// �X�R�A�̏I������
	UninitScore();

	UninitDebugProc();
	// BGM��~
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateGame(void)
{
	// �J�����X�V
	UpdateCamera();

	// �n�ʏ����̍X�V
	UpdateMeshField();

	//// �Ǐ����̍X�V
	UpdateMeshWall();

	// �e�����̍X�V
	UpdateShadow();

	// �v���C���[�����̍X�V
	UpdateEnemy();


	// �v���C���[�����̍X�V
	UpdatePlayer();


	// �p�[�e�B�N���̍X�V����
	UpdateParticle();

	// ���������̍X�V
	UpdateExplosion();


	// ���C�t�����̍X�V
	UpdateLife();

	// �^�C�}�[�����̍X�V
	UpdateTimer();

	// �X�R�A�����̍X�V
	UpdateScore();

	UpdateDebugProc();
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawGame(void)
{
	// �J�����̐ݒ�
	SetCamera();

	// �n�ʏ����̕`��
	DrawMeshField();

	// �e�����̕`��
	DrawShadow();

	// �G�l�~�[�����̍X�V
	DrawEnemy();

	// �v���C���[�����̕`��
	DrawPlayer();

	//�@�p�[�e�B�N���̕`�揈��
	DrawParticle();

	//// �Ǐ����̕`��
	DrawMeshWall();

	// ���������̕`��
	DrawExplosion();
	

	// ���C�t�����̕`��
	DrawLife();

	// �^�C�}�[�����̕`��
	DrawTimer();

	// �X�R�A�����̕`��
	DrawScore();

	DrawDebugProc();

}
