//=============================================================================
//
// �G�l�~�[���� [enemy.cpp]
// Author :	 ���� �[��
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
// �}�N����`
//*****************************************************************************
#define	ENEMY_MODEL		"data/ENEMY/enemy_bar.x"							// �ǂݍ��ރ��f����

#define	VIEW_ANGLE		(D3DXToRadian(45.0f))							// �r���[���ʂ̎���p
#define	VIEW_ASPECT		((float)SCREEN_WIDTH / (float)SCREEN_HEIGHT)	// �r���[���ʂ̃A�X�y�N�g��	
#define	ENEMY_MOVE		(3.0f)											// �ړ���
#define	ENEMY_ROTATE	(D3DX_PI * 0.02f)								// ��]��
#define ENEMY_LOST_Y	(-200.0f)

#define ENEMY_LABEL	"Enemy"
//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void EnemyHoming(void);
void EnemySanten(void);
void EnemyQuaternion(void);
void EnemyBlow(void);


//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9	pD3DTextureEnemy;		// �e�N�X�`���ւ̃|�C���^
LPD3DXMESH			pD3DXMeshEnemy;		// ���b�V�����ւ̃|�C���^
LPD3DXBUFFER		pD3DXBuffMatEnemy;	// �}�e���A�����ւ̃|�C���^
DWORD				nNumMatEnemy;			// �}�e���A�����̐�



ENEMY				enemy[ENEMY_MAX];


D3DXMATRIX			enemy_mtxWorld;				// ���[���h�}�g���b�N�X
D3DXMATRIX			mtxWorld_body;

static LPDIRECTSOUNDBUFFER8		g_pSE;						// SE�p�o�b�t�@


//D3DLIGHT9			aLight[NUM_LIGHT];	// ���C�g���

//=============================================================================
// ����������
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
		// �ʒu�E��]�E�X�P�[���̏����ݒ�
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

	// X�t�@�C���̓ǂݍ���
	if (FAILED(D3DXLoadMeshFromX(ENEMY_MODEL,				// �ǂݍ��ރ��f���t�@�C����(X�t�@�C��)
		D3DXMESH_SYSTEMMEM,		// ���b�V���̍쐬�I�v�V�������w��
		pDevice,				// IDirect3DDevice9�C���^�[�t�F�C�X�ւ̃|�C���^
		NULL,					// �אڐ��f�[�^���܂ރo�b�t�@�ւ̃|�C���^
		&pD3DXBuffMatEnemy,	// �}�e���A���f�[�^���܂ރo�b�t�@�ւ̃|�C���^
		NULL,					// �G�t�F�N�g�C���X�^���X�̔z����܂ރo�b�t�@�ւ̃|�C���^
		&nNumMatEnemy,		// D3DXMATERIAL�\���̂̐�
		&pD3DXMeshEnemy)))	// ID3DXMesh�C���^�[�t�F�C�X�ւ̃|�C���^�̃A�h���X

	{
		return E_FAIL;
	}
	//�@���֌W

	g_pSE = LoadSound(SE_HIT);



#if 0
	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,					// �f�o�C�X�ւ̃|�C���^
		TEXTURE_FILENAME,		// �t�@�C���̖��O
		&pD3DTextureEnemy);	// �ǂݍ��ރ������[
