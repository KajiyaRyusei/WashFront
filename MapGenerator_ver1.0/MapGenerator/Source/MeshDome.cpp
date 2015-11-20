//=============================================================================
//
// ���b�V���h�[���N���X [MeshDome.cpp]
// Author : KEITA OHUCHI
//
//=============================================================================

#include "MeshDome.h"
#include "Main.h"
#include "Manager.h"
#include "ObjectManager.h"
#include "Renderer.h"
#include "CameraManager.h"
#include "Camera.h"


//=============================================================================
// �R���X�g���N�^
//=============================================================================
MeshDome::MeshDome(int priority) : Scene3D(priority)
{
	// �����o�ϐ��̃N���A
	radius_ = 0.0f;
	indexBuffer_ = nullptr;
	indexNum_ = 0;
	vertexNum_ = 0;
	blockNumX_ = 0;
	blockNumY_ = 0;
	polygonNum_ = 0;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
MeshDome::~MeshDome()
{

	SafeRelease(indexBuffer_);

}

//=============================================================================
// ����������
//=============================================================================
HRESULT MeshDome::Init(D3DXVECTOR3 pos,
	int block_num_x, int block_num_y,
	float radius)
{
	Renderer *renderer = Manager::GetInstance()->GetRenderer();
	LPDIRECT3DDEVICE9 device = renderer->GetDevice();

	// �����ɂ��ϐ��̏�����
	blockNumX_ = block_num_x;
	blockNumY_ = block_num_y;
	radius_ = radius;

	// �|���S���̕`��ɕK�v�ȕϐ��̏�����
	const int vertical_line_num = blockNumX_ + 1;  // �u���b�N���������߂ɕK�v�Ȑ������̖{��
	const int horizon_line_num = blockNumY_ + 1;  // �u���b�N���������߂ɕK�v�Ȑ������̖{��
	const int turn_num = blockNumY_ - 1;  // �܂�Ԃ���
	indexNum_ = vertical_line_num * block_num_y * 2 + turn_num * 2;
	vertexNum_ = vertical_line_num * horizon_line_num;
	polygonNum_ = (blockNumX_ * blockNumY_) * 2 + turn_num * 4;

	// �n�ʏ��̏�����
	position_ = pos;
	rotation_ = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	scale_ = D3DXVECTOR3(1.0f, 1.0f, 1.0f);

	// ���_�o�b�t�@�̐���
	if (FAILED(device->CreateVertexBuffer(
							sizeof(VERTEX_3D) * (vertexNum_ + 1),  // �m�ۂ��郁�����̃T�C�Y
							D3DUSAGE_WRITEONLY,
							FVF_VERTEX_3D,  // �g�p���钸�_�t�H�[�}�b�g
							D3DPOOL_MANAGED,
							&vertexBuffer_,  // ���_�o�b�t�@�ւ̃|�C���^
							nullptr))) {
		return E_FAIL;
	}

	// �C���f�b�N�X�o�b�t�@�̐���
	if (FAILED(device->CreateIndexBuffer(
							sizeof(WORD) * indexNum_,  // �m�ۂ��郁�����̃T�C�Y
							D3DUSAGE_WRITEONLY,
							D3DFMT_INDEX16,
							D3DPOOL_MANAGED,
							&indexBuffer_,  // �C���f�b�N�X�o�b�t�@�ւ̃|�C���^
							nullptr))) {
		return E_FAIL;
	}


	// ���_���W�̐ݒ�
	VERTEX_3D *vtx;
	vertexBuffer_->Lock(0, 0, (void**)&vtx, 0);  // ���_���̃��b�N

	vtx[0].vtx = D3DXVECTOR3(0.0f, radius_, 0.0f);
	vtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	vtx[0].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	vtx[0].tex = D3DXVECTOR2(0.0f, 0.001f);

	for (int count_y = 0; count_y < horizon_line_num; ++count_y) {
		for (int count_x = 0; count_x < vertical_line_num; ++count_x) {
			vtx[count_x + count_y * vertical_line_num + 1].vtx =
				D3DXVECTOR3(sinf(D3DX_PI * 2 / blockNumX_ * count_x) * cosf(D3DX_PI / 2 - D3DX_PI / (2 * horizon_line_num) * (count_y + 1)) * radius_,
							sinf(D3DX_PI / 2 - D3DX_PI / (2 * horizon_line_num) * (count_y + 1)) * radius_,
							cosf(D3DX_PI * 2 / blockNumX_ * count_x) * cosf(D3DX_PI / 2 - D3DX_PI / (2 * horizon_line_num) * (count_y + 1)) * radius_);
			vtx[count_x + count_y * vertical_line_num + 1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
			vtx[count_x + count_y * vertical_line_num + 1].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			vtx[count_x + count_y * vertical_line_num + 1].tex = D3DXVECTOR2(
																	(float)count_x / blockNumX_,
																	(float)count_y / blockNumY_);
		}
	}
	
	vertexBuffer_->Unlock();  // ���_���̃A�����b�N



	// �C���f�b�N�X�o�b�t�@�̐ݒ�
	WORD *index;
	indexBuffer_->Lock(0, 0, (void**)&index, 0);  // �C���f�b�N�X���̃��b�N

	const int vtx_id_begined = blockNumX_ + 1; // �J�n���_ID
	int even_number_count = 0;  // ������p�J�E���^���[�N
	int odd_number_count = 0;  // ���p�J�E���^���[�N
	int turn_count = 0;  // �܂�Ԃ��񐔃J�E���^���[�N
	for (int count_y = 0; count_y < blockNumY_; ++count_y) {
		for (int count_x = 0; count_x < vertical_line_num*2; ++count_x) {
			if (count_x % 2 == 0) {  // ������
				index[count_x + count_y * vertical_line_num * 2 + turn_count * 2] =
					vtx_id_begined + even_number_count + 1;  // �J�n�ʒu���������炷
				++even_number_count;
			} else {  // ���
				index[count_x + count_y * vertical_line_num * 2 + turn_count * 2] =
					odd_number_count + 1;  // ����[0]���������炷
				++odd_number_count;
			}
			// �܂�Ԃ�����
			if ((count_x + 1) == vertical_line_num*2  // ���ݒ肵�I���
				&& count_y < turn_num) {  // ���A�܂�Ԃ��񐔂𒴂��Ă��Ȃ����
				index[count_x + count_y * vertical_line_num*2 + turn_count*2 + 1] =
					(odd_number_count - 1) + 1;  // �k�ރ|���S����2���
				index[count_x + count_y * vertical_line_num*2 + turn_count*2 + 2] =
					vtx_id_begined + even_number_count + 1;  // �k�ރ|���S���������2���
				++turn_count;
			}
		}
	}

	indexBuffer_->Unlock();  // �C���f�b�N�X���̃A�����b�N


	// �e�N�X�`���̓ǂݍ���
	SetTexture("Resource/Texture/Game/Skydome000.jpg");


	return S_OK;

}

//=============================================================================
// �X�V����
//=============================================================================
void MeshDome::Update()
{
	// ��]
	rotation_.y += 0.0001f;
	if (D3DX_PI < rotation_.y) {
		rotation_.y -= D3DX_PI * 2;
	}

	// �ړ�
	Camera *camera = Manager::GetInstance()->GetCameraManager()->GetCamera();
	D3DXVECTOR3 pos = camera->GetPosition();
	position_.x = pos.x;
	position_.z = pos.z;
}

//=============================================================================
// �`�揈��
//=============================================================================
void MeshDome::Draw()
{
	Renderer *renderer = Manager::GetInstance()->GetRenderer();
	LPDIRECT3DDEVICE9 device = renderer->GetDevice();
	D3DXMATRIX mtxScl, mtxRot, mtxTranslate;  // �傫��, ��], �ʒu�̍s��

	// ���[���h�}�g���b�N�X�̐ݒ�
	D3DXMatrixIdentity(&worldMatrix_);  // �P�ʍs��ŏ�����

	// �n�ʂ̃X�P�[���𔽉f
	D3DXMatrixScaling(&mtxScl, scale_.x, scale_.y, scale_.z);
	D3DXMatrixMultiply(&worldMatrix_, &worldMatrix_, &mtxScl);  // �s��̂������킹
	// �n�ʂ̉�]�𔽉f(y, x, z)
	D3DXMatrixRotationYawPitchRoll(&mtxRot, rotation_.y, rotation_.x, rotation_.z);
	D3DXMatrixMultiply(&worldMatrix_, &worldMatrix_, &mtxRot);  // �s��̂������킹
	// �n�ʂ̈ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTranslate, position_.x, position_.y, position_.z);
	D3DXMatrixMultiply(&worldMatrix_, &worldMatrix_, &mtxTranslate);  // �s��̂������킹
	
	device->SetTransform(D3DTS_WORLD, &worldMatrix_);  // �s��̐ݒ�

	// ���C�g�𖳌��ɂ���
	device->SetRenderState(D3DRS_LIGHTING, FALSE);
	// Z�o�b�t�@���g�p���Ȃ�
	device->SetRenderState(D3DRS_ZENABLE, FALSE);
	// �t�H�O���g�p���Ȃ�
    device->SetRenderState(D3DRS_FOGENABLE, FALSE);



	// 3D�|���S���̕`��
	device->SetStreamSource(0, vertexBuffer_, 0, sizeof(VERTEX_3D));  // ���_�o�b�t�@���f�[�^�X�g���[���Ƀo�C���h
	device->SetIndices(indexBuffer_);  // �C���f�b�N�X�o�b�t�@���o�C���h
	device->SetFVF(FVF_VERTEX_3D);  // ���_�t�H�[�}�b�g�̐ݒ�

	device->SetTexture(0, texture_);  // �e�N�X�`���̐ݒ�

	device->SetRenderState(D3DRS_CULLMODE, D3DCULL_CW);
	device->DrawPrimitive(D3DPT_TRIANGLEFAN, 0, blockNumX_);  // �|���S���i�t�@���j�̕`��
	device->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);

	device->DrawIndexedPrimitive(
		D3DPT_TRIANGLESTRIP,
		0, 0, vertexNum_, 0, polygonNum_);


	// ���C�g��L���ɂ���
	device->SetRenderState(D3DRS_LIGHTING, TRUE);
	// Z�o�b�t�@���g�p����
	device->SetRenderState(D3DRS_ZENABLE, TRUE);
	// �t�H�O���g�p����
    device->SetRenderState(D3DRS_FOGENABLE, TRUE);

}

//=========================================================================
// ��������
//========================================================================
MeshDome *MeshDome::Create(D3DXVECTOR3 pos,
	int block_num_x, int block_num_y,
	float radius)
{
	// ����
	MeshDome *dome = new MeshDome();
	// ������
	dome->Init(pos, block_num_x, block_num_y, radius);


	return dome;
}


// End Of File