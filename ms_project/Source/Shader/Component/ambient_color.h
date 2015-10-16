//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// �A���r�G���g�F
//
// Created by Ryusei Kajiya on 20151013
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
	class AmbientColor
	{
	public:
		AmbientColor() : _handle_ambient_color(nullptr) {}
		virtual ~AmbientColor() {}

		// �n���h���擾���s���܂��B
		void InitializeAmbientColor(LPD3DXEFFECT effect)
		{
			_handle_ambient_color = effect->GetParameterByName(nullptr, "uniform_ambient_color");
			ASSERT(_handle_ambient_color != nullptr, "�n���h���ǂݍ��݂Ɏ��s���܂����B");
		}

		// �V�F�[�_�[�ɑ��M
		void SendAmbientColor(LPD3DXEFFECT effect) const
		{
			effect->SetVector(_handle_ambient_color, &_ambient_color);
		}

		// �~���[�e�[�^
		void SetAmbientColor(const D3DXVECTOR4& ambient_color)
		{
			_ambient_color = ambient_color;
		}

	private:
		D3DXHANDLE _handle_ambient_color;
		D3DXVECTOR4 _ambient_color;
	};

};
