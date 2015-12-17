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
#include "SceneX.h"
#include "../resource.h"


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
mplayer_(nullptr)
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
	SafeDelete(mplayer_);
}

//=========================================================================
// ����������
//=========================================================================
HRESULT PreviewCamera::Init()
{
	HWND hCombo1 = 0;
	int time = 0;
	if (Manager::GetInstance()->GetRouteManager()->GetRouteMode()
		== ROUTE_MODE_1P_CAMERA) {
		hCombo1 = GetDlgItem(GetRouteDialogHandle(), IDC_COMBO4);
		time = SendMessage(
			(HWND)hCombo1,			// �R���{�{�b�N�X�̃n���h��
			(UINT)CB_GETCURSEL,		// �I�𒆂̃C���f�b�N�X�擾
			0,						// �O�Œ�
			0						// �ǉ����鍀�ڂ̕�����
			);
	}
	else {
		hCombo1 = GetDlgItem(GetRouteDialogHandle(), IDC_COMBO2);
		time = SendMessage(
			(HWND)hCombo1,			// �R���{�{�b�N�X�̃n���h��
			(UINT)CB_GETCURSEL,		// �I�𒆂̃C���f�b�N�X�擾
			0,						// �O�Œ�
			0						// �ǉ����鍀�ڂ̕�����
			);
	}

	time_ = (float)time;
	length_ = 3.0f;

	currentPoint_ = Manager::GetInstance()->GetRouteManager()->GetRoutePoint(index_, (int)time_);
	nextPoint_ = Manager::GetInstance()->GetRouteManager()->GetRoutePoint(index_, (int)time_ + 1);


	//if (!player_) {
	//	player_ = new SceneBillboard();
	//	player_->Init(D3DXVECTOR2(1.0f, 2.0f), D3DXCOLOR(1, 1, 1, 1));
	//	player_->SetTexture("./Resource/Texture/Game/Bullet000.png");
	//}

	if (!mplayer_) {
		mplayer_ = new SceneX();
		mplayer_->Init("./Resource/Model/Game/new_standby.fbx");
//		mplayer_->SetTexture("");
	}



	return S_OK;
}
HRESULT PreviewCamera::Init(int index)
{

	HWND hCombo1 = 0;
	int time = 0;
	if (Manager::GetInstance()->GetRouteManager()->GetRouteMode()
		== ROUTE_MODE_1P_CAMERA) {
		hCombo1 = GetDlgItem(GetRouteDialogHandle(), IDC_COMBO4);
		time = SendMessage(
			(HWND)hCombo1,			// �R���{�{�b�N�X�̃n���h��
			(UINT)CB_GETCURSEL,		// �I�𒆂̃C���f�b�N�X�擾
			0,						// �O�Œ�
			0						// �ǉ����鍀�ڂ̕�����
			);
	} else {
		hCombo1 = GetDlgItem(GetRouteDialogHandle(), IDC_COMBO2);
		time = SendMessage(
			(HWND)hCombo1,			// �R���{�{�b�N�X�̃n���h��
			(UINT)CB_GETCURSEL,		// �I�𒆂̃C���f�b�N�X�擾
			0,						// �O�Œ�
			0						// �ǉ����鍀�ڂ̕�����
			);
	}

	time_ = (float)time;
	length_ = 3.0f;
	index_ = index;

	currentPoint_ = Manager::GetInstance()->GetRouteManager()->GetRoutePoint(index_, (int)time_);
	nextPoint_ = Manager::GetInstance()->GetRouteManager()->GetRoutePoint(index_, (int)time_ + 1);

	//if (!player_) {
	//	player_ = new SceneBillboard();
	//	player_->Init(D3DXVECTOR2(1.0f, 1.5f), D3DXCOLOR(1, 1, 1, 1));
	//	player_->SetTexture("./Resource/Texture/Game/Bullet000.png");
	//}

	if (!mplayer_) {
		mplayer_ = new SceneX();
		mplayer_->Init("./Resource/Model/Game/Player.x");
	}

	return S_OK;
}

//=========================================================================
// �X�V����
//=========================================================================
void PreviewCamera::Update()
{
	D3DXVECTOR3 cameraDirection(0, 0, length_);
	D3DXVECTOR3 playerDirection(0, 0, 5.0f);

	int cursor = (int)time_;
	currentPoint_ = Manager::GetInstance()->GetRouteManager()->GetRoutePoint(index_, cursor);
	nextPoint_ = Manager::GetInstance()->GetRouteManager()->GetRoutePoint(index_, cursor + 1);

	if (currentPoint_ == nullptr || nextPoint_ == nullptr)
		return;


	// �����_�ȉ�
	float t = time_ - cursor;

	// 2���C�[�W���O
	float t2;
	if (t < 0.5f)
		t2 = 2 * t * 2 * t * 0.5f;
	else
		t2 = -1 * (2 * t - 2) * (2 * t - 2) * 0.5f + 1.0f;



	D3DXQUATERNION q, q1, q2;
	D3DXMATRIX m, m1, m2;
	D3DXMatrixIdentity(&m1);
	D3DXMatrixRotationYawPitchRoll(&m1, currentPoint_->rotation.y, currentPoint_->rotation.x, currentPoint_->rotation.z);
	D3DXMatrixIdentity(&m2);
	D3DXMatrixRotationYawPitchRoll(&m2, nextPoint_->rotation.y, nextPoint_->rotation.x, nextPoint_->rotation.z);
	D3DXQuaternionRotationMatrix(&q1, &m1);
	D3DXQuaternionRotationMatrix(&q2, &m2);



	// ���
	D3DXQuaternionSlerp(&q, &q1, &q2, t2);
	D3DXMatrixRotationQuaternion(&m, &q);

	D3DXVec3TransformCoord(&cameraDirection, &cameraDirection, &m);


	//if (nextPoint_->state == 0) {
		// ���_�����_
		position_ = currentPoint_->position * (1 - t) + nextPoint_->position * t;
		D3DXVec3Lerp(&position_, &currentPoint_->position, &nextPoint_->position, t);
		lookPosition_ = position_ + cameraDirection;
	/*} else if (nextPoint_->state == 1) {
		D3DXVECTOR3 v = nextPoint_->position - currentPoint_->position;
		D3DXVec3Normalize(&v, &v);
		v = v * length_;
		lookPosition_ = currentPoint_->position * (1 - t) + nextPoint_->position * t + v;
		position_ = lookPosition_ - cameraDirection;
	}*/

	
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


	D3DXVECTOR3 v = nextPoint_->position - currentPoint_->position;

	//if (currentPoint_->state == 0 && nextPoint_->state == 0) {
	float rot = atan2f(v.x, v.z);
		mplayer_->SetPosition(position_ + playerDirection);
		mplayer_->SetRotation(D3DXVECTOR3(0.0f, rot, 0.0f));
	//} else if (nextPoint_->state == 0 && nextPoint_->state == 1) {

	//}

	// ���Ԃ����Z
	float l = D3DXVec3Length(&v);

	time_ += currentPoint_->speed * 1 / l;

}

//=========================================================================
// �`�揈��
//=========================================================================
void PreviewCamera::Set()
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
		(float)SCREEN_WIDTH / (float)(SCREEN_HEIGHT / 2),  // �A�X�y�N�g��(�� / ����)
		0.1f,  // near�l
		1000.0f);  // far�l
	device->SetTransform(D3DTS_PROJECTION, &projectionMatrix_);


	D3DVIEWPORT9 viewport;
	viewport.X = 0;
	viewport.Y = 0;
	viewport.Width = SCREEN_WIDTH;
	viewport.Height = SCREEN_HEIGHT / 2;
	viewport.MinZ = 0.0f;
	viewport.MaxZ = 1.0f;
	device->SetViewport(&viewport);
}


// End of file