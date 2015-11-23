//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// ���^���l�X�e�N�X�`��
//
// Created by Ryusei Kajiya on 20151120
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//*****************************************************************************
// ���d�C���N���[�h�h�~
#pragma once

//*****************************************************************************
// �N���X�݌v
namespace component
{
	// �ڂ����̓t�@�C���擪�̃R�����g���Q�Ƃ��Ă��������B
	class MetalnessMap
	{
	public:
		MetalnessMap() : _handle_metalness_texture(nullptr) {}
		virtual ~MetalnessMap() {}

		// �n���h���擾���s���܂��B
		void InitializeMetalnessMap(LPD3DXEFFECT effect)
		{
			_handle_metalness_texture = effect->GetParameterByName(nullptr, "uniform_metalness_texture");
			ASSERT(_handle_metalness_texture != nullptr, "�n���h���ǂݍ��݂Ɏ��s���܂����B");
		}

		// �V�F�[�_�[�ɑ��M
		void SendMetalnessMap(LPD3DXEFFECT effect) const
		{
			effect->SetTexture(_handle_metalness_texture, _metalness_texture);
		}

		// �~���[�e�[�^
		void SetMetalnessMap(const LPDIRECT3DTEXTURE9& metalness_texture)
		{
			_metalness_texture = metalness_texture;
		}

	private:
		D3DXHANDLE _handle_metalness_texture;
		LPDIRECT3DTEXTURE9 _metalness_texture;
	};

};
