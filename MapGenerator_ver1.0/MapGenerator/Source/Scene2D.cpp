//=============================================================================
//
// 2D�|���S���̃N���X [Scene2D.cpp]
// Author : KEITA OHUCHI
//
//=============================================================================

#include "Main.h"
#include "Scene2d.h"
#include "Manager.h"
#include "Keyboard.h"


//-----------------------------------------------------------------------------
// �}�N����`
//-----------------------------------------------------------------------------
#define ANIMATION_RATIO	(0.4f)	// �A�j���[�V�����̊���
#define MOVEMENT_RATIO	(0.3f)	// �ړ��̊���


//=========================================================================
// �R���X�g���N�^
//=========================================================================
Scene2D::Scene2D(int priority) : Scene(priority)
{

	rotation_ = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	vertexBuffer_ = nullptr;
	width_ = destWidth_ = 0.0f;
	height_ = destHeight_ = 0.0f;
	flashFlag_ = false;
	flashSpeed_ = 0.0f;
	destPosition_ = D3DXVECTOR3(0, 0, 0);

}

//=========================================================================
// �f�X�g���N�^
//=========================================================================
Scene2D::~Scene2D()
{

	SafeRelease(vertexBuffer_);

}

//=============================================================================
// ����������
//=============================================================================
HRESULT Scene2D::Init(D3DXVECTOR3 pos, float width, float height, D3DXCOLOR color)
{
	// �����o�ϐ��̏�����
	width_ = destWidth_ = width;
	height_ = destHeight_ = height;
	position_ = destPosition_ = pos;

	// ���_���W�̐ݒ�
	VERTEX_2D *pVtx;
	Renderer *renderer = Manager::GetInstance()->GetRenderer();
	LPDIRECT3DDEVICE9 device = renderer->GetDevice();

	// ���_�o�b�t�@�̐����i�������̊m�ہj
	if (FAILED(device->CreateVertexBuffer(
							sizeof(VERTEX_2D) * 4,  // �m�ۂ��郁�����̃T�C�Y
							D3DUSAGE_WRITEONLY,
							FVF_VERTEX_2D,  // �g�p���钸�_�t�H�[�}�b�g
							D3DPOOL_MANAGED,
							&vertexBuffer_,  // ���_�o�b�t�@�̐擪�A�h���X�̓������|�C���^�ϐ��̃A�h���X
							nullptr))) {
		return E_FAIL;
	}


	// ���_���W�̐ݒ�
	vertexBuffer_->Lock(0, 0, (void**)&pVtx, 0);  // ���_�������b�N

	pVtx[0].vtx = D3DXVECTOR3(position_.x - width / 2 + 0.5f, position_.y - height / 2 + 0.5f, 0.0f);
	pVtx[1].vtx = D3DXVECTOR3(position_.x + width / 2 - 0.5f, position_.y - height / 2 + 0.5f, 0.0f);
	pVtx[2].vtx = D3DXVECTOR3(position_.x - width / 2 + 0.5f, position_.y + height / 2 - 0.5f, 0.0f);
	pVtx[3].vtx = D3DXVECTOR3(position_.x + width / 2 - 0.5f, position_.y + height / 2 - 0.5f, 0.0f);
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;
	pVtx[0].diffuse = color;
	pVtx[1].diffuse = color;
	pVtx[2].diffuse = color;
	pVtx[3].diffuse = color;

	// �e�N�X�`�����̏�����
	pVtx[0].tex = D3DXVECTOR2(0.001f, 0.001f);
	pVtx[1].tex = D3DXVECTOR2(0.999f, 0.001f);
	pVtx[2].tex = D3DXVECTOR2(0.001f, 0.999f);
	pVtx[3].tex = D3DXVECTOR2(0.999f, 0.999f);

	vertexBuffer_->Unlock();  // ���_�����A�����b�N


	return S_OK;
}

