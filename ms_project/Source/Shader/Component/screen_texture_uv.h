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
	class ScreenTextureUv
	{
	public:
		ScreenTextureUv() : _handle_screen_texture_uv(nullptr){}
		virtual ~ScreenTextureUv() {}

		// UV�n���h���擾���s���܂��B
		void InitializeScreenTextureUv(LPD3DXEFFECT effect)
		{
			_handle_screen_texture_uv = effect->GetParameterByName(nullptr, "uniform_texture_uv");
			ASSERT(_handle_screen_texture_uv != nullptr, "�n���h���ǂݍ��݂Ɏ��s���܂����B");
		}


		// UV�l���V�F�[�_�[�ɑ��M
		void SendScreenTextureUv(LPD3DXEFFECT effect) const
		{
			fx32 tmp[2] = { _screen_texture_uv.x, _screen_texture_uv.y };
			effect->SetFloatArray(_handle_screen_texture_uv, tmp, 2);
		}


		// �e�N�X�`��UV�~���[�e�[�^
		void SetScreenTextureUv(const D3DXVECTOR2& screen_texture_uv)
		{
			_screen_texture_uv = screen_texture_uv;
		}


	private:
		D3DXHANDLE _handle_screen_texture_uv;

		D3DXVECTOR2 _screen_texture_uv;

	};

};
