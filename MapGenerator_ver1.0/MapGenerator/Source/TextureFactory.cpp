//=============================================================================
//
// �e�N�X�`���t�@�N�g�� [TextureFactory.cpp]
// Author : KEITA OHUCHI
//
//=============================================================================

#include "TextureFactory.h"
#include "Manager.h"
#include "Renderer.h"


//=========================================================================
// �R���X�g���N�^
//=========================================================================
TextureFactory::TextureFactory()
{
}

//=========================================================================
// �f�X�g���N�^
//=========================================================================
TextureFactory::~TextureFactory()
{
	
	// �e�N�X�`���|�C���^�̉��
	for (auto itr = textureMap_.begin(); itr != textureMap_.end(); ++itr) {
		// �������
		SafeRelease(itr->second);
	}
	textureMap_.clear();

}

//=========================================================================
// �e�N�X�`���̃C���|�[�g
//=========================================================================
int TextureFactory::ImportTexture(std::string texturePath)
{
	// ���łɂ��邩�ǂ����`�F�b�N
	if (textureMap_.find(texturePath) == textureMap_.end()) {
		// �e�N�X�`������
		D3DXCreateTextureFromFile(
			Manager::GetInstance()->GetRenderer()->GetDevice(),
			texturePath.c_str(),
			&textureMap_[texturePath]);
		return 1;
	} else {
		return 0;
	}

}

//=========================================================================
// �e�N�X�`���̎擾
//=========================================================================
LPDIRECT3DTEXTURE9 TextureFactory::GetTexture(std::string texturePath)
{

	// ���łɂ��邩�ǂ����`�F�b�N
	if (textureMap_.find(texturePath) == textureMap_.end()) {
		// �e�N�X�`������
		D3DXCreateTextureFromFile(
			Manager::GetInstance()->GetRenderer()->GetDevice(),
			texturePath.c_str(),
			&textureMap_[texturePath]);
	}

	return textureMap_[texturePath];

}


// End of file