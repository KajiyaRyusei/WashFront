//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// �e�N�X�`�����W�̈ړ�
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
	class TexcoordMove
	{
	public:
		TexcoordMove() : _handle_texcoord_move(nullptr) {}
		virtual ~TexcoordMove() {}

		// �n���h���擾���s���܂��B
		void InitializeTexcoordMove(LPD3DXEFFECT effect)
		{
			_handle_texcoord_move = effect->GetParameterByName(nullptr, "uniform_texcoord_move");
			ASSERT(_handle_texcoord_move != nullptr, "�n���h���ǂݍ��݂Ɏ��s���܂����B");
		}

		// �V�F�[�_�[�ɑ��M
		void SendTexcoordMove(LPD3DXEFFECT effect) const
		{
			fx32 tmp[2] = { _texcoord_move.x, _texcoord_move.y };
			effect->SetFloatArray(_handle_texcoord_move, tmp, 2);
		}

		// �~���[�e�[�^
		void SetTexcoordMove(const D3DXVECTOR2& texcoord_move)
		{
			_texcoord_move = texcoord_move;
		}

	private:
		D3DXHANDLE _handle_texcoord_move;
		D3DXVECTOR2 _texcoord_move;
	};

};
