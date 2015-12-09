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
#include "SceneBillboard.h"


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
length_(0),
index_(0),
player_(nullptr)
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
	SafeDelete(player_);
}

//=========================================================================
// ����������
//=========================================================================
HRESULT PreviewCamera::Init()
{
	time_ = 0.0f;
	length_ = 3.0f;

	currentPoint_ = Manager::GetInstance()->GetRouteManager()->GetRoutePoint(index_, (int)time_);
	nextPoint_ = Manager::GetInstance()->GetRouteManager()->GetRoutePoint(index_, (int)time_ + 1);


	if (!player_) {
		player_ = new SceneBillboard();
		player_->Init(D3DXVECTOR2(1.0f, 2.0f), D3DXCOLOR(1, 1, 1, 1));
		player_->SetTexture("./Resource/Texture/Game/Bullet000.png");
	}


	return S_OK;
}
HRESULT PreviewCamera::Init(int index)
{
	time_ = 0.0f;
	length_ = 3.0f;
	index_ = index;

	currentPoint_ = Manager::GetInstance()->GetRouteManager()->GetRoutePoint(index_, (int)time_);
	nextPoint_ = Manager::GetInstance()->GetRouteManager()->GetRoutePoint(index_, (int)time_ + 1);

	if (!player_) {
		player_ = new SceneBillboard();
		player_->Init(D3DXVECTOR2(1.0f, 2.0f), D3DXCOLOR(1, 1, 1, 1));
	}

	return S_OK;
}

//=========================================================================
// �X�V����
//=========================================================================
void PreviewCamera::Update()
{
	D3DXVECTOR3 cameraDirection(0, 0, length_);
	D3DXVECTOR3 playerDirection(0, 0, 3.0f);

	int cursor = (int)time_;
	currentPoint_ = Manager::GetInstance()->GetRouteManager()->GetRoutePoint(index_, cursor);
	nextPoint_ = Manager::GetInstance()->GetRouteManager()->GetRoutePoint(index_, cursor + 1);

	if (currentPoint_ == nullptr || nextPoint_ == nullptr)
		return;



	// �����_�ȉ�
	float t = time_ - cursor;

	D3DXQUATERNION q, q1, q2;
	D3DXMATRIX m, m1, m2;
	D3DXMatrixIdentity(&m1);
	D3DXMatrixRotationYawPitchRoll(&m1, currentPoint_->rotation.y, currentPoint_->rotation.x, currentPoint_->rotation.z);
	D3DXMatrixIdentity(&m2);
	D3DXMatrixRotationYawPitchRoll(&m2, nextPoint_->rotation.y, nextPoint_->rotation.x, nextPoint_->rotation.z);
	D3DXQuaternionRotationMatrix(&q1, &m1);
	D3DXQuaternionRotationMatrix(&q2, &m2);

	// 2���C�[�W���O
	float t2;
	if (t < 0.5f)
		t2 = 2 * t * 2 * t * 0.5f;
	else
		t2 = -1 * (2 * t - 2) * (2 * t - 2) * 0.5f + 1.0f;

	// ���
	D3DXQuaternionSlerp(&q, &q1, &q2, t2);
	D3DXMatrixRotationQuaternion(&m, &q);

	D3DXVec3TransformCoord(&cameraDirection, &cameraDirection, &m);

	// ���_�����_
	position_ = currentPoint_->position * (1 - t) + nextPoint_->position * t;
	lookPosition_ = position_ + cameraDirection;


	
	D3DXMatrixIdentity(&m1);
	D3DXMatrixRotationYawPitchRoll(&m1, 
		currentPoint_->rotation.y + currentPoint_->playerDirection.y,
		currentPoint_->rotation.x + currentPoint_->playerDirection.x,
		currentPoint_->rotation.z + currentPoint_->playerDirection.z);
	D3DXMatrixIdentity(&m2);
	D3DXMatrixRotationYawPitchRoll(&m2,
		nextPoint_->rotation.y + nextPoint_->playerDirection.y,
		nextPoint_->rotation.x + nextPoint_->playerDirection.x,
		nextPoint_->rotation.z + nextPoint_->playerDirection.z);
	D3DXQuaternionRotationMatrix(&q1, &m1);
	D3DXQuaternionRotationMatrix(&q2, &m2);

	// ���
	D3DXQuaternionSlerp(&q, &q1, &q2, t2);
	D3DXMatrixRotationQuaternion(&m, &q);
	
	D3DXVec3TransformCoord(&playerDirection, &playerDirection, &m);

	player_->SetPosition(position_ + playerDirection);


	// ���Ԃ����Z
	D3DXVECTOR3 v = nextPoint_->position - currentPoint_->position;
	float l = D3DXVec3Length(&v);

	time_ += 0.1f * 1 / l;

}


// End of file