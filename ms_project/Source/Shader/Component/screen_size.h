//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// �X�N���[����ł̍��W
//
// Created by Ryusei Kajiya on 20151012
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
	class ScreenSize
	{
	public:
		ScreenSize() : _handle_screen_size(nullptr) {}
		virtual ~ScreenSize() {}

		// �n���h���擾���s���܂��B
		void InitializeScreenSize(LPD3DXEFFECT effect)
		{
			_handle_screen_size = effect->GetParameterByName(nullptr, "uniform_screen_size");
			ASSERT(_handle_screen_size != nullptr, "�n���h���ǂݍ��݂Ɏ��s���܂����B");
		}

		// �V�F�[�_�[�ɑ��M
		void SendScreenSize(LPD3DXEFFECT effect) const
		{
			fx32 tmp[2] = { _screen_size.x, _screen_size.y };
			effect->SetFloatArray(_handle_screen_size, tmp, 2);
		}

		// �~���[�e�[�^
		void SetScreenSize(const D3DXVECTOR2& screen_size)
		{
			_screen_size = screen_size;
		}

	private:
		D3DXHANDLE _handle_screen_size;
		D3DXVECTOR2 _screen_size;
	};

};
