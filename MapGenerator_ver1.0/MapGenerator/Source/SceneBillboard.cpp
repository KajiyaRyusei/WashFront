//=============================================================================
//
// �r���{�[�h�N���X [SceneBillboard.cpp]
// Author : KEITA OHUCHI
//
//=============================================================================

#include "Main.h"
#include "SceneBillboard.h"
#include "Renderer.h"
#include "ObjectManager.h"
#include "CameraManager.h"
#include "Camera.h"
#include "Manager.h"
#include "Mouse.h"
#include "Debug.h"


//-----------------------------------------------------------------------------
// �}�N����`
//-----------------------------------------------------------------------------
#define POLYGON_WIDTH (1.0f)
#define POLYGON_HEIGHT (1.0f)


//=============================================================================
// �R���X�g���N�^
//=============================================================================
SceneBillboard::SceneBillboard(int priority) : Scene(priority)
{
	// �����o�ϐ��̏�����
	vertexBuffer_ = nullptr;  // ���_���i�[���[�N
	D3DXMatrixIdentity(&worldMatrix_);  // ���[���h�}�g���N�X
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
SceneBillboard::~SceneBillboard()
{

	SafeRelease(vertexBuffer_);

}


HRESULT SceneBillboard::Init(D3DXVECTOR2 size, D3DXCOLOR color)
{
	// ���_���W�̐ݒ�
	Renderer *renderer = Manager::GetInstance()->GetRenderer();
	LPDIRECT3DDEVICE9 device = renderer->GetDevice();

	// ���_�o�b�t�@�̐����i�������̊m�ہj
	if (FAILED(device->CreateVertexBuffer(
		sizeof(VERTEX_3D)* 4,  // �m�ۂ��郁�����̃T�C�Y
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,  // �g�p���钸�_�t�H�[�}�b�g
		D3DPOOL_MANAGED,
		&vertexBuffer_,  // ���_�o�b�t�@�̐擪�A�h���X�̓������|�C���^�ϐ��̃A�h���X
		nullptr))) {
		return E_FAIL;
	}

	float fAngle = atan2f(size.x / 2, size.y / 2);  // �Ίp���̂Ȃ��p������
	float fLength = sqrtf((size.x / 2) * (size.x / 2)
		+ (size.y / 2) * (size.y / 2));  // �Ίp���̒���������

	// ���_���W�̐ݒ�
	VERTEX_3D *pVtx;
	vertexBuffer_->Lock(0, 0, (void**)&pVtx, 0);  // ���_�������b�N

	pVtx[0].vtx = D3DXVECTOR3(-sinf(fAngle) * fLength, cosf(fAngle) * fLength, 0.0f);
	pVtx[1].vtx = D3DXVECTOR3(sinf(fAngle) * fLength, cosf(fAngle) * fLength, 0.0f);
	pVtx[2].vtx = D3DXVECTOR3(-sinf(fAngle) * fLength, -cosf(fAngle) * fLength, 0.0f);
	pVtx[3].vtx = D3DXVECTOR3(sinf(fAngle) * fLength, -cosf(fAngle) * fLength, 0.0f);

	pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	pVtx[0].diffuse = pVtx[1].diffuse = pVtx[2].diffuse = pVtx[3].diffuse = color;

	// �e�N�X�`�����̏�����
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	vertexBuffer_->Unlock();  // ���_�����A�����b�N


	return S_OK;
}

//=============================================================================
// ����������
//=============================================================================
HRESULT SceneBillboard::Init()
{
	// ���_���W�̐ݒ�
	Renderer *renderer = Manager::GetInstance()->GetRenderer();
	LPDIRECT3DDEVICE9 device = renderer->GetDevice();

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

	float fAngle = atan2f(POLYGON_WIDTH / 2, POLYGON_HEIGHT / 2);  // �Ίp���̂Ȃ��p������
	float fLength = sqrtf((POLYGON_WIDTH / 2) * (POLYGON_WIDTH / 2) 
							+(POLYGON_HEIGHT / 2) * (POLYGON_HEIGHT / 2));  // �Ίp���̒���������

	// ���_���W�̐ݒ�
	VERTEX_3D *pVtx;
	vertexBuffer_->Lock(0, 0, (void**)&pVtx, 0);  // ���_�������b�N

	pVtx[0].vtx = D3DXVECTOR3(-sinf(fAngle) * fLength, cosf(fAngle) * fLength, 0.0f);
	pVtx[1].vtx = D3DXVECTOR3(sinf(fAngle) * fLength, cosf(fAngle) * fLength, 0.0f);
	pVtx[2].vtx = D3DXVECTOR3(-sinf(fAngle) * fLength, -cosf(fAngle) * fLength, 0.0f);
	pVtx[3].vtx = D3DXVECTOR3(sinf(fAngle) * fLength, -cosf(fAngle) * fLength, 0.0f);

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


	return S_OK;
}

//=============================================================================
// �X�V����
//=============================================================================
void SceneBillboard::Update()
{
}

//=============================================================================
// �`�揈��
//=============================================================================
void SceneBillboard::Draw()
{
	Renderer *renderer = Manager::GetInstance()->GetRenderer();
	LPDIRECT3DDEVICE9 device = renderer->GetDevice();
	Camera *camera = Manager::GetInstance()->GetCameraManager()->GetCamera();
	D3DXMATRIX view_mtx = camera->GetViewMtx();
	D3DXMATRIX translate_mtx;  // �ʒu�̍s��
	D3DMATERIAL9 def_mtr;  // �f�t�H���g�}�e���A��
	device->GetMaterial(&def_mtr);  // ���݂̃}�e���A���ޔ�
	
	// ���C�g�̕`��𖳌���
	device->SetRenderState(D3DRS_LIGHTING, FALSE);
	device->SetRenderState(D3DRS_ZENABLE, false);
	// �A���t�@�e�X�g�L��
	device->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	device->SetRenderState(D3DRS_ALPHAREF, 0);
	device->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	// �G�~�b�V�u�ݒ�
	D3DMATERIAL9 mtr;
	ZeroMemory(&mtr,sizeof(mtr));
	mtr.Emissive = D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f);
	device->SetMaterial(&mtr);
	
	// ���[���h�}�g���b�N�X�̐ݒ�
	D3DXMatrixIdentity(&worldMatrix_);  // �P�ʍs��ŏ�����
	D3DXMatrixInverse(&worldMatrix_, nullptr, &view_mtx);  // �r���[�}�g���N�X�̋t�s�����
	worldMatrix_._41 = 0.0f;  // �s��̗v�f��0������
	worldMatrix_._42 = 0.0f;  // �s��̗v�f��0������
	worldMatrix_._43 = 0.0f;  // �s��̗v�f��0������

	D3DXMatrixTranslation(&translate_mtx, position_.x, position_.y, position_.z);  // �r���{�[�h�̈ʒu�𔽉f
	D3DXMatrixMultiply(&worldMatrix_, &worldMatrix_, &translate_mtx);  // �s��̂������킹
	device->SetTransform(D3DTS_WORLD, &worldMatrix_);  // �s��̐ݒ�


	// 3D�|���S���̕`��
	// ���_�o�b�t�@���f�[�^�X�g���[���Ƀo�C���h
	device->SetStreamSource(0, vertexBuffer_, 0, sizeof(VERTEX_3D));

	device->SetFVF(FVF_VERTEX_3D);  // ���_�t�H�[�}�b�g�̐ݒ�
	device->SetTexture(0, texture_);  // �e�N�X�`���̐ݒ�
	device->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);  // �|���S���̕`��
	

	// �}�e���A�������ɖ߂�
	device->SetMaterial(&def_mtr);

	// �A���t�@�e�X�g����
	device->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
	// ���C�g�̕`���L����
	device->SetRenderState(D3DRS_LIGHTING, TRUE);
	device->SetRenderState(D3DRS_ZENABLE, true);
}

//=============================================================================
// ��������
//=============================================================================
SceneBillboard *SceneBillboard::Create()
{
	// ����
	SceneBillboard *scene = new SceneBillboard;
	// ������
	scene->Init();


	return scene;
}


// End of file