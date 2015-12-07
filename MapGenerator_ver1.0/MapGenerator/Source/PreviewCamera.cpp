//=============================================================================
//
// �v���r���[�p�J�����N���X [PreviewCamera.cpp]
// Author : KEITA OHUCHI
//
//=============================================================================

#include "Main.h"
#include "PreviewCamera.h"
#include "Manager.h"
#include "ObjectManager.h"
#include "Keyboard.h"
#include "Mouse.h"
#include "RouteManager.h"


//-----------------------------------------------------------------------------
// �}�N����`
//-----------------------------------------------------------------------------
#define DEFAULT_POSITION (D3DXVECTOR3(0.f, 30.f, -50.f))
#define DEFAULT_LOOK_POSITION (D3DXVECTOR3(0.f, 0.f, 0.0f))

#define CAMERA_ROT_DAMPING	(0.15f)	// �J�����̉�]�̊���
#define CAMERA_MOVE_DAMPING	(0.3f)	// �J�����̈ړ��̊���
#define CAMERA_HEIGHT		(1.0f)	// �t�B�[���h���王�_�܂ł̍���
#define LOOK_POS_LENGTH		(0.4f)	// �v���C���[���璍���_�܂ł̋���

#define CAMERA_SPEED		(0.05f)

#define CAMERA_HEIGHT_MIN	(0.5f)	// ���_�̍Œ�_


//=========================================================================
// �R���X�g���N�^
//=========================================================================
PreviewCamera::PreviewCamera() :
time_(0),
length_(0)
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
PreviewCamera::~PreviewCamera()
{
}

//=========================================================================
// ����������
//=========================================================================
HRESULT PreviewCamera::Init()
{
	time_ = 0.0f;
	length_ = 3.0f;

	currentPoint_ = Manager::GetInstance()->GetRouteManager()->GetRoutePoint((int)time_);
	nextPoint_ = Manager::GetInstance()->GetRouteManager()->GetRoutePoint((int)time_ + 1);


	return S_OK;
}

//=========================================================================
// �X�V����
//=========================================================================
void PreviewCamera::Update()
{
	D3DXVECTOR3 cameraDirection(0, 0, length_);

	time_ += 0.01f;
	int cursor = (int)time_;
	currentPoint_ = Manager::GetInstance()->GetRouteManager()->GetRoutePoint(cursor);
	nextPoint_ = Manager::GetInstance()->GetRouteManager()->GetRoutePoint(cursor + 1);


	float t = time_ - cursor;

	//D3DXVECTOR3 rotation = currentPoint_.rotation * (1 - t) + nextPoint_.rotation * t;

	//D3DXMATRIX m;
	//D3DXMatrixIdentity(&m);
	//D3DXMatrixRotationYawPitchRoll(&m, rotation.y, rotation.x, rotation.z);
	//D3DXVec3TransformCoord(&cameraDirection, &cameraDirection, &m);


	D3DXQUATERNION q, q1, q2;
	D3DXMATRIX m, m1, m2;
	D3DXMatrixIdentity(&m1);
	D3DXMatrixRotationYawPitchRoll(&m1, currentPoint_.rotation.y, currentPoint_.rotation.x, currentPoint_.rotation.z);
	D3DXMatrixIdentity(&m2);
	D3DXMatrixRotationYawPitchRoll(&m2, nextPoint_.rotation.y, nextPoint_.rotation.x, nextPoint_.rotation.z);
	D3DXQuaternionRotationMatrix(&q1, &m1);
	D3DXQuaternionRotationMatrix(&q2, &m2);

	D3DXQuaternionSlerp(&q, &q1, &q2, t);
	D3DXMatrixRotationQuaternion(&m, &q);

	D3DXVec3TransformCoord(&cameraDirection, &cameraDirection, &m);


	position_ = currentPoint_.position * (1 - t) + nextPoint_.position * t;
	lookPosition_ = position_ + cameraDirection;

}


// End of file