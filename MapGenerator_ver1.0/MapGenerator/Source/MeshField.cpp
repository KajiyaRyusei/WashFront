//=============================================================================
//
// ���b�V���t�B�[���h [MeshField.cpp]
// Author : KEITA OHUCHI
//
//=============================================================================

#include "Main.h"
#include "Manager.h"
#include "Renderer.h"
#include "MeshField.h"
#include <stdio.h>


//-----------------------------------------------------------------------------
// �}�N����`
//-----------------------------------------------------------------------------
// ���̍��W
#define EDGE_POS_X (-blockSizeX_ * blockNumX_ / 2.0f)
#define EDGE_POS_Z (blockSizeZ_ * blockNumZ_ / 2.0f)

// �F
#define TOP_DIFFUSE_COLOR (D3DXCOLOR(0.40f, 0.62f, 0.23f, 1.0f))
#define BOTTOM_DIFFUSE_COLOR (D3DXCOLOR(0.41f, 0.36f, 0.31f, 1.0f))
// �F�̐ݒ�p�̍���
#define TOP_HEIGHT		(13.0f)
#define BOTTOM_HEIGHT	(0.0f)


//=============================================================================
// �R���X�g���N�^
//=============================================================================
MeshField::MeshField(int priority) : Scene3D(priority)
{
	// �����o�ϐ��̏�����
	indexBuffer_ = nullptr;
	indexNum_ = 0;
	vertexNum_ = 0;
	polygonNum_ = 0;
	blockNumX_ = 0;
	blockNumZ_ = 0;
	blockSizeX_ = 0.0f;
	blockSizeZ_ = 0.0f;
	faceNormal_ = nullptr;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
MeshField::~MeshField()
{

	// �|�C���^�ϐ��̉��
	SafeRelease(indexBuffer_);
	SafeDelete(faceNormal_);

}


//=============================================================================
// ����������
//=============================================================================
HRESULT MeshField::Init(int block_num_x, int block_num_z,
	float block_size_x, float block_size_z,
	D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	Renderer *renderer = Manager::GetInstance()->GetRenderer();
	LPDIRECT3DDEVICE9 device = renderer->GetDevice();

	// �����ɂ��ϐ��̏�����
	blockNumX_ = block_num_x;
	blockNumZ_ = block_num_z;
	blockSizeX_ = block_size_x;
	blockSizeZ_ = block_size_z;
	position_ = pos;
	rotation_ = rot;

	// �|���S���̕`��ɕK�v�ȕϐ��̏�����
	const int vertical_line_num = blockNumX_ + 1;  // �u���b�N���������߂ɕK�v�Ȑ������̖{��
	const int horizon_line_num = blockNumZ_ + 1;  // �u���b�N���������߂ɕK�v�Ȑ������̖{��
	const int turn_num = blockNumZ_ - 1;  // �܂�Ԃ���
	indexNum_ = vertical_line_num * blockNumZ_ * 2 + turn_num * 2;
	vertexNum_ = vertical_line_num * horizon_line_num;
	polygonNum_ = (blockNumX_ * blockNumZ_) * 2 + turn_num * 4;

	// ���_�o�b�t�@�̐���
	if (FAILED(device->CreateVertexBuffer(
							sizeof(VERTEX_3D) * vertexNum_,  // �m�ۂ��郁�����̃T�C�Y
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


	// �����}�b�v�̐���
	/*
	float *height_map = new float[vertexNum_];
	memset(height_map, nullptr, sizeof(float *) * vertexNum_);
	CreateHeightMap(height_map);
	*/

	// ���_���W�̐ݒ�
	VERTEX_3D *pVtx;
	vertexBuffer_->Lock(0, 0, (void**)&pVtx, 0);  // ���_���̃��b�N
	
	// ���_���̕ۑ�
	float height = rand() % 100 * 0.01f + 0.5f;
	float offset = rand() % 314 * 0.01f;
	for (int count_z = 0; count_z < horizon_line_num; ++count_z) {
		for (int count_x = 0; count_x < vertical_line_num; ++count_x) {
			float x, z;
			x = pVtx[count_x + count_z * vertical_line_num].vtx.x = EDGE_POS_X + blockSizeX_ * count_x;
			z = pVtx[count_x + count_z * vertical_line_num].vtx.z = EDGE_POS_Z - blockSizeZ_ * count_z;
			x -= EDGE_POS_X;
			z -= EDGE_POS_Z;
			float length = sqrtf(x * x + z * z);
			pVtx[count_x + count_z * vertical_line_num].vtx.y = 0.0f;
			//pVtx[count_x + count_z * vertical_line_num].vtx.y = sinf(length * 0.3f + offset) * height;
			pVtx[count_x + count_z * vertical_line_num].diffuse = TOP_DIFFUSE_COLOR;
			pVtx[count_x + count_z * vertical_line_num].tex = D3DXVECTOR2((float)count_x, (float)count_z);
		}
		if ((count_z / 40) % 2) {
			height += rand() % 10 * 0.01f + 0.05f;
		} else {
			height -= rand() % 10 * 0.01f + 0.05f;
		}
	}

	// �����}�b�v�̉��
	//delete[] height_map;

	// �ʂ̖@�����i�[���[�N���m��
	faceNormal_ = new D3DXVECTOR3[blockNumX_ * 2 * blockNumZ_];

	// �ʂ̖@�����̕ۑ�
	for (int count_z = 0; count_z < blockNumZ_; ++count_z) {
		for (int count_x = 0; count_x < blockNumX_; ++count_x) {
			D3DXVECTOR3 vec0, vec1, vecN, nor;
			// �ʂ��\������x�N�g���̌v�Z
			vec0 = pVtx[count_x + count_z * vertical_line_num].vtx
					- pVtx[count_x + (count_z + 1) * vertical_line_num].vtx;
			vec1 = pVtx[count_x + (count_z + 1) * vertical_line_num + 1].vtx
					- pVtx[count_x + (count_z + 1) * vertical_line_num].vtx;
			// �O�ςŖ@���̌������v�Z
			D3DXVec3Cross(&vecN, &vec0, &vec1);
			// �@���̌����̃x�N�g���𐳋K��
			D3DXVec3Normalize(&nor, &vecN);
			// �@������ۑ�
			faceNormal_[count_z * blockNumX_ * 2 + count_x * 2] = nor;

			// �ʂ��\������x�N�g���̌v�Z
			vec0 = pVtx[count_x + (count_z + 1) * vertical_line_num + 1].vtx
					- pVtx[count_x + count_z * vertical_line_num + 1].vtx;
			vec1 = pVtx[count_x + count_z * vertical_line_num].vtx
					- pVtx[count_x + count_z * vertical_line_num + 1].vtx;
			// �O�ςŖ@���̌������v�Z
			D3DXVec3Cross(&vecN, &vec0, &vec1);
			// �@���̌����̃x�N�g���𐳋K��
			D3DXVec3Normalize(&nor, &vecN);
			// �@������ۑ�
			faceNormal_[count_z * blockNumX_ * 2 + count_x * 2 + 1] = nor;
		}
	}

	// ���_�̖@�����̕ۑ�
	for (int count_z = 0; count_z < horizon_line_num; ++count_z) {
		for (int count_x = 0; count_x < vertical_line_num; ++count_x) {
			D3DXVECTOR3 nor;
			// ����
			if (count_x == 0 && count_z == 0) {
				nor = (faceNormal_[0] + faceNormal_[1]) * 0.5f;
				D3DXVec3Normalize(&nor, &nor);
				pVtx[count_x + count_z * vertical_line_num].nor = nor;
			// ����
			} else if (count_x == 0 && count_z == horizon_line_num - 1) {
				pVtx[count_x + count_z * vertical_line_num].nor =
					faceNormal_[(blockNumZ_ - 1) * (blockNumX_ * 2)];
			// �E��
			} else if (count_x == vertical_line_num - 1 && count_z == 0) {
				pVtx[count_x + count_z * vertical_line_num].nor =
					faceNormal_[blockNumX_ * 2 - 1];
			// �E��
			} else if (count_x == vertical_line_num - 1 && count_z == horizon_line_num - 1) {
				nor = (faceNormal_[(blockNumZ_ - 1) * (blockNumX_ * 2) + blockNumX_ * 2 - 2]
						+ faceNormal_[(blockNumZ_ - 1) * (blockNumX_ * 2) + blockNumX_ * 2 - 1]) * 0.5f;
				D3DXVec3Normalize(&nor, &nor);
				pVtx[count_x + count_z * vertical_line_num].nor = nor;
			// ��[
			} else if (0 < count_x && count_x < vertical_line_num - 1
				&& count_z == 0) {
				
				nor = faceNormal_[count_x * 2 - 1] + (faceNormal_[count_x * 2] + faceNormal_[count_x * 2 + 1]) * 0.5f;
				D3DXVec3Normalize(&nor, &nor);
				pVtx[count_x + count_z * vertical_line_num].nor = nor;
			// ���[
			} else if (0 < count_x && count_x < vertical_line_num - 1
				&& count_z == horizon_line_num - 1) {
				
				nor = (faceNormal_[(blockNumZ_ - 1) * (blockNumX_ * 2) + count_x * 2 - 1]
						+ faceNormal_[(blockNumZ_ - 1) * (blockNumX_ * 2) + count_x * 2]) * 0.5f
							+ faceNormal_[(blockNumZ_ - 1) * (blockNumX_ * 2) + count_x * 2 + 1];
				D3DXVec3Normalize(&nor, &nor);
				pVtx[count_x + count_z * vertical_line_num].nor = nor;
			// ���[
			} else if (count_x == 0
				&& 0 < count_z && count_z < horizon_line_num - 1) {
				
				nor = faceNormal_[(count_z - 1) * (blockNumX_ * 2)]
						+ (faceNormal_[count_z * (blockNumX_ * 2)]
							+ faceNormal_[count_z * (blockNumX_ * 2) + 1]) * 0.5f;
				D3DXVec3Normalize(&nor, &nor);
				pVtx[count_x + count_z * vertical_line_num].nor = nor;
			// �E�[
			} else if (count_x == vertical_line_num - 1
				&& 0 < count_z && count_z < horizon_line_num - 1) {
				
				nor = (faceNormal_[(count_z - 1) * (blockNumX_ * 2) + blockNumX_ * 2 - 2]
						+ faceNormal_[(count_z - 1) * (blockNumX_ * 2) + blockNumX_ * 2 - 1]) * 0.5f
							+ faceNormal_[count_z * (blockNumX_ * 2) + blockNumX_ * 2 - 1];
				D3DXVec3Normalize(&nor, &nor);
				pVtx[count_x + count_z * vertical_line_num].nor = nor;
			// �����̖@��
			} else {
				nor = (faceNormal_[(count_z - 1) * (blockNumX_ * 2) + count_x * 2 - 2]
						+ faceNormal_[(count_z - 1) * (blockNumX_ * 2) + count_x * 2 - 1]) * 0.5f
							+ faceNormal_[(count_z - 1) * (blockNumX_ * 2) + count_x * 2]
								+ faceNormal_[count_z * (blockNumX_ * 2) + count_x * 2 - 1]
									+ (faceNormal_[count_z * (blockNumX_ * 2) + count_x * 2]
										+ faceNormal_[count_z * (blockNumX_ * 2) + count_x * 2 + 1]) * 0.5f;
				D3DXVec3Normalize(&nor, &nor);
				pVtx[count_x + count_z * vertical_line_num].nor = nor;
			}
		}
	}
	
	vertexBuffer_->Unlock();  // ���_���̃A�����b�N


	// �C���f�b�N�X�o�b�t�@�̐ݒ�
	WORD *pIndex;
	indexBuffer_->Lock(0, 0, (void**)&pIndex, 0);  // �C���f�b�N�X���̃��b�N

	const int vtx_id_begined = blockNumX_ + 1; // �J�n���_ID
	int even_nucounter_ = 0;  // ������p�J�E���^���[�N
	int odd_nucounter_ = 0;  // ���p�J�E���^���[�N
	int turn_count = 0;  // �܂�Ԃ��񐔃J�E���^���[�N

	for (int count_z = 0; count_z < blockNumZ_; ++count_z) {
		for (int count_x = 0; count_x < vertical_line_num*2; ++count_x) {
			if (count_x % 2 == 0) {  // ������
				pIndex[count_x + count_z * vertical_line_num * 2 + turn_count * 2] =
					vtx_id_begined + even_nucounter_;  // �J�n�ʒu���������炷
				++even_nucounter_;
			} else {  // ���
				pIndex[count_x + count_z * vertical_line_num * 2 + turn_count * 2] =
					odd_nucounter_;  // ����[0]���������炷
				++odd_nucounter_;
			}

			// �܂�Ԃ�����
			if ((count_x + 1) == vertical_line_num * 2  // ���ݒ肵�I���
				&& count_z < turn_num) {  // ���A�܂�Ԃ��񐔂𒴂��Ă��Ȃ����
				pIndex[count_x + count_z * vertical_line_num * 2 + turn_count*2 + 1] =
					(odd_nucounter_ - 1);  // �k�ރ|���S����2���
				pIndex[count_x + count_z * vertical_line_num * 2 + turn_count*2 + 2] =
					vtx_id_begined + even_nucounter_;  // �k�ރ|���S���������2���
				++turn_count;
			}
		}
	}

	indexBuffer_->Unlock();  // �C���f�b�N�X���̃A�����b�N

	// �e�N�X�`���̓ǂݍ���
	//SetTexture("Resource/Texture/Game/Field.jpg");


	return S_OK;
}


HRESULT MeshField::Init(char *fileName, D3DXVECTOR3 position, D3DXVECTOR3 rotation)
{
	Renderer *renderer = Manager::GetInstance()->GetRenderer();
	LPDIRECT3DDEVICE9 device = renderer->GetDevice();

	int block_num_x, block_num_z;
	float block_size_x, block_size_z;
	float *height_map;

	FILE *file = fopen(fileName, "rb");
	fread(&block_num_x, sizeof(int), 1, file);
	fread(&block_num_z, sizeof(int), 1, file);
	fread(&block_size_x, sizeof(float), 1, file);
	fread(&block_size_z, sizeof(float), 1, file);

	// �����ɂ��ϐ��̏�����
	blockNumX_ = block_num_x;
	blockNumZ_ = block_num_z;
	blockSizeX_ = block_size_x;
	blockSizeZ_ = block_size_z;
	position_ = position;
	rotation_ = rotation;

	// �|���S���̕`��ɕK�v�ȕϐ��̏�����
	const int vertical_line_num = blockNumX_ + 1;  // �u���b�N���������߂ɕK�v�Ȑ������̖{��
	const int horizon_line_num = blockNumZ_ + 1;  // �u���b�N���������߂ɕK�v�Ȑ������̖{��
	const int turn_num = blockNumZ_ - 1;  // �܂�Ԃ���
	indexNum_ = vertical_line_num * blockNumZ_ * 2 + turn_num * 2;
	vertexNum_ = vertical_line_num * horizon_line_num;
	polygonNum_ = (blockNumX_ * blockNumZ_) * 2 + turn_num * 4;

	height_map = new float[vertexNum_];
	fread(height_map, sizeof(float), vertexNum_, file);

	fclose(file);

	// ���_�o�b�t�@�̐���
	if (FAILED(device->CreateVertexBuffer(
							sizeof(VERTEX_3D) * vertexNum_,  // �m�ۂ��郁�����̃T�C�Y
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


	D3DXCOLOR topColor = TOP_DIFFUSE_COLOR;
	D3DXCOLOR bottomColor = BOTTOM_DIFFUSE_COLOR;
	float y = 0;


	// ���_���W�̐ݒ�
	VERTEX_3D *pVtx;
	vertexBuffer_->Lock(0, 0, (void**)&pVtx, 0);  // ���_���̃��b�N
	
	// ���_���̕ۑ�
	float height = rand() % 100 * 0.01f + 0.5f;
	float offset = rand() % 314 * 0.01f;
	for (int count_z = 0; count_z < horizon_line_num; ++count_z) {
		for (int count_x = 0; count_x < vertical_line_num; ++count_x) {
			pVtx[count_x + count_z * vertical_line_num].vtx.x = EDGE_POS_X + blockSizeX_ * count_x;
			pVtx[count_x + count_z * vertical_line_num].vtx.z = EDGE_POS_Z - blockSizeZ_ * count_z;
			y = pVtx[count_x + count_z * vertical_line_num].vtx.y = height_map[count_x + count_z * vertical_line_num];
			if (y < 0) {
				y = 0;
			} else if (TOP_HEIGHT < y) {
				y = TOP_HEIGHT;
			}
			D3DXCOLOR color = topColor * (y / TOP_HEIGHT) + bottomColor * (1.0f - y / TOP_HEIGHT);
			pVtx[count_x + count_z * vertical_line_num].diffuse = color;
			//pVtx[count_x + count_z * vertical_line_num].diffuse = TOP_DIFFUSE_COLOR;
			pVtx[count_x + count_z * vertical_line_num].tex = D3DXVECTOR2((float)count_x / 5.0f, (float)count_z / 5.0f);
		}
		if ((count_z / 40) % 2) {
			height += rand() % 10 * 0.01f + 0.05f;
		} else {
			height -= rand() % 10 * 0.01f + 0.05f;
		}
	}

	delete[] height_map;


	// �ʂ̖@�����i�[���[�N���m��
	faceNormal_ = new D3DXVECTOR3[blockNumX_ * 2 * blockNumZ_];

	// �ʂ̖@�����̕ۑ�
	for (int count_z = 0; count_z < blockNumZ_; ++count_z) {
		for (int count_x = 0; count_x < blockNumX_; ++count_x) {
			D3DXVECTOR3 vec0, vec1, vecN, nor;
			// �ʂ��\������x�N�g���̌v�Z
			vec0 = pVtx[count_x + count_z * vertical_line_num].vtx
					- pVtx[count_x + (count_z + 1) * vertical_line_num].vtx;
			vec1 = pVtx[count_x + (count_z + 1) * vertical_line_num + 1].vtx
					- pVtx[count_x + (count_z + 1) * vertical_line_num].vtx;
			// �O�ςŖ@���̌������v�Z
			D3DXVec3Cross(&vecN, &vec0, &vec1);
			// �@���̌����̃x�N�g���𐳋K��
			D3DXVec3Normalize(&nor, &vecN);
			// �@������ۑ�
			faceNormal_[count_z * blockNumX_ * 2 + count_x * 2] = nor;

			// �ʂ��\������x�N�g���̌v�Z
			vec0 = pVtx[count_x + (count_z + 1) * vertical_line_num + 1].vtx
					- pVtx[count_x + count_z * vertical_line_num + 1].vtx;
			vec1 = pVtx[count_x + count_z * vertical_line_num].vtx
					- pVtx[count_x + count_z * vertical_line_num + 1].vtx;
			// �O�ςŖ@���̌������v�Z
			D3DXVec3Cross(&vecN, &vec0, &vec1);
			// �@���̌����̃x�N�g���𐳋K��
			D3DXVec3Normalize(&nor, &vecN);
			// �@������ۑ�
			faceNormal_[count_z * blockNumX_ * 2 + count_x * 2 + 1] = nor;
		}
	}
	

	// ���_�̖@�����̕ۑ�
	for (int count_z = 0; count_z < horizon_line_num; ++count_z) {
		for (int count_x = 0; count_x < vertical_line_num; ++count_x) {
			D3DXVECTOR3 nor;
			// ����
			if (count_x == 0 && count_z == 0) {
				nor = (faceNormal_[0] + faceNormal_[1]) * 0.5f;
				D3DXVec3Normalize(&nor, &nor);
				pVtx[count_x + count_z * vertical_line_num].nor = nor;
			// ����
			} else if (count_x == 0 && count_z == horizon_line_num - 1) {
				pVtx[count_x + count_z * vertical_line_num].nor =
					faceNormal_[(blockNumZ_ - 1) * (blockNumX_ * 2)];
			// �E��
			} else if (count_x == vertical_line_num - 1 && count_z == 0) {
				pVtx[count_x + count_z * vertical_line_num].nor =
					faceNormal_[blockNumX_ * 2 - 1];
			// �E��
			} else if (count_x == vertical_line_num - 1 && count_z == horizon_line_num - 1) {
				nor = (faceNormal_[(blockNumZ_ - 1) * (blockNumX_ * 2) + blockNumX_ * 2 - 2]
						+ faceNormal_[(blockNumZ_ - 1) * (blockNumX_ * 2) + blockNumX_ * 2 - 1]) * 0.5f;
				D3DXVec3Normalize(&nor, &nor);
				pVtx[count_x + count_z * vertical_line_num].nor = nor;
			// ��[
			} else if (0 < count_x && count_x < vertical_line_num - 1
				&& count_z == 0) {
				
				nor = faceNormal_[count_x * 2 - 1] + (faceNormal_[count_x * 2] + faceNormal_[count_x * 2 + 1]) * 0.5f;
				D3DXVec3Normalize(&nor, &nor);
				pVtx[count_x + count_z * vertical_line_num].nor = nor;
			// ���[
			} else if (0 < count_x && count_x < vertical_line_num - 1
				&& count_z == horizon_line_num - 1) {

				nor = (faceNormal_[(blockNumZ_ - 1) * (blockNumX_ * 2) + count_x * 2 - 1]
						+ faceNormal_[(blockNumZ_ - 1) * (blockNumX_ * 2) + count_x * 2]) * 0.5f
							+ faceNormal_[(blockNumZ_ - 1) * (blockNumX_ * 2) + count_x * 2 + 1];
				D3DXVec3Normalize(&nor, &nor);
				pVtx[count_x + count_z * vertical_line_num].nor = nor;
			// ���[
			} else if (count_x == 0 && 0 < count_z && count_z < horizon_line_num - 1) {
				nor = faceNormal_[(count_z - 1) * (blockNumX_ * 2)]
						+ (faceNormal_[count_z * (blockNumX_ * 2)]
							+ faceNormal_[count_z * (blockNumX_ * 2) + 1]) * 0.5f;
				D3DXVec3Normalize(&nor, &nor);
				pVtx[count_x + count_z * vertical_line_num].nor = nor;
			// �E�[
			} else if (count_x == vertical_line_num - 1
				&& 0 < count_z && count_z < horizon_line_num - 1) {

				nor = (faceNormal_[(count_z - 1) * (blockNumX_ * 2) + blockNumX_ * 2 - 2]
						+ faceNormal_[(count_z - 1) * (blockNumX_ * 2) + blockNumX_ * 2 - 1]) * 0.5f
							+ faceNormal_[count_z * (blockNumX_ * 2) + blockNumX_ * 2 - 1];
				D3DXVec3Normalize(&nor, &nor);
				pVtx[count_x + count_z * vertical_line_num].nor = nor;
			// �����̖@��
			} else {
				nor = (faceNormal_[(count_z - 1) * (blockNumX_ * 2) + count_x * 2 - 2]
						+ faceNormal_[(count_z - 1) * (blockNumX_ * 2) + count_x * 2 - 1]) * 0.5f
							+ faceNormal_[(count_z - 1) * (blockNumX_ * 2) + count_x * 2]
								+ faceNormal_[count_z * (blockNumX_ * 2) + count_x * 2 - 1]
									+ (faceNormal_[count_z * (blockNumX_ * 2) + count_x * 2]
										+ faceNormal_[count_z * (blockNumX_ * 2) + count_x * 2 + 1]) * 0.5f;
				D3DXVec3Normalize(&nor, &nor);
				pVtx[count_x + count_z * vertical_line_num].nor = nor;
			}
		}
	}
	
	vertexBuffer_->Unlock();  // ���_���̃A�����b�N



	// �C���f�b�N�X�o�b�t�@�̐ݒ�
	WORD *pIndex;

	indexBuffer_->Lock(0, 0, (void**)&pIndex, 0);  // �C���f�b�N�X���̃��b�N

	const int vtx_id_begined = blockNumX_ + 1; // �J�n���_ID
	int even_nucounter_ = 0;  // ������p�J�E���^���[�N
	int odd_nucounter_ = 0;  // ���p�J�E���^���[�N
	int turn_count = 0;  // �܂�Ԃ��񐔃J�E���^���[�N

	for (int count_z = 0; count_z < blockNumZ_; ++count_z) {
		for (int count_x = 0; count_x < vertical_line_num*2; ++count_x) {
			if (count_x % 2 == 0) {  // ������
				pIndex[count_x + count_z * vertical_line_num * 2 + turn_count * 2] =
					vtx_id_begined + even_nucounter_;  // �J�n�ʒu���������炷
				++even_nucounter_;
			} else {  // ���
				pIndex[count_x + count_z * vertical_line_num * 2 + turn_count * 2] =
					odd_nucounter_;  // ����[0]���������炷
				++odd_nucounter_;
			}

			// �܂�Ԃ�����
			if ((count_x + 1) == vertical_line_num * 2  // ���ݒ肵�I���
				&& count_z < turn_num) {  // ���A�܂�Ԃ��񐔂𒴂��Ă��Ȃ����
				pIndex[count_x + count_z * vertical_line_num * 2 + turn_count*2 + 1] =
					(odd_nucounter_ - 1);  // �k�ރ|���S����2���
				pIndex[count_x + count_z * vertical_line_num * 2 + turn_count*2 + 2] =
					vtx_id_begined + even_nucounter_;  // �k�ރ|���S���������2���
				++turn_count;
			}
		}
	}

	indexBuffer_->Unlock();  // �C���f�b�N�X���̃A�����b�N


	return S_OK;
}

//=============================================================================
// �X�V����
//=============================================================================
void MeshField::Update()
{
}

//=============================================================================
// �`�揉��
//=============================================================================
void MeshField::Draw()
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

	// 3D�|���S���̕`��
	device->SetStreamSource(0, vertexBuffer_, 0, sizeof(VERTEX_3D));  // ���_�o�b�t�@���f�[�^�X�g���[���Ƀo�C���h
	device->SetIndices(indexBuffer_);  // �C���f�b�N�X�o�b�t�@���o�C���h
	device->SetFVF(FVF_VERTEX_3D);  // ���_�t�H�[�}�b�g�̐ݒ�
	device->SetTexture(0, texture_);  // �e�N�X�`���̐ݒ�
	device->DrawIndexedPrimitive(
		D3DPT_TRIANGLESTRIP,
		0, 0, vertexNum_, 0, polygonNum_);
}

//=========================================================================
// ��������
//=========================================================================
MeshField *MeshField::Create(int block_num_x, int block_num_z,
	float block_size_x, float block_size_z,
	D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	// ����
	MeshField * field = new MeshField();
	// ������
	field->Init(block_num_x, block_num_z,
				block_size_x, block_size_z,
				pos, rot);


	return field;
}

MeshField *MeshField::Create(char *fileName, D3DXVECTOR3 position, D3DXVECTOR3 rotation)
{
	// ����
	MeshField *field = new MeshField();
	// ������
	field->Init(fileName, position, rotation);


	return field;
}


//=========================================================================
// �����}�b�v��������
//=========================================================================
void MeshField::CreateHeightMap(float *map)
{
}

//=========================================================================
// �v���C���[��y���W�����߂鏈��
//=========================================================================
float MeshField::GetHeight(D3DXVECTOR3 pos)
{
	D3DXVECTOR3 pos0, pos1, pos2, pos3;
	D3DXVECTOR3 vec0, vec1, vec2;
	D3DXVECTOR3 vec_p0, vec_p1, vec_p2;
	float height = 0;
	VERTEX_3D *vtx;
	
	//D3DXMATRIX mtx;
	//D3DXMatrixIdentity(&mtx);
	//D3DXMatrixRotationYawPitchRoll(&mtx, rotation_.y, rotation_.x, rotation_.z);

	int	x,	z;
	// �O���b�h�̎w�W�𒊏o
	x = (int)((pos.x - EDGE_POS_X) / blockSizeX_);
	z = (int)((pos.z - EDGE_POS_Z) / blockSizeZ_);
	if (x < 0) {
		x = -x;
	}
	if (z < 0) {
		z = -z;
	}
	
	// ���_���̃��b�N
	vertexBuffer_->Lock(0, 0, (void**)&vtx, 0);
			
	pos0 = vtx[x + (z + 1) * (blockNumX_ + 1)].vtx;
	pos1 = vtx[x + z * (blockNumX_ + 1)].vtx;
	pos2 = vtx[x + (z + 1) * (blockNumX_ + 1) + 1].vtx;
	pos3 = vtx[x + z * (blockNumX_ + 1) + 1].vtx;

	//D3DXVec3TransformCoord(&pos0, &pos0, &mtx);
	//D3DXVec3TransformCoord(&pos1, &pos1, &mtx);
	//D3DXVec3TransformCoord(&pos2, &pos2, &mtx);
	//D3DXVec3TransformCoord(&pos3, &pos3, &mtx);

	// �ꖇ�ڂ̃|���S��
	vec0 = pos1 - pos0;
	vec1 = pos2 - pos1;
	vec2 = pos0 - pos2;
	vec_p0 = pos - pos0;
	vec_p1 = pos - pos1;
	vec_p2 = pos - pos2;

	// �O�ςɂ����O����
	if ((vec0.x * vec_p0.z - vec0.z * vec_p0.x) <= 0
		&& (vec1.x * vec_p1.z - vec1.z * vec_p1.x) <= 0
		&& (vec2.x * vec_p2.z - vec2.z * vec_p2.x) <= 0) {
		D3DXVECTOR3 face_nor = faceNormal_[x * 2 + z * blockNumX_ * 2];
		//D3DXVec3TransformCoord(&face_nor, &faceNormal_[x * 2 + z * blockNumX_ * 2], &mtx);
				
		// �������擾
		height = GetHeightPolygon(pos0, pos, face_nor);

		// ���_���̃A�����b�N
		vertexBuffer_->Unlock();


		return height;
	}

	// �񖇖ڂ̃|���S��
	vec0 = pos1 - pos2;
	vec1 = pos3 - pos1;
	vec2 = pos2 - pos3;
	vec_p0 = pos - pos2;
	vec_p1 = pos - pos1;
	vec_p2 = pos - pos3;

	// �O�ςɂ����O����
	if ((vec0.x * vec_p0.z - vec0.z * vec_p0.x) <= 0
		&& (vec1.x * vec_p1.z - vec1.z * vec_p1.x) <= 0
		&& (vec2.x * vec_p2.z - vec2.z * vec_p2.x) <= 0) {
		// ��]��̖@���̌v�Z
		D3DXVECTOR3 face_nor = faceNormal_[x * 2 + z * blockNumX_ * 2 + 1];
		//D3DXVec3TransformCoord(&face_nor, &faceNormal_[x * 2 + z * blockNumX_ * 2 + 1], &mtx);

		// �������擾
		height = GetHeightPolygon(pos3, pos, face_nor);

		// ���_���̃A�����b�N
		vertexBuffer_->Unlock();


		return height;
	}

	// ���_���̃A�����b�N
	vertexBuffer_->Unlock();


	return height;
}

//=========================================================================
// �����̌v�Z����
//=========================================================================
float MeshField::GetHeightPolygon(D3DXVECTOR3 pos0, D3DXVECTOR3 pos1, D3DXVECTOR3 nor)
{
	if (nor.y) {
		float height;
		height = pos0.y - ((pos1.x - pos0.x) * nor.x + (pos1.z - pos0.z) * nor.z) / nor.y;
		return height;
	}


	return 0.0f;
}


// End of file.