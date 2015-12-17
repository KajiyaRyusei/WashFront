//=============================================================================
//
// �G�f�B�b�g�p�J�����N���X [EditorCamera.cpp]
// Author : KEITA OHUCHI
//
//=============================================================================

#include "Main.h"
#include "EditorCamera.h"
#include "Manager.h"
#include "ObjectManager.h"
#include "Keyboard.h"
#include "Mouse.h"


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
EditorCamera::EditorCamera()
{
	// �����o�ϐ��̏�����
	position_ = D3DXVECTOR3(0.0f, 0.0f, 0.0f);  // ���_�̍��W
	lookPosition_ = D3DXVECTOR3(0.0f, 0.0f, 0.0f);  // �����_�̍��W
	upperVector_ = D3DXVECTOR3(0.0f, 1.0f, 0.0f);  // ������x�N�g��
	rotation_ = D3DXVECTOR3(0.0f, 0.0f, 0.0f);  // ����
	D3DXMatrixIdentity(&viewMatrix_);  // �r���[�}�g���N�X
	D3DXMatrixIdentity(&projectionMatrix_);  // �v���W�F�N�V�����}�g���N�X
	destRotation_ = rotation_;
}

//=========================================================================
// �f�X�g���N�^
//=========================================================================
EditorCamera::~EditorCamera()
{
}

//=========================================================================
// ����������
//=========================================================================
HRESULT EditorCamera::Init(D3DXVECTOR3 pos, D3DXVECTOR3 look_pos)
{
	// �����o�ϐ��̏�����
	position_ = pos;
	lookPosition_ = look_pos;

	// �����̎擾
	/*
	Game *game = Manager::GetInstance()->GetGame();
	MeshField *field = game->GetField();
	float height = field->GetHeight(position_);
	position_.y = m_dest_pos.y = height + CAMERA_HEIGHT;

	Player *player = game->GetPlayer();
	D3DXVECTOR3 player_pos = player->GetPosition();
	lookPosition_.y = m_dest_look_pos.y = player_pos.y;
	*/
	return S_OK;
}

HRESULT EditorCamera::Init()
{
	position_ = DEFAULT_POSITION;
	lookPosition_ = DEFAULT_LOOK_POSITION;

	upperVector_ = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	rotation_ = D3DXVECTOR3(atan2f(lookPosition_.y - position_.y, lookPosition_.z - position_.z),
		atan2f(lookPosition_.x - position_.x, lookPosition_.z - position_.z),
		atan2f(lookPosition_.x - position_.x, lookPosition_.y - position_.y));

	length_ = sqrtf((lookPosition_.x - position_.x) * (lookPosition_.x - position_.x)
		+ (lookPosition_.y - position_.y) * (lookPosition_.y - position_.y)
		+ (lookPosition_.z - position_.z) * (lookPosition_.z - position_.z));


	return S_OK;
}

//=========================================================================
// �X�V����
//=========================================================================
void EditorCamera::Update()
{
	Mouse *mouse = Manager::GetInstance()->GetMouse();
	DIMOUSESTATE state = mouse->GetPressMouse();

	// �}�E�X�z�C�[���N���b�N�ŕ��s�ړ�
	if (state.rgbButtons[BUTTON_SCROLL] & BUTTON_MASK) {
		// �J�����̎��_�̍X�V
		position_.x += sinf(rotation_.y - D3DX_PI / 2) * state.lX * CAMERA_SPEED * (length_ * 0.1f);
		position_.y += sinf(rotation_.x + D3DX_PI / 2) * state.lY * CAMERA_SPEED * (length_ * 0.1f);
		position_.z += cosf(rotation_.y - D3DX_PI / 2) * state.lX * CAMERA_SPEED * (length_ * 0.1f);

		// �J�����̒����_�̍X�V
		lookPosition_.x = position_.x + sinf(rotation_.y) * cosf(rotation_.x) * length_;
		lookPosition_.y = position_.y + sinf(rotation_.x) * length_;
		lookPosition_.z = position_.z + cosf(rotation_.y) * cosf(rotation_.x) * length_;
	} else {
		// �}�E�X�z�C�[���ŃY�[��
		length_ -= 0.03f * state.lZ;
		if (length_ < 0.2f) {
			length_ = 0.2f;
		}

		// �E�N���b�N�����_�ړ�
		if (state.rgbButtons[BUTTON_RIGHT] & BUTTON_MASK) {
			rotation_.y += 0.01f * state.lX;
			if (rotation_.y < -D3DX_PI) {
				rotation_.y += D3DX_PI * 2;
			}
			else if (D3DX_PI < rotation_.y) {
				rotation_.y -= D3DX_PI * 2;
			}
			rotation_.x -= 0.01f * state.lY;
			if (rotation_.x < -D3DX_PI * 0.4999f) {
				rotation_.x = -D3DX_PI * 0.4999f;
			}
			else if (D3DX_PI * 0.4999f < rotation_.x) {
				rotation_.x = D3DX_PI * 0.4999f;
			}
		}

		position_.x = lookPosition_.x - sinf(rotation_.y) * cosf(rotation_.x) * length_;
		position_.y = lookPosition_.y - sinf(rotation_.x) * length_;
		position_.z = lookPosition_.z - cosf(rotation_.y) * cosf(rotation_.x) * length_;
	}

}

//=========================================================================
// �`�揈��
//=========================================================================
void EditorCamera::Set()
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


	D3DVIEWPORT9 viewport;
	viewport.X = 0;
	viewport.Y = 0;
	viewport.Width = SCREEN_WIDTH;
	viewport.Height = SCREEN_HEIGHT;
	viewport.MinZ = 0.0f;
	viewport.MaxZ = 1.0f;
	device->SetViewport(&viewport);
}

// End of file