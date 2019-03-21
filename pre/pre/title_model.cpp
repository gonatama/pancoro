//=============================================================================
//
// �^�C�g����ʏ��� [title.cpp]
// Author : �����@�[��
//
//=============================================================================
#include "title_model.h"
#include "input.h"
#include "camera.h"
#include "fade.h"
#include "physics.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define TITLE_PLAYER		"data/PLAYER/Panjandrum.x"	

#define SPEED					(1.0f)

#define TITLE_COUNT				(3)
#define RETURN_POS				(-250.0f)
#define RETRY_POS				(1000.0f)
//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************

LPDIRECT3DTEXTURE9	pD3DTextureTitle_Model;		// �e�N�X�`���ւ̃|�C���^
LPD3DXMESH			pD3DXMeshTitle_Model;		// ���b�V�����ւ̃|�C���^
LPD3DXBUFFER		pD3DXBuffMatTitle_Model;	// �}�e���A�����ւ̃|�C���^
DWORD				nNumMatTitle_Model;			// �}�e���A�����̐�

D3DXVECTOR3			Title_model_pos;				// ���f���̈ʒu
D3DXVECTOR3			Title_model_rot;				// ���f���̌���(��])
D3DXVECTOR3			Title_model_scl;				// ���f���̑傫��(�X�P�[��)
D3DXVECTOR3			Title_model_move;				// �ړ���
D3DXVECTOR3			Title_model_rotDest;				// �ړI�̌���

float				title_vel;

D3DXMATRIX			Title_mtxWorld;				// ���[���h�}�g���b�N�X
float				title_speed;
float				title_jump=100.0f;
int					title_count;

bool				title_air;
bool				title_drop;
bool				enter;
//=============================================================================
// ����������
//=============================================================================
HRESULT InitTitle_Model(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();



	Title_model_pos = D3DXVECTOR3(0.0f, 20.0f, 1000.0f);		// ���f���̈ʒu
	Title_model_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// ���f���̌���(��])
	Title_model_scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);			// ���f���̑傫��(�X�P�[��)
	Title_model_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// �ړ���
	Title_model_rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// �ړI�̌���
	title_speed = 0.0f;

	title_vel = 0.0f;
		// X�t�@�C���̓ǂݍ���
	if (FAILED(D3DXLoadMeshFromX(TITLE_PLAYER,				// �ǂݍ��ރ��f���t�@�C����(X�t�@�C��)
		D3DXMESH_SYSTEMMEM,		// ���b�V���̍쐬�I�v�V�������w��
		pDevice,				// IDirect3DDevice9�C���^�[�t�F�C�X�ւ̃|�C���^
		NULL,					// �אڐ��f�[�^���܂ރo�b�t�@�ւ̃|�C���^
		&pD3DXBuffMatTitle_Model,	// �}�e���A���f�[�^���܂ރo�b�t�@�ւ̃|�C���^
		NULL,					// �G�t�F�N�g�C���X�^���X�̔z����܂ރo�b�t�@�ւ̃|�C���^
		&nNumMatTitle_Model,		// D3DXMATERIAL�\���̂̐�
		&pD3DXMeshTitle_Model)))	// ID3DXMesh�C���^�[�t�F�C�X�ւ̃|�C���^�̃A�h���X
	{
		return E_FAIL;
	}
	return S_OK;


}

//*******************************************************************************
// �I������
//*******************************************************************************
void UninitTitle_Model(void)
{
	if (pD3DTextureTitle_Model != NULL)
	{// �e�N�X�`���̊J��
		pD3DTextureTitle_Model->Release();
		pD3DTextureTitle_Model = NULL;
	}

	if (pD3DXMeshTitle_Model != NULL)
	{// ���b�V���̊J��
		pD3DXMeshTitle_Model->Release();
		pD3DXMeshTitle_Model = NULL;
	}

	if (pD3DXBuffMatTitle_Model != NULL)
	{// �}�e���A���̊J��
		pD3DXBuffMatTitle_Model->Release();
		pD3DXBuffMatTitle_Model = NULL;
	}

}

