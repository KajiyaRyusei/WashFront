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
	class ScreenMatrix
	{
	public:
		ScreenMatrix() : _handle_screen_matrix(nullptr) {}
		virtual ~ScreenMatrix() {}

		// �n���h���擾���s���܂��B
		void InitializeScreenMatrix(LPD3DXEFFECT effect)
		{
			_handle_screen_matrix = effect->GetParameterByName(nullptr, "uniform_screen_matrix");
			ASSERT(_handle_screen_matrix != nullptr, "�n���h���ǂݍ��݂Ɏ��s���܂����B");
		}

		 // �V�F�[�_�[�ɑ��M
		void SendScreenMatrix(LPD3DXEFFECT effect) const
		{
			effect->SetMatrix(_handle_screen_matrix, &_screen_matrix);
		}

		// �~���[�e�[�^
		void SetScreenMatrix(const D3DXMATRIX& screen_matrix)
		{
			_screen_matrix = screen_matrix;
		}

	private:
		D3DXHANDLE _handle_screen_matrix;
		D3DXMATRIX _screen_matrix;
	};

};
