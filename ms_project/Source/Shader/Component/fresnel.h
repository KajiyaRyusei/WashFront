//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// �t���l���W��
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
	class Fresnel
	{
	public:
		Fresnel() : _handle_fresnel(nullptr) {}
		virtual ~Fresnel() {}

		// �n���h���擾���s���܂��B
		void InitializeFresnel(LPD3DXEFFECT effect)
		{
			_handle_fresnel = effect->GetParameterByName(nullptr, "uniform_fresnel");
			ASSERT(_handle_fresnel != nullptr, "�n���h���ǂݍ��݂Ɏ��s���܂����B");
		}

		// �V�F�[�_�[�ɑ��M
		void SendFresnel(LPD3DXEFFECT effect) const
		{
			effect->SetFloat(_handle_fresnel, _fresnel);
		}

		// �~���[�e�[�^
		void SetFresnel(const float fresnel)
		{
			_fresnel = fresnel;
		}

	private:
		D3DXHANDLE _handle_fresnel;
		float _fresnel;
	};

};
