//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// TOON�e�N�X�`��
//
// Created by Ryusei Kajiya on 20151202
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
	class ToonTexture
	{
	public:
		ToonTexture() : _handle_toon_texture(nullptr) {}
		virtual ~ToonTexture() {}

		// �n���h���擾���s���܂��B
		void InitializeToonTexture(LPD3DXEFFECT effect)
		{
			_handle_toon_texture = effect->GetParameterByName(nullptr, "uniform_toon_texture");
			ASSERT(_handle_toon_texture != nullptr, "�n���h���ǂݍ��݂Ɏ��s���܂����B");
		}

		// �V�F�[�_�[�ɑ��M
		void SendToonTexture(LPD3DXEFFECT effect) const
		{
			effect->SetTexture(_handle_toon_texture, _toon_texture);
		}

		// �~���[�e�[�^
		void SetToonTexture(const LPDIRECT3DTEXTURE9& toon_texture)
		{
			_toon_texture = toon_texture;
		}

	private:
		D3DXHANDLE _handle_toon_texture;
		LPDIRECT3DTEXTURE9 _toon_texture;
	};
};
