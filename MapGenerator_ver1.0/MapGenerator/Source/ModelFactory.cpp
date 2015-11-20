//=============================================================================
//
// ���f���t�@�N�g�� [ModelFactory.cpp]
// Author : KEITA OHUCHI
//
//=============================================================================

#include "ModelFactory.h"
#include "Manager.h"
#include "Renderer.h"


//=========================================================================
// �R���X�g���N�^
//=========================================================================
ModelFactory::ModelFactory()
{
}

//=========================================================================
// �f�X�g���N�^
//=========================================================================
ModelFactory::~ModelFactory()
{

	// ���f���|�C���^�̉��
	for (auto itr = modelMap_.begin(); itr != modelMap_.end(); ++itr) {
		// �������
		SafeDelete(itr->second);
	}
	modelMap_.clear();

}



//=========================================================================
// ���f���̓ǂݍ���
//=========================================================================
int ModelFactory::ImportModel(std::string xFilePath)
{

	// ���łɂ��邩�ǂ����`�F�b�N
	if (modelMap_.find(xFilePath) == modelMap_.end()) {
		// ���f������
		modelMap_[xFilePath] = Model::Create(xFilePath.c_str());
		return 1;
	} else {
		return 0;
	}

}


//=========================================================================
// ���f���|�C���^�̎擾
//=========================================================================
Model *ModelFactory::GetModel(std::string xFilePath)
{

	// ���łɂ��邩�ǂ����`�F�b�N
	if (modelMap_.find(xFilePath) == modelMap_.end()) {
		// ���f������
		modelMap_[xFilePath] = Model::Create(xFilePath.c_str());
	}

	return modelMap_[xFilePath];

}


// End of file