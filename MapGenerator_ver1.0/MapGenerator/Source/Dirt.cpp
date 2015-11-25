//=============================================================================
//
// ���� [Dirt.cpp]
// Author : KEITA OHUCHI
//
//=============================================================================
#include "Dirt.h"
#include "Manager.h"
#include "Renderer.h"


VERTEX_3D Dirt::vertexBuffer_[9] = {
	{ D3DXVECTOR3(sinf(-D3DX_PI), cosf(-D3DX_PI), 0.0f), D3DXVECTOR3(0, 0, 0), D3DXCOLOR(1, 0, 0, 1), D3DXVECTOR2(0, 0) },
	{ D3DXVECTOR3(sinf(-D3DX_PI * 3 / 4), cosf(-D3DX_PI * 3 / 4), 0.0f), D3DXVECTOR3(0, 0, 0), D3DXCOLOR(1, 0, 0, 1), D3DXVECTOR2(0, 0) },
	{ D3DXVECTOR3(sinf(-D3DX_PI / 2), cosf(-D3DX_PI / 2), 0.0f), D3DXVECTOR3(0, 0, 0), D3DXCOLOR(1, 0, 0, 1), D3DXVECTOR2(0, 0) },
	{ D3DXVECTOR3(sinf(-D3DX_PI / 4), cosf(-D3DX_PI / 4), 0.0f), D3DXVECTOR3(0, 0, 0), D3DXCOLOR(1, 0, 0, 1), D3DXVECTOR2(0, 0) },
	{ D3DXVECTOR3(sinf(0.0f), cosf(0.0f), 0.0f), D3DXVECTOR3(0, 0, 0), D3DXCOLOR(1, 0, 0, 1), D3DXVECTOR2(0, 0) },
	{ D3DXVECTOR3(sinf(D3DX_PI / 4), cosf(D3DX_PI / 4), 0.0f), D3DXVECTOR3(0, 0, 0), D3DXCOLOR(1, 0, 0, 1), D3DXVECTOR2(0, 0) },
	{ D3DXVECTOR3(sinf(D3DX_PI / 2), cosf(D3DX_PI / 2), 0.0f), D3DXVECTOR3(0, 0, 0), D3DXCOLOR(1, 0, 0, 1), D3DXVECTOR2(0, 0) },
	{ D3DXVECTOR3(sinf(D3DX_PI * 3 / 4), cosf(D3DX_PI * 3 / 4), 0.0f), D3DXVECTOR3(0, 0, 0), D3DXCOLOR(1, 0, 0, 1), D3DXVECTOR2(0, 0) },
	{ D3DXVECTOR3(sinf(-D3DX_PI), cosf(-D3DX_PI), 0.0f), D3DXVECTOR3(0, 0, 0), D3DXCOLOR(1, 0, 0, 1), D3DXVECTOR2(0, 0) },


};


//=========================================================================
// �R���X�g���N�^�ƃf�X�g���N�^
//=========================================================================
Dirt::Dirt() :
position_(D3DXVECTOR3(0, 0, 0)),
radius_(0)
{
}

//=========================================================================
// �R���X�g���N�^�ƃf�X�g���N�^
//=========================================================================
Dirt::~Dirt()
{
}

//=========================================================================
// ����������
//=========================================================================
HRESULT Dirt::Init()
{

	radius_ = 1.0f;

	return S_OK;
}

//=========================================================================
// �X�V����
//=========================================================================
void Dirt::Update()
{
}

//=========================================================================
// �`�揈��
//=========================================================================
void Dirt::Draw()
{
	LPDIRECT3DDEVICE9 device = Manager::GetInstance()->GetRenderer()->GetDevice();
	device->SetRenderState(D3DRS_LIGHTING, false);


	device->SetFVF(FVF_VERTEX_3D);		// ���_�t�H�[�}�b�g�̐ݒ�
	device->SetTexture(0, nullptr);


	// ���[���h�}�g���b�N�X�̐ݒ�
	D3DXMATRIX worldMatrix, scale, rotation, position;
	D3DXMatrixIdentity(&worldMatrix);
	D3DXMatrixScaling(&scale, radius_, radius_, radius_);
	D3DXMatrixRotationYawPitchRoll(&rotation, 0.0f, 0.0f, 0.0f);
	D3DXMatrixTranslation(&position, position_.x, position_.y, position_.z);
	
	worldMatrix = scale * rotation * position;
	device->SetTransform(D3DTS_WORLD, &worldMatrix);
	device->DrawPrimitiveUP(D3DPT_LINESTRIP, 8, vertexBuffer_, sizeof(VERTEX_3D));


	D3DXMatrixRotationYawPitchRoll(&rotation, 0.0f, D3DX_PI / 2, 0.0f);
	worldMatrix = scale * rotation * position;
	device->SetTransform(D3DTS_WORLD, &worldMatrix);
	device->DrawPrimitiveUP(D3DPT_LINESTRIP, 8, vertexBuffer_, sizeof(VERTEX_3D));


	D3DXMatrixRotationYawPitchRoll(&rotation, D3DX_PI / 2, 0.0f, 0.0f);
	worldMatrix = scale * rotation * position;
	device->SetTransform(D3DTS_WORLD, &worldMatrix);
	device->DrawPrimitiveUP(D3DPT_LINESTRIP, 8, vertexBuffer_, sizeof(VERTEX_3D));


	device->SetRenderState(D3DRS_LIGHTING, true);
}


// End of file