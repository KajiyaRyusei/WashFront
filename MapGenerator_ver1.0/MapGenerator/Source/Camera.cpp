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