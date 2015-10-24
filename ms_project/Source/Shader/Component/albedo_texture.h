//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// �A���x�h�e�N�X�`��
//
// Created by Ryusei Kajiya on 20151023
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
	class AlbedoMap
	{
	public:
		AlbedoMap() : _handle_albedo_texture(nullptr) {}
		virtual ~AlbedoMap() {}

		// �n���h���擾���s���܂��B
		void InitializeAlbedoTexture(LPD3DXEFFECT effect)
		{
			_handle_albedo_texture = effect->GetParameterByName(nullptr, "uniform_diffuse_texture");
			ASSERT(_handle_albedo_texture != nullptr, "�n���h���ǂݍ��݂Ɏ��s���܂����B");
		}

		// �V�F�[�_�[�ɑ��M
		void SendAlbedoTexture(LPD3DXEFFECT effect) const
		{
			effect->SetTexture(_handle_albedo_texture, _albedo_texture);
		}

		// �~���[�e�[�^
		void SetAlbedoTexture(const LPDIRECT3DTEXTURE9& albedo_texture)
		{
			_albedo_texture = albedo_texture;
		}

	private:
		D3DXHANDLE _handle_albedo_texture;
		LPDIRECT3DTEXTURE9 _albedo_texture;
	};

};
