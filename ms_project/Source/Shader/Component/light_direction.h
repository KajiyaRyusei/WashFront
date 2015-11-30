//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// ���C�g�̕���
//
// Created by Ryusei Kajiya on 20151009
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
	class LightDirection
	{
	public:
		LightDirection() : _handle_light_direction(nullptr) {}
		virtual ~LightDirection() {}

		// �n���h���擾���s���܂��B
		void InitializeLightDirection(LPD3DXEFFECT effect)
		{
			_handle_light_direction = effect->GetParameterByName(nullptr, "uniform_light_direction");
			ASSERT(_handle_light_direction != nullptr, "�n���h���ǂݍ��݂Ɏ��s���܂����B");
		}

		// �V�F�[�_�[�ɑ��M
		void SendLightDirection(LPD3DXEFFECT effect) const
		{
			effect->SetVector(_handle_light_direction, &_light_direction);
		}

		// �~���[�e�[�^
		void SetLightDirection(const D3DXVECTOR4& light_direction)
		{
			_light_direction = light_direction;
		}

	private:
		D3DXHANDLE _handle_light_direction;
		D3DXVECTOR4 _light_direction;
	};

};
