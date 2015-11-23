//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// ����e�N�X�`��
//
// Created by Ryusei Kajiya on 20151122
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
	class DirtyMap
	{
	public:
		DirtyMap() : _handle_dirty_texture(nullptr) {}
		virtual ~DirtyMap() {}

		// �n���h���擾���s���܂��B
		void InitializeDirtyTexture(LPD3DXEFFECT effect)
		{
			_handle_dirty_texture = effect->GetParameterByName(nullptr, "uniform_dirty_texture");
			ASSERT(_handle_dirty_texture != nullptr, "�n���h���ǂݍ��݂Ɏ��s���܂����B");
		}

		// �V�F�[�_�[�ɑ��M
		void SendDirtyTexture(LPD3DXEFFECT effect) const
		{
			effect->SetTexture(_handle_dirty_texture, _dirty_texture);
		}

		// �~���[�e�[�^
		void SetDirtyTexture(const LPDIRECT3DTEXTURE9& dirty_texture)
		{
			_dirty_texture = dirty_texture;
		}

	private:
		D3DXHANDLE _handle_dirty_texture;
		LPDIRECT3DTEXTURE9 _dirty_texture;
	};

};