//=============================================================================
// �X�V����
//=============================================================================
void Scene2D::Update()
{
	VERTEX_2D *pVtx;
	D3DXCOLOR color;


	width_ += (destWidth_ - width_) * ANIMATION_RATIO;
	height_ += (destHeight_ - height_) * ANIMATION_RATIO;
	position_ += (destPosition_ - position_) * MOVEMENT_RATIO;


	// ���_���W�̐ݒ�
	vertexBuffer_->Lock(0, 0, (void**)&pVtx, 0);  // ���_�������b�N

	pVtx[0].vtx = D3DXVECTOR3(position_.x - width_ / 2, position_.y - height_ / 2, 0.0f);
	pVtx[1].vtx = D3DXVECTOR3(position_.x + width_ / 2, position_.y - height_ / 2, 0.0f);
	pVtx[2].vtx = D3DXVECTOR3(position_.x - width_ / 2, position_.y + height_ / 2, 0.0f);
	pVtx[3].vtx = D3DXVECTOR3(position_.x + width_ / 2, position_.y + height_ / 2, 0.0f);

	// �_�ł��邩
	if (flashFlag_) {
		color = pVtx[0].diffuse;
		color.a += flashSpeed_;
		if (color.a < 0.2f) {
			color.a = 0.2f;
			flashSpeed_ *= -1.0f;
		} else if (1.0f < color.a) {
			color.a = 1.0f;
			flashSpeed_ *= -1.0f;
		}
		pVtx[0].diffuse = color;
		pVtx[1].diffuse = color;
		pVtx[2].diffuse = color;
		pVtx[3].diffuse = color;
	}

	vertexBuffer_->Unlock();  // ���_�����A�����b�N
}

//=============================================================================
// �`�揈��
//=============================================================================
void Scene2D::Draw()
{
	Renderer *renderer = Manager::GetInstance()->GetRenderer();
	LPDIRECT3DDEVICE9 device = renderer->GetDevice();


	device->SetRenderState(D3DRS_ZENABLE, FALSE);

	// ���_�o�b�t�@���f�[�^�X�g���[���Ƀo�C���h
	device->SetStreamSource(0, vertexBuffer_, 0, sizeof(VERTEX_2D));
		
	device->SetFVF(FVF_VERTEX_2D);  // ���_�t�H�[�}�b�g�̐ݒ�
	device->SetTexture(0, texture_);  // �e�N�X�`���̐ݒ�
	device->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);  // �|���S���̕`��

	device->SetRenderState(D3DRS_ZENABLE, TRUE);

}

//=============================================================================
// ��������
//=============================================================================
Scene2D *Scene2D::Create(D3DXVECTOR3 pos, float width, float height, D3DXCOLOR color)
{
	// ����
	Scene2D *scene2D = new Scene2D();
	// ������
	scene2D->Init(pos, width, height, color);
	

	return scene2D;
}

//=========================================================================
// �F�̐ݒ�
//=========================================================================
void Scene2D::SetColor(D3DXCOLOR color)
{
	// ���_���W�̐ݒ�
	VERTEX_2D *pVtx;
	
	// ���_���W�̐ݒ�
	vertexBuffer_->Lock(0, 0, (void**)&pVtx, 0);  // ���_�������b�N

	pVtx[0].diffuse = color;
	pVtx[1].diffuse = color;
	pVtx[2].diffuse = color;
	pVtx[3].diffuse = color;

	vertexBuffer_->Unlock();
}

//=========================================================================
// ���̐ݒ�
//=========================================================================
void Scene2D::SetWidth(float width)
{
	width_ = destWidth_ = width;

	VERTEX_2D *pVtx;
	vertexBuffer_->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].vtx = D3DXVECTOR3(position_.x - width_ / 2, position_.y - height_ / 2, 0.0f);
	pVtx[1].vtx = D3DXVECTOR3(position_.x + width_ / 2, position_.y - height_ / 2, 0.0f);
	pVtx[2].vtx = D3DXVECTOR3(position_.x - width_ / 2, position_.y + height_ / 2, 0.0f);
	pVtx[3].vtx = D3DXVECTOR3(position_.x + width_ / 2, position_.y + height_ / 2, 0.0f);

	vertexBuffer_->Unlock();
}
//=========================================================================
// �����̐ݒ�
//=========================================================================
void Scene2D::SetHeight(float height)
{
	height_ = destHeight_ = height;

	VERTEX_2D *pVtx;
	vertexBuffer_->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].vtx = D3DXVECTOR3(position_.x - width_ / 2, position_.y - height_ / 2, 0.0f);
	pVtx[1].vtx = D3DXVECTOR3(position_.x + width_ / 2, position_.y - height_ / 2, 0.0f);
	pVtx[2].vtx = D3DXVECTOR3(position_.x - width_ / 2, position_.y + height_ / 2, 0.0f);
	pVtx[3].vtx = D3DXVECTOR3(position_.x + width_ / 2, position_.y + height_ / 2, 0.0f);

	vertexBuffer_->Unlock();
}



// End of file