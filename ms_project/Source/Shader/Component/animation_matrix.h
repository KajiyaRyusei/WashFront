//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// �A�j���[�V�����}�g���b�N�X
//
// Created by Ryusei Kajiya on 20151014
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
	class AnimationMatrix
	{
	public:
		AnimationMatrix() : _handle_animation_matrix(nullptr)
		{

		}
		virtual ~AnimationMatrix() {}

		// �n���h���擾���s���܂��B
		void InitializeAnimationMatrix(LPD3DXEFFECT effect)
		{
			_handle_animation_matrix = effect->GetParameterByName(nullptr, "uniform_animation_matrix_list");
			ASSERT(_handle_animation_matrix != nullptr, "�n���h���ǂݍ��݂Ɏ��s���܂����B");
		}

		 // �V�F�[�_�[�ɑ��M
		void SendAnimationMatrix(LPD3DXEFFECT effect) const
		{
			effect->SetMatrixArray(_handle_animation_matrix, _animation_matrix_list, 40);
		}

		// �~���[�e�[�^
		// �s��̍ő吔�͌���40�ł��B
		void SetAnimationMatrix(const D3DXMATRIX* animation_matrix_list )
		{
			for( u8 i = 0; i < kMatrixMax;++i )
			{
				_animation_matrix_list[i] = animation_matrix_list[i];
			}
		}

		static const u8 kMatrixMax = 18;

	private:
		D3DXHANDLE _handle_animation_matrix;
		D3DXMATRIX _animation_matrix_list[kMatrixMax];
	};

};
