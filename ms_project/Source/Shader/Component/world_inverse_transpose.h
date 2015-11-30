//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// ���[���h
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
	class WorldInverseTranspose
	{
	public:
		WorldInverseTranspose() : _handle_world_inverse_transpose(nullptr) {}
		virtual ~WorldInverseTranspose() {}

		// �n���h���擾���s���܂��B
		void InitializeWorldInverseTranspose(LPD3DXEFFECT effect)
		{
			_handle_world_inverse_transpose = effect->GetParameterByName(nullptr, "uniform_world_inverse_transpose");
			ASSERT(_handle_world_inverse_transpose != nullptr, "�n���h���ǂݍ��݂Ɏ��s���܂����B");
		}

		 // �V�F�[�_�[�ɑ��M
		void SendWorldInverseTranspose(LPD3DXEFFECT effect) const
		{
			effect->SetMatrix(_handle_world_inverse_transpose, &_world_inverse_transpose);
		}

		// �~���[�e�[�^
		void SetWorldInverseTranspose(const D3DXMATRIX& world_inverse_transpose)
		{
			_world_inverse_transpose = world_inverse_transpose;
		}

	private:
		D3DXHANDLE _handle_world_inverse_transpose;
		D3DXMATRIX _world_inverse_transpose;
	};

};
