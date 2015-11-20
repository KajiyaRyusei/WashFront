//=============================================================================
//
// ���f���N���X [Model.h]
// Author : KEITA OHUCHI
//
//=============================================================================

#include "Model.h"
#include "Manager.h"
#include "Renderer.h"
#include "TextureFactory.h"


//=========================================================================
// �R���X�g���N�^
//=========================================================================
Model::Model()
{

	texture_ = nullptr;
	materialBuffer_ = nullptr;
	materialNum_ = 0;
	mesh_ = nullptr;
	filePath_ = nullptr;

}

//=========================================================================
// �f�X�g���N�^
//=========================================================================
Model::~Model()
{

	// �}�e���A���o�b�t�@�̊J������
	SafeRelease(materialBuffer_);
	// ���b�V���̊J������
	SafeRelease(mesh_);
	// �e�N�X�`���̊J������
	SafeDelete(texture_);

}


//=========================================================================
// ����������
//=========================================================================
bool Model::Init(LPCSTR xFileName)
{

	filePath_ = xFileName;


	// X�t�@�C���̓ǂݍ���
	if (FAILED(D3DXLoadMeshFromX(
			xFileName,
			D3DXMESH_SYSTEMMEM,
			Manager::GetInstance()->GetRenderer()->GetDevice(),
			nullptr,
			&materialBuffer_,
			nullptr,
			&materialNum_,
			&mesh_))) {
		return false;
	}


	// �e�N�X�`���֘A
	texture_ = new LPDIRECT3DTEXTURE9[materialNum_];
	D3DXMATERIAL *pD3DXMat = nullptr;
	pD3DXMat = (D3DXMATERIAL*)materialBuffer_->GetBufferPointer();

	for (int count = 0; count < (int)materialNum_; ++count) {
		// �e�N�X�`���|�C���^�̏�����
		texture_[count] = nullptr;
		// �g�p���Ă���e�N�X�`��������Γǂݍ���
		if (pD3DXMat[count].pTextureFilename != nullptr && lstrlen(pD3DXMat[count].pTextureFilename) > 0) {
			// �e�N�X�`���̎擾
			// texture_[count] = Manager::GetInstance()->GetTextureFactory()->GetTexture(pD3DXMat[count].pTextureFilename);
		}
	}


	return true;

}

//=========================================================================
// �`�揈��
//=========================================================================
void Model::Draw()
{

	LPDIRECT3DDEVICE9 device = Manager::GetInstance()->GetRenderer()->GetDevice();
	D3DXMATERIAL *material;
	D3DMATERIAL9 materialDefault;

	// �}�e���A���̎��o��
	device->GetMaterial(&materialDefault);
	material = (D3DXMATERIAL *)materialBuffer_->GetBufferPointer();


	for (int count = 0; static_cast<unsigned>(count) < materialNum_; ++count) {
		// �}�e���A���̐ݒ�
		device->SetMaterial(&material[count].MatD3D);
		// �e�N�X�`���̐ݒ�
		device->SetTexture(0, texture_[count]);
		// �`��
		mesh_->DrawSubset(count);
	}

	device->SetTexture(0, nullptr);
	device->SetMaterial(&materialDefault);

}

//=========================================================================
// ��������
//=========================================================================
Model* Model::Create(LPCSTR xFileName)
{

	Model *model = nullptr;
	model = new Model();
	model->Init(xFileName);


	return model;

}


// End of file