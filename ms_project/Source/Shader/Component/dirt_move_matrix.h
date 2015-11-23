//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// ����p�ړ��}�g���b�N�X
//
// Created by Ryusei Kajiya on 20151103
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
	class DirtMoveMatrix
	{
	public:
		DirtMoveMatrix() : _handle_dirt_move_matrix(nullptr) {}
		virtual ~DirtMoveMatrix() {}

		// �n���h���擾���s���܂��B
		void InitializeDirtMoveMatrix(LPD3DXEFFECT effect)
		{
			_handle_dirt_move_matrix = effect->GetParameterByName(nullptr, "uniform_dirt_move_matrix");
			ASSERT(_handle_dirt_move_matrix != nullptr, "�n���h���ǂݍ��݂Ɏ��s���܂����B");
		}

		 // �V�F�[�_�[�ɑ��M
		void SendDirtMoveMatrix(LPD3DXEFFECT effect) const
		{
			effect->SetMatrix(_handle_dirt_move_matrix, &_dirt_move_matrix);
		}

		// �~���[�e�[�^
		void SetDirtMoveMatrix(const D3DXMATRIX& dirt_move_matrix)
		{
			_dirt_move_matrix = dirt_move_matrix;
		}

	private:
		D3DXHANDLE _handle_dirt_move_matrix;
		D3DXMATRIX _dirt_move_matrix;
	};

};