#endif

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
	void UninitEnemy(void)
	{
		if (pD3DTextureEnemy != NULL)
		{// �e�N�X�`���̊J��
			pD3DTextureEnemy->Release();
			pD3DTextureEnemy = NULL;
		}

		if (pD3DXMeshEnemy != NULL)
		{// ���b�V���̊J��
			pD3DXMeshEnemy->Release();
			pD3DXMeshEnemy = NULL;
		}

		if (pD3DXBuffMatEnemy != NULL)
		{// �}�e���A���̊J��
			pD3DXBuffMatEnemy->Release();
			pD3DXBuffMatEnemy = NULL;
		}
		if (g_pSE != NULL)
		{	// �e�N�X�`���̊J��
			g_pSE->Release();
			g_pSE = NULL;
		}

	}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateEnemy(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	PLAYER *player = GetPlayer();
	ENEMY *enemy = GetEnemy(0);
	D3DXVECTOR3 move(0.0f, 0.0f, 0.0f);
	
	//�z�[�~���O
	EnemyHoming();
	//�O�]����
	EnemySanten();
	//�N�H�[�^�j�I��
	EnemyQuaternion();
	//�������
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

			//�O�_����
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
			**�@�p������
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
			{	// �r���{�[�h�Ƃ̓����蔻��

				if (hitCheckWall(enemy->posEnemy, enemy->oldEnemy) != 0)
				{
					// �������Ă���̂Ō��̈ʒu�ɖ߂�
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
// �`�揈��
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
			// ���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&enemy_mtxWorld);

			// �X�P�[���𔽉f
			D3DXMatrixScaling(&mtxScl, enemy->sclEnemy.x, enemy->sclEnemy.y, enemy->sclEnemy.z);
			D3DXMatrixMultiply(&enemy_mtxWorld, &enemy_mtxWorld, &mtxScl);

			// ��]�𔽉f
			D3DXMatrixRotationYawPitchRoll(&mtxRot, enemy->rotEnemy.y, enemy->rotEnemy.x, enemy->rotEnemy.z);
			D3DXMatrixMultiply(&enemy_mtxWorld, &enemy_mtxWorld, &mtxRot);

			//�N�H�[�^�j�I�����}�g���N�X
			D3DXMatrixRotationQuaternion(&quatMatrixs, &enemy->Quaternion);
			D3DXMatrixMultiply(&enemy_mtxWorld, &enemy_mtxWorld, &quatMatrixs);

			// �ړ��𔽉f
			D3DXMatrixTranslation(&mtxTranslate, enemy->posEnemy.x, enemy->posEnemy.y, enemy->posEnemy.z);
			D3DXMatrixMultiply(&enemy_mtxWorld, &enemy_mtxWorld, &mtxTranslate);



			// ���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &enemy_mtxWorld);

			// ���݂̃}�e���A�����擾
			pDevice->GetMaterial(&matDef);

			// �}�e���A�����ɑ΂���|�C���^���擾
			pD3DXMat = (D3DXMATERIAL*)pD3DXBuffMatEnemy->GetBufferPointer();

			for (int nCntMat = 0; nCntMat < (int)nNumMatEnemy; nCntMat++)
			{
				// �}�e���A���̐ݒ�
				pDevice->SetMaterial(&pD3DXMat[nCntMat].MatD3D);

				// �e�N�X�`���̐ݒ�
				pDevice->SetTexture(0, pD3DTextureEnemy);

				// �`��
				pD3DXMeshEnemy->DrawSubset(nCntMat);
			}

			//mtxWorld_body = enemy_mtxWorld;

			//DrawEnemy_Head();

			// �}�e���A�����f�t�H���g�ɖ߂�
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
// �ʒu�擾
//=============================================================================
D3DXVECTOR3 GetPositionModel(void)
{
	return enemy->posEnemy;
}

//=============================================================================
// �����擾
//=============================================================================
D3DXVECTOR3 GetRotationModel(void)
{
	return enemy->rotEnemy;
}

//=============================================================================
// �ړI�̌����擾
//=============================================================================
D3DXVECTOR3 GetRotationDestModel(void)
{
	return enemy->rotDestEnemy;
}


/*********************************************************************************
**�z�[�~���O
************************************************************************************/
void homing(ENEMY *enemy)
{
	D3DXVECTOR3 gap,pos;
	float dot;
	D3DXVECTOR3 cross;

	pos=GetPositionPlayer();

	gap = (pos - enemy->posEnemy);
	D3DXVec3Normalize(&gap, &gap);
	//����
	dot = (enemy->posEnemy.x * pos.x) + (enemy->posEnemy.y *pos.y) + (enemy->posEnemy.z * pos.z);
	dot = acosf(dot);

	//�O��
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


