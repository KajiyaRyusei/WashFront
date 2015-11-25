//=============================================================================
//
// �r�� [Building.cpp]
// Author : KEITA OHUCHI
//
//=============================================================================

#include "Main.h"
#include "Manager.h"
#include "Renderer.h"
#include "Building.h"
#include "model.h"
#include "ModelFactory.h"
#include "TextureFactory.h"


//=========================================================================
// �R���X�g���N�^�ƃf�X�g���N�^
//=========================================================================
Building::Building(int priority) : Scene(priority),
model_(nullptr),
rotation_(D3DXVECTOR3(0, 0, 0)),
scale_(D3DXVECTOR3(1, 1, 1)),
id_(-1),
modelFilePath_(nullptr),
textureFilePath_(nullptr)
{
	D3DXMatrixIdentity(&worldMatrix_);
}

Building::~Building()
{
	model_ = nullptr;
}

//=========================================================================
// ����������
//=========================================================================
HRESULT Building::Init()
{
	return S_OK;
}

HRESULT Building::Init(const char *modelFilePath, const char *textureFilePath)
{
	if (modelFilePath)
		model_ = Manager::GetInstance()->GetModelFactory()->GetModel(modelFilePath);
	if (textureFilePath)
		texture_ = Manager::GetInstance()->GetTextureFactory()->GetTexture(textureFilePath);
	modelFilePath_ = (char *)modelFilePath;
	textureFilePath_ = (char *)textureFilePath;


	return S_OK;
}

HRESULT Building::Init(const char *modelFilePath, const char *textureFilePath, D3DXVECTOR3 position, D3DXVECTOR3 rotation, D3DXVECTOR3 scale)
{
	if (modelFilePath)
		model_ = Manager::GetInstance()->GetModelFactory()->GetModel(modelFilePath);
	if (textureFilePath)
		texture_ = Manager::GetInstance()->GetTextureFactory()->GetTexture(textureFilePath);
	modelFilePath_ = (char *)modelFilePath;
	textureFilePath_ = (char *)textureFilePath;
	position_ = position;
	rotation_ = rotation;
	scale_ = scale;

	return S_OK;
}

//=========================================================================
// �X�V����
//=========================================================================
void Building::Update()
{
}

//=========================================================================
// �`�揈��
//=========================================================================
void Building::Draw()
{

	Renderer *renderer = Manager::GetInstance()->GetRenderer();
	LPDIRECT3DDEVICE9 device = renderer->GetDevice();
	D3DXMATRIX mtxScl, mtxRot, mtxTranslate;  // �傫��, ��], �ʒu�̍s��

	// ���[���h�}�g���b�N�X�̐ݒ�
	D3DXMatrixIdentity(&worldMatrix_);  // �P�ʍs��ŏ�����

	D3DXMatrixScaling(&mtxScl, scale_.x, scale_.y, scale_.z);
	D3DXMatrixMultiply(&worldMatrix_, &worldMatrix_, &mtxScl);  // �s��̂������킹

	// �n�ʂ̉�]�𔽉f(y, x, z)
	D3DXMatrixRotationYawPitchRoll(&mtxRot, rotation_.y, rotation_.x, rotation_.z);
	D3DXMatrixMultiply(&worldMatrix_, &worldMatrix_, &mtxRot);  // �s��̂������킹

	// �n�ʂ̈ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTranslate, position_.x, position_.y, position_.z);
	D3DXMatrixMultiply(&worldMatrix_, &worldMatrix_, &mtxTranslate);  // �s��̂������킹

	device->SetTransform(D3DTS_WORLD, &worldMatrix_);  // �s��̐ݒ�

	device->SetTexture(0, texture_);
	model_->Draw(worldMatrix_);
	device->SetTexture(0, nullptr);
}


// End of file