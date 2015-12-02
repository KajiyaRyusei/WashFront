//=============================================================================
//
// �J�����N���X [Camera.cpp]
// Author : KEITA OHUCHI
//
//=============================================================================

#include "Camera.h"
#include "Manager.h"


//=========================================================================
// �R���X�g���N�^
//=========================================================================
Camera::Camera()
{
	// �����o�ϐ��̏�����
	position_ = D3DXVECTOR3(0.0f, 0.0f, 0.0f);  // ���_�̍��W
	lookPosition_ = D3DXVECTOR3(0.0f, 0.0f, 0.0f);  // �����_�̍��W
	upperVector_ = D3DXVECTOR3(0.0f, 1.0f, 0.0f);  // ������x�N�g��
	rotation_ = D3DXVECTOR3(0.0f, 0.0f, 0.0f);  // ����
	D3DXMatrixIdentity(&viewMatrix_);  // �r���[�}�g���N�X
	D3DXMatrixIdentity(&projectionMatrix_);;  // �v���W�F�N�V�����}�g���N�X
	destRotation_ = rotation_;
}

//=========================================================================
// �f�X�g���N�^
//=========================================================================
Camera::~Camera()
{
}


//=========================================================================
// �`�揈��
//=========================================================================
void Camera::Set()
{
	Renderer *renderer = Manager::GetInstance()->GetRenderer();
	LPDIRECT3DDEVICE9 device = renderer->GetDevice();

	// �r���[�}�g���N�X�̐ݒ�
	D3DXMatrixIdentity(&viewMatrix_);  // �P�ʍs��ŏ�����
	D3DXMatrixLookAtLH(&viewMatrix_, &position_, &lookPosition_, &upperVector_);
	device->SetTransform(D3DTS_VIEW, &viewMatrix_);


	// �v���W�F�N�V�����}�g���N�X�̐ݒ�
	D3DXMatrixIdentity(&projectionMatrix_);  // �P�ʍs��ŏ�����
	D3DXMatrixPerspectiveFovLH(
		&projectionMatrix_,  // �v���W�F�N�V�����}�g���N�X�̐���
		D3DX_PI / 4.0f,  // ����p(��/4)
		(float)SCREEN_WIDTH / (float)SCREEN_HEIGHT,  // �A�X�y�N�g��(�� / ����)
		0.1f,  // near�l
		1000.0f);  // far�l
	device->SetTransform(D3DTS_PROJECTION, &projectionMatrix_);
}


//=========================================================================
// �X�N���[�����W���烏�[���h���W�ւ̕ϊ�
//=========================================================================
D3DXVECTOR3 Camera::CalcScreenToWorld(D3DXVECTOR3 screenPosition, D3DXVECTOR2 windowSize)
{
	// �e�s��̋t�s����Z�o
	D3DXMATRIX InvView, InvPrj, VP, InvViewport;
	D3DXMatrixInverse(&InvView, NULL, &viewMatrix_);
	D3DXMatrixInverse(&InvPrj, NULL, &projectionMatrix_);
	D3DXMatrixIdentity(&VP);
	VP._11 = windowSize.x / 2.0f; VP._22 = -windowSize.y / 2.0f;
	VP._41 = windowSize.x / 2.0f; VP._42 = windowSize.y / 2.0f;
	D3DXMatrixInverse(&InvViewport, NULL, &VP);

	// �t�ϊ�
	D3DXVECTOR3 worldPosition;
	D3DXMATRIX tmp = InvViewport * InvPrj * InvView;
	D3DXVec3TransformCoord(&worldPosition, &screenPosition, &tmp);

	return worldPosition;
}


// End of file