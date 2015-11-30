//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// �J����eye�̍��W
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
	class EyePosition
	{
	public:
		EyePosition() : _handle_eye_position(nullptr) {}
		virtual ~EyePosition() {}

		// �n���h���擾���s���܂��B
		void InitializeEyePosition(LPD3DXEFFECT effect)
		{
			_handle_eye_position = effect->GetParameterByName(nullptr, "uniform_eye_position");
			ASSERT(_handle_eye_position != nullptr, "�n���h���ǂݍ��݂Ɏ��s���܂����B");
		}

		// �V�F�[�_�[�ɑ��M
		void SendEyePosition(LPD3DXEFFECT effect) const
		{
			effect->SetVector(_handle_eye_position, &_eye_position);
		}

		// �~���[�e�[�^
		void SetEyePosition(const D3DXVECTOR4& eye_position)
		{
			_eye_position = eye_position;
		}

	private:
		D3DXHANDLE _handle_eye_position;
		D3DXVECTOR4 _eye_position;
	};

};
