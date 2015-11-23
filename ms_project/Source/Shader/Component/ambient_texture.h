//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// �A���r�G���g�F
//
// Created by Ryusei Kajiya on 20151013
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
	class AmbientTexture
	{
	public:
		AmbientTexture() : _handle_ambient_texture(nullptr) {}
		virtual ~AmbientTexture() {}

		// �n���h���擾���s���܂��B
		void InitializeAmbientTexture(LPD3DXEFFECT effect)
		{
			_handle_ambient_texture = effect->GetParameterByName(nullptr, "uniform_screen_texture");
			ASSERT(_handle_ambient_texture != nullptr, "�n���h���ǂݍ��݂Ɏ��s���܂����B");
		}

		// �V�F�[�_�[�ɑ��M
		void SendAmbientTexture(LPD3DXEFFECT effect) const
		{
			effect->SetTexture(_handle_ambient_texture, _ambient_texture);
		}

		// �~���[�e�[�^
		void SetAmbientTexture(const LPDIRECT3DTEXTURE9 ambient_texture)
		{
			_ambient_texture = ambient_texture;
		}

	private:
		D3DXHANDLE _handle_ambient_texture;
		LPDIRECT3DTEXTURE9 _ambient_texture;
	};

};
