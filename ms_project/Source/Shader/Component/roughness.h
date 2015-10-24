//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// ���t�l�X�W��
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
	class Roughness
	{
	public:
		Roughness() : _handle_roughness(nullptr) {}
		virtual ~Roughness() {}

		// �n���h���擾���s���܂��B
		void InitializeRoughness(LPD3DXEFFECT effect)
		{
			_handle_roughness = effect->GetParameterByName(nullptr, "uniform_roughness");
			ASSERT(_handle_roughness != nullptr, "�n���h���ǂݍ��݂Ɏ��s���܂����B");
		}

		// �V�F�[�_�[�ɑ��M
		void SendRoughness(LPD3DXEFFECT effect) const
		{
			effect->SetFloat(_handle_roughness, _roughness);
		}

		// �~���[�e�[�^
		void SetRoughness(const float roughness)
		{
			_roughness = roughness;
		}

	private:
		D3DXHANDLE _handle_roughness;
		float _roughness;
	};

};
