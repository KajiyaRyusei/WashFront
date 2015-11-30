//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// �A���x�h�L���[�u�e�N�X�`��
//
// Created by Ryusei Kajiya on 20151022
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
	class AlbedoCubeMap
	{
	public:
		AlbedoCubeMap() : _handle_albedo_cube_texture(nullptr) {}
		virtual ~AlbedoCubeMap() {}

		// �n���h���擾���s���܂��B
		void InitializeAlbedoCubeTexture(LPD3DXEFFECT effect)
		{
			_handle_albedo_cube_texture = effect->GetParameterByName(nullptr, "uniform_albedo_cube_texture");
			ASSERT(_handle_albedo_cube_texture != nullptr, "�n���h���ǂݍ��݂Ɏ��s���܂����B");
		}

		// �V�F�[�_�[�ɑ��M
		void SendAlbedoCubeTexture(LPD3DXEFFECT effect) const
		{
			effect->SetTexture(_handle_albedo_cube_texture, _albedo_cube_texture);
		}

		// �~���[�e�[�^
		void SetAlbedoCubeTexture(const LPDIRECT3DCUBETEXTURE9& albedo_cube_texture)
		{
			_albedo_cube_texture = albedo_cube_texture;
		}

	private:
		D3DXHANDLE _handle_albedo_cube_texture;
		LPDIRECT3DCUBETEXTURE9 _albedo_cube_texture;
	};

};
