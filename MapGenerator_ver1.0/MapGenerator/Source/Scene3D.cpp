//=============================================================================
//
// 3D�|���S���̃N���X [Scene3D.cpp]
// Author : KEITA OHUCHI
//
//=============================================================================

#include "Main.h"
#include "Scene3d.h"
#include "Manager.h"


//-----------------------------------------------------------------------------
// �}�N����`
//-----------------------------------------------------------------------------
#define TEXTURE_NAME (nullptr)
#define POLYGON_WIDTH (250.0f)
#define POLYGON_DEPTH (250.0f)


//=============================================================================
// �R���X�g���N�^
//=============================================================================
Scene3D::Scene3D(int priority) : Scene(priority)
{
	// �����o�ϐ��̏�����
	vertexBuffer_ = nullptr;  // ���_���i�[���[�N
	D3DXMatrixIdentity(&worldMatrix_);  // ���[���h�}�g���N�X
	scale_ = D3DXVECTOR3(1.0f, 1.0f, 1.0f);  // �傫��
	rotation_ = D3DXVECTOR3(0.0f, 0.0f, 0.0f);  // ����
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
Scene3D::~Scene3D()
{
	SafeRelease(vertexBuffer_);
}

//=============================================================================
// ����������
//=============================================================================
HRESULT Scene3D::Init(D3DXVECTOR3 pos, D3DXVECTOR2 size, char *texturePath)
{
	position_ = pos;

	// ���_���W�̐ݒ�
	Renderer *renderer = Manager::GetInstance()->GetRenderer();
	LPDIRECT3DDEVICE9 device = renderer->GetDevice();

	// �e�N�X�`���̓ǂݍ���
	SetTexture(TEXTURE_NAME);

	// ���_�o�b�t�@�̐����i�������̊m�ہj
	if (FAILED(device->CreateVertexBuffer(
							sizeof(VERTEX_3D) * 4,  // �m�ۂ��郁�����̃T�C�Y
							D3DUSAGE_WRITEONLY,
							FVF_VERTEX_3D,  // �g�p���钸�_�t�H�[�}�b�g
							D3DPOOL_MANAGED,
							&vertexBuffer_,  // ���_�o�b�t�@�̐擪�A�h���X�̓������|�C���^�ϐ��̃A�h���X
							nullptr))) {
		return E_FAIL;
	}

	float fAngle = atan2f(size.x / 2, size.y / 2);  // �Ίp���̂Ȃ��p������
	float fLength = sqrtf((size.x / 2) * (size.x / 2) 
							+(size.y / 2) * (size.y / 2));  // �Ίp���̒���������


	// ���_���W�̐ݒ�
	VERTEX_3D *pVtx;
	vertexBuffer_->Lock(0, 0, (void**)&pVtx, 0);  // ���_�������b�N

	pVtx[0].vtx = D3DXVECTOR3(-sinf(fAngle) * fLength, 0.0f, cosf(fAngle) * fLength);
	pVtx[1].vtx = D3DXVECTOR3(sinf(fAngle) * fLength, 0.0f, cosf(fAngle) * fLength);
	pVtx[2].vtx = D3DXVECTOR3(-sinf(fAngle) * fLength, 0.0f, -cosf(fAngle) * fLength);
	pVtx[3].vtx = D3DXVECTOR3(sinf(fAngle) * fLength, 0.0f, -cosf(fAngle) * fLength);

	pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	pVtx[0].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	// �e�N�X�`�����̏�����
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	vertexBuffer_->Unlock();  // ���_�����A�����b�N


	SetTexture(texturePath);


	return S_OK;
}

//=============================================================================
// �X�V����
//=============================================================================
void Scene3D::Update()
{
}

//=============================================================================
// �`�揈��
//=============================================================================
void Scene3D::Draw()
{
	Renderer *renderer = Manager::GetInstance()->GetRenderer();
	LPDIRECT3DDEVICE9 device = renderer->GetDevice();
	D3DXMATRIX mtxScl, mtxRot, mtxTranslate;  // �傫��, ��], �ʒu�̍s��

	// ���[���h�}�g���b�N�X�̐ݒ�
	D3DXMatrixIdentity(&worldMatrix_);  // �P�ʍs��ŏ�����

	D3DXMatrixScaling(&mtxScl, scale_.x, scale_.y, scale_.z);  // �n�ʂ̃X�P�[���𔽉f
	D3DXMatrixMultiply(&worldMatrix_, &worldMatrix_, &mtxScl);  // �s��̂������킹

	D3DXMatrixRotationYawPitchRoll(&mtxRot, rotation_.y, rotation_.x, rotation_.z);  // �n�ʂ̉�]�𔽉f(y, x, z)
	D3DXMatrixMultiply(&worldMatrix_, &worldMatrix_, &mtxRot);  // �s��̂������킹

	D3DXMatrixTranslation(&mtxTranslate, position_.x, position_.y, position_.z);  // �n�ʂ̈ʒu�𔽉f
	D3DXMatrixMultiply(&worldMatrix_, &worldMatrix_, &mtxTranslate);  // �s��̂������킹

	device->SetTransform(D3DTS_WORLD, &worldMatrix_);  // �s��̐ݒ�


	// 3D�|���S���̕`��
	// ���_�o�b�t�@���f�[�^�X�g���[���Ƀo�C���h
	device->SetStreamSource(0, vertexBuffer_, 0, sizeof(VERTEX_3D));

	device->SetFVF(FVF_VERTEX_3D);  // ���_�t�H�[�}�b�g�̐ݒ�
	device->SetTexture(0, texture_);  // �e�N�X�`���̐ݒ�
	device->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);  // �|���S���̕`��
}


// End of file