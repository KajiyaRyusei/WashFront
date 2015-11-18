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
	class ScreenTextureAlpha
	{
	public:
		ScreenTextureAlpha() : _handle_screen_texture_alpha(nullptr){}
		virtual ~ScreenTextureAlpha() {}

		// �A���t�@�l�n���h���擾���s���܂��B
		void InitializeScreenTextureAlpha(LPD3DXEFFECT effect)
		{
			_handle_screen_texture_alpha = effect->GetParameterByName(nullptr, "uniform_texture_alpha");
			ASSERT(_handle_screen_texture_alpha != nullptr, "�n���h���ǂݍ��݂Ɏ��s���܂����B");
		}


		// �A���t�@�l���V�F�[�_�[�ɑ��M
		void SendScreenTextureAlpha(LPD3DXEFFECT effect) const
		{
			effect->SetFloat(_handle_screen_texture_alpha, _screen_texture_alpha);
		}


		// �e�N�X�`���A���t�@���[�e�[�^
		void SetScreenTextureAlpha(const float& screen_texture_alpha)
		{
			_screen_texture_alpha = screen_texture_alpha;
		}


	private:
		D3DXHANDLE _handle_screen_texture_alpha;

		float _screen_texture_alpha;

	};

};
