//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// �@���}�b�v
//
// Created by Ryusei Kajiya on 20151029
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
	class NormalMap
	{
	public:
		NormalMap() : _handle_normal_texture(nullptr) {}
		virtual ~NormalMap() {}

		// �n���h���擾���s���܂��B
		void InitializeNormalTexture(LPD3DXEFFECT effect)
		{
			_handle_normal_texture = effect->GetParameterByName(nullptr, "uniform_normal_texture");
			ASSERT(_handle_normal_texture != nullptr, "�n���h���ǂݍ��݂Ɏ��s���܂����B");
		}

		// �V�F�[�_�[�ɑ��M
		void SendNormalTexture(LPD3DXEFFECT effect) const
		{
			effect->SetTexture(_handle_normal_texture, _normal_texture);
		}

		// �~���[�e�[�^
		void SetNormalTexture(const LPDIRECT3DTEXTURE9& normal_texture)
		{
			_normal_texture = normal_texture;
		}

	private:
		D3DXHANDLE _handle_normal_texture;
		LPDIRECT3DTEXTURE9 _normal_texture;
	};

};