//*********************************************************************************
// �X�V����
//*********************************************************************************
void UpdateTitle_Model(void)
{

	D3DXVECTOR3 rotCamera = GetRotCamera();
	if (enter == false)
	{
		Title_model_move.x -= sinf(rotCamera.y) * SPEED *title_speed;
		Title_model_move.z -= cosf(rotCamera.y) * SPEED *title_speed;
		Title_model_rot.x += SPEED * 3;



		Title_model_rotDest.y = rotCamera.y;

		Title_model_pos += Title_model_move;

		//���f���̃W�����v
		if (title_air == false)
		{
			Jump_title();
		}

		//�d�͏���
		if ((title_air == true) || (title_drop == true))
		{
			Gravity_title();
		}
		//���˂鏈��
		if ((Title_model_pos.y <= 0.00f)&&(title_count<=3))
		{
			Repeling_title();
			title_count++;

		}
		//���˂�񐔂̃J�E���g
		if (title_count == TITLE_COUNT)
		{
			title_count = 0;
			title_air = false;
			title_drop = false;
		}


		if (Title_model_pos.z < -RETURN_POS)
		{
			int i = rand() % 300;
			if (i % 2 == 0)
			{
				i = i * (-1);
			}
			Title_model_pos.x = (float)i;
			Title_model_pos.z = RETRY_POS + title_speed;
		}

		title_speed += 0.0015f;
		if (title_speed > 0.3f)
		{
			Title_model_move.x = 0.0f;
			Title_model_move.z = 0.0f;
			title_speed = 0.000f;
		}
	}
}

//****************************************************************************************
// �`�揈��
//****************************************************************************************
void DrawTitle_Model(void)
{

	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxScl, mtxRot, mtxTranslate;
	D3DXMATERIAL *pD3DXMat;
	D3DMATERIAL9 matDef;

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&Title_mtxWorld);

	// �X�P�[���𔽉f
	D3DXMatrixScaling(&mtxScl, Title_model_scl.x, Title_model_scl.y, Title_model_scl.z);
	D3DXMatrixMultiply(&Title_mtxWorld, &Title_mtxWorld, &mtxScl);

	// ��]�𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, Title_model_rot.y, Title_model_rot.x, Title_model_rot.z);
	D3DXMatrixMultiply(&Title_mtxWorld, &Title_mtxWorld, &mtxRot);

	// �ړ��𔽉f
	D3DXMatrixTranslation(&mtxTranslate, Title_model_pos.x, Title_model_pos.y, Title_model_pos.z);
	D3DXMatrixMultiply(&Title_mtxWorld, &Title_mtxWorld, &mtxTranslate);

	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &Title_mtxWorld);

	// ���݂̃}�e���A�����擾
	pDevice->GetMaterial(&matDef);

	// �}�e���A�����ɑ΂���|�C���^���擾
	pD3DXMat = (D3DXMATERIAL*)pD3DXBuffMatTitle_Model->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)nNumMatTitle_Model; nCntMat++)
	{
		// �}�e���A���̐ݒ�
		pDevice->SetMaterial(&pD3DXMat[nCntMat].MatD3D);

		// �e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, pD3DTextureTitle_Model);

		// �`��
		pD3DXMeshTitle_Model->DrawSubset(nCntMat);
	}

	// �}�e���A�����f�t�H���g�ɖ߂�
	pDevice->SetMaterial(&matDef);


}


/*********************************
*�d��(enemy)
**********************************/
void Gravity_title(void)
{

	title_vel -= GRAVITY * UNIT_TIME;
	Title_model_pos.y += 0.5f * title_vel * UNIT_TIME;

}
/*********************************
*�W�����v(player)
*********************************/
void Jump_title(void)
{
	title_air = true;
	title_drop = true;
	title_vel += title_jump;

}
/********************************
*����
*********************************/
void Repeling_title(void)
{
	title_vel = title_vel * REPELLING;
}
