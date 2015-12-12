//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// �r���[
//
// Created by Ryusei Kajiya on 20151212
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//*****************************************************************************
// ���d�C���N���[�h�h�~
#pragma once

//*****************************************************************************
// �N���X�݌v
namespace component
{

	class View
	{
	public:
		View() : _handle_view(nullptr) {}
		virtual ~View() {}

		// �n���h���擾���s���܂��B
		void InitializeView(LPD3DXEFFECT effect)
		{
			_handle_view = effect->GetParameterByName(nullptr, "uniform_view");
			ASSERT(_handle_view != nullptr, "�n���h���ǂݍ��݂Ɏ��s���܂����B");
		}

		 // �V�F�[�_�[�ɑ��M
		void SendView(LPD3DXEFFECT effect) const
		{
			effect->SetMatrix(_handle_view, &_view);
		}

		// �~���[�e�[�^
		void SetView(const D3DXMATRIX& view)
		{
			_view = view;
		}

	private:
		D3DXHANDLE _handle_view;
		D3DXMATRIX _view;
	};

};
