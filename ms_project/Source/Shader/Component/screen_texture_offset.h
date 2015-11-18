//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// �X�N���[���e�N�X�`���ݒ�
//
// Created by Chiharu Kamiyama on 20151111
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
	class ScreenTextureOffset
	{
	public:
		ScreenTextureOffset() : _handle_screen_texture_offset(nullptr){}
		virtual ~ScreenTextureOffset() {}


		// �I�t�Z�b�g�n���h���擾���s���܂��B
		void InitializeScreenTextureOffset(LPD3DXEFFECT effect)
		{
			_handle_screen_texture_offset = effect->GetParameterByName(nullptr, "uniform_texture_offset");
			ASSERT(_handle_screen_texture_offset != nullptr, "�n���h���ǂݍ��݂Ɏ��s���܂����B");
		}

		// �I�t�Z�b�g�l���V�F�[�_�[�ɑ��M
		void SendScreenTextureOffset(LPD3DXEFFECT effect) const
		{
			fx32 tmp[2] = { _screen_texture_offset.x, _screen_texture_offset.y };
			effect->SetFloatArray(_handle_screen_texture_offset, tmp, 2);
		}

		// �e�N�X�`���I�t�Z�b�g�~���[�e�[�^
		void SetScreenTextureOffset(const D3DXVECTOR2& screen_texture_offset)
		{
			_screen_texture_offset = screen_texture_offset;
		}


	private:
		D3DXHANDLE _handle_screen_texture_offset;

		D3DXVECTOR2 _screen_texture_offset;

	};

};
