//=============================================================================
//
// �X�e���V���V���h�E�N���X [StencilShadow.cpp]
// Author : KEITA OHUCHI
//
//=============================================================================

#include "Main.h"
#include "Manager.h"
#include "StencilShadow.h"
#include "SceneX.h"
#include "Scene2D.h"


//=========================================================================
// �R���X�g���N�^
//=========================================================================
StencilShadow::StencilShadow(int priority) : Scene(priority),
	shadow_(nullptr),
	polygon_(nullptr),
	scale_(1, 1, 1)
{
	shadow_ = new SceneX();
	shadow_->Init("Resource/Model/Game/Shadow/StencilShadow.x");
	shadow_->SetRenderFlag(false);


	polygon_ = new Scene2D();
	polygon_->Init(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0),
	SCREEN_WIDTH, SCREEN_HEIGHT, D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.3f));
	polygon_->SetRenderFlag(false);
}

//=========================================================================
// �f�X�g���N�^
//=========================================================================
StencilShadow::~StencilShadow()
{
	SafeDelete(shadow_);
	SafeDelete(polygon_);
}

//=========================================================================
// �X�V����
//=========================================================================
void StencilShadow::Update()
{
	shadow_->SetPosition(D3DXVECTOR3(0, 0, 0));
}

//=========================================================================
// �`�揈��
//=========================================================================
void StencilShadow::Draw()
{
	Renderer *renderer = Manager::GetInstance()->GetRenderer();
	LPDIRECT3DDEVICE9 device = renderer->GetDevice();
	D3DXMATRIX scaleMatrix, translateMatrix, worldMatrix;
	

	// ���[���h�}�g���b�N�X�̐ݒ�
	D3DXMatrixIdentity(&worldMatrix);

	// �g�k�s��
	D3DXMatrixScaling(&scaleMatrix, scale_.x, scale_.y, scale_.z);
	D3DXMatrixMultiply(&worldMatrix, &worldMatrix, &scaleMatrix);
	// �ړ��s��
	D3DXMatrixTranslation(&translateMatrix, position_.x, position_.y, position_.z);
	D3DXMatrixMultiply(&worldMatrix, &worldMatrix, &translateMatrix);

	// �e�p���f���ɐe�̃}�g���N�X��ݒ�
	shadow_->SetWorldMatrix(worldMatrix);

	
	// ���f���̕\�����X�e���V���o�b�t�@�ɕ`��
	device->SetRenderState(D3DRS_STENCILENABLE, TRUE);
	device->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
	device->SetRenderState(D3DRS_COLORWRITEENABLE, 0x0);
	device->SetRenderState(D3DRS_STENCILFUNC, D3DCMP_ALWAYS);
	device->SetRenderState(D3DRS_STENCILPASS, D3DSTENCILOP_INCR);
	device->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);

	shadow_->Draw();


	// �e�p���f���ɐe�̃}�g���N�X��ݒ�
	shadow_->SetWorldMatrix(worldMatrix);

	// ���f���̗������X�e���V���o�b�t�@�ɕ`��
	device->SetRenderState(D3DRS_STENCILPASS, D3DSTENCILOP_DECR);
	device->SetRenderState(D3DRS_CULLMODE, D3DCULL_CW);

	shadow_->Draw();


	// �S���2D�|���S�����X�e���V���o�b�t�@���Q�Ƃ��ĕ`��
	device->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	device->SetRenderState(D3DRS_STENCILREF, 0x01);
	device->SetRenderState(D3DRS_STENCILFUNC, D3DCMP_EQUAL);
	device->SetRenderState(D3DRS_COLORWRITEENABLE, 0xf);

	polygon_->Draw();

	// �o�b�t�@�̐ݒ�����ǂ�
	device->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
	device->SetRenderState(D3DRS_STENCILENABLE, FALSE);
	
}


// End of file