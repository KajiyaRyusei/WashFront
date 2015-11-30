//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// �X�y�L�����L���[�u�e�N�X�`��
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
	class SpecularCubeMap
	{
	public:
		SpecularCubeMap() : _handle_specular_cube_texure(nullptr) {}
		virtual ~SpecularCubeMap() {}

		// �n���h���擾���s���܂��B
		void InitializeSpecularCubeMap(LPD3DXEFFECT effect)
		{
			_handle_specular_cube_texure = effect->GetParameterByName(nullptr, "uniform_specular_cube_texture");
			ASSERT(_handle_specular_cube_texure != nullptr, "�n���h���ǂݍ��݂Ɏ��s���܂����B");
		}

		// �V�F�[�_�[�ɑ��M
		void SendSpecularCubeMap(LPD3DXEFFECT effect) const
		{
			effect->SetTexture(_handle_specular_cube_texure, _specular_cube_texure);
		}

		// �~���[�e�[�^
		void SetSpecularCubeMap(const LPDIRECT3DCUBETEXTURE9& specular_cube_texure)
		{
			_specular_cube_texure = specular_cube_texure;
		}

	private:
		D3DXHANDLE _handle_specular_cube_texure;
		LPDIRECT3DCUBETEXTURE9 _specular_cube_texure;
	};

};
