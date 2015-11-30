//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// �f�B�t���[�Y�L���[�u�e�N�X�`��
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
	class DiffuseCubeMap
	{
	public:
		DiffuseCubeMap() : _handle_diffuse_cube_texture(nullptr) {}
		virtual ~DiffuseCubeMap() {}

		// �n���h���擾���s���܂��B
		void InitializeDiffuseCubeMap(LPD3DXEFFECT effect)
		{
			_handle_diffuse_cube_texture = effect->GetParameterByName(nullptr, "uniform_diffuse_cube_texture");
			ASSERT(_handle_diffuse_cube_texture != nullptr, "�n���h���ǂݍ��݂Ɏ��s���܂����B");
		}

		// �V�F�[�_�[�ɑ��M
		void SendDiffuseCubeMap(LPD3DXEFFECT effect) const
		{
			effect->SetTexture(_handle_diffuse_cube_texture, _diffuse_cube_texture);
		}

		// �~���[�e�[�^
		void SetDiffuseCubeMap(const LPDIRECT3DCUBETEXTURE9& diffuse_cube_texture)
		{
			_diffuse_cube_texture = diffuse_cube_texture;
		}

	private:
		D3DXHANDLE _handle_diffuse_cube_texture;
		LPDIRECT3DCUBETEXTURE9 _diffuse_cube_texture;
	};

};
