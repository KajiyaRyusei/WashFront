//=============================================================================
//
// X�t�@�C�����f���N���X [SceneX.cpp]
// Author : KEITA OHUCHI
//
//=============================================================================

#include "Main.h"
#include "SceneX.h"
#include "Manager.h"
#include "Keyboard.h"
#include "ModelFactory.h"
#include "Debug.h"


//=============================================================================
// �R���X�g���N�^
//=============================================================================
SceneX::SceneX(int priority) : Scene(priority)
{
	// �����o�ϐ��̏�����
	model_ = nullptr;
	D3DXMatrixIdentity(&worldMatrix_);
	scale_ = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	rotation_ = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
SceneX::~SceneX()
{
}

//=============================================================================
// ����������
//=============================================================================
HRESULT SceneX::Init()
{
	return S_OK;
}

HRESULT SceneX::Init(char *modelFileName)
{
	// ���f���̎擾
	model_ = Manager::GetInstance()->GetModelFactory()->GetModel(modelFileName);

	return S_OK;
}

HRESULT SceneX::Init(char *modelFileName, char *textureFileName)
{
	// ���f���̎擾
	model_ = Manager::GetInstance()->GetModelFactory()->GetModel(modelFileName);


	// �e�N�X�`���̓ǂݍ���
	SetTexture(textureFileName);

	return S_OK;
}

//=============================================================================
// �X�V����
//=============================================================================
void SceneX::Update()
{
}

//=============================================================================
// �`�揈��
//=============================================================================
void SceneX::Draw()
{
	Renderer *renderer = Manager::GetInstance()->GetRenderer();
	LPDIRECT3DDEVICE9 device = renderer->GetDevice();
	D3DXMATRIX mtxScl, mtxRot, mtxTranslate, worldMatrix;  // �傫��, ��], �ʒu�̍s��

	D3DXMatrixIdentity(&worldMatrix);

	D3DXMatrixScaling(&mtxScl, scale_.x, scale_.y, scale_.z);  // �n�ʂ̃X�P�[���𔽉f
	D3DXMatrixMultiply(&worldMatrix, &worldMatrix, &mtxScl);  // �s��̂������킹

	D3DXMatrixRotationYawPitchRoll(&mtxRot, rotation_.y, rotation_.x, rotation_.z);  // �n�ʂ̉�]�𔽉f(y, x, z)
	D3DXMatrixMultiply(&worldMatrix, &worldMatrix, &mtxRot);  // �s��̂������킹

	D3DXMatrixTranslation(&mtxTranslate, position_.x, position_.y, position_.z);  // �n�ʂ̈ʒu�𔽉f
	D3DXMatrixMultiply(&worldMatrix, &worldMatrix, &mtxTranslate);  // �s��̂������킹

	D3DXMatrixMultiply(&worldMatrix_, &worldMatrix, &worldMatrix_);

	device->SetTransform(D3DTS_WORLD, &worldMatrix_);  // �s��̐ݒ�


	// �`��
	//model_->Draw();


	// ���[���h�}�g���b�N�X�̐ݒ�
	D3DXMatrixIdentity(&worldMatrix_);  // �P�ʍs��ŏ�����
}

//=============================================================================
// ��������
//=============================================================================
SceneX *SceneX::Create()
{
	// ����
	SceneX *scene = new SceneX;
	// ������
	scene->Init();

	return scene;
}

//=========================================================================
// ���f���̐ݒ�
//=========================================================================
void SceneX::SetModel(char *xFileName)
{
	// ���f���̎擾
	model_ = Manager::GetInstance()->GetModelFactory()->GetModel(xFileName);
}


// End of file