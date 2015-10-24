//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// ���^���l�X�W��
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
	class Metalness
	{
	public:
		Metalness() : _handle_metalness(nullptr) {}
		virtual ~Metalness() {}

		// �n���h���擾���s���܂��B
		void InitializeMetalness(LPD3DXEFFECT effect)
		{
			_handle_metalness = effect->GetParameterByName(nullptr, "uniform_metalness");
			ASSERT(_handle_metalness != nullptr, "�n���h���ǂݍ��݂Ɏ��s���܂����B");
		}

		// �V�F�[�_�[�ɑ��M
		void SendMetalness(LPD3DXEFFECT effect) const
		{
			effect->SetFloat(_handle_metalness, _metalness);
		}

		// �~���[�e�[�^
		void SetMetalness(const float metalness)
		{
			_metalness = metalness;
		}

	private:
		D3DXHANDLE _handle_metalness;
		float _metalness;
	};

};
