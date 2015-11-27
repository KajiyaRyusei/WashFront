//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// �r���[�v���W�F�N�V����
//
// Created by Ryusei Kajiya on 20151125
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
	class ViewProjection
	{
	public:
		ViewProjection() : _handle_view_projection(nullptr) {}
		virtual ~ViewProjection() {}

		// �n���h���擾���s���܂��B
		void InitializeViewProjection(LPD3DXEFFECT effect)
		{
			_handle_view_projection = effect->GetParameterByName(nullptr, "uniform_view_projection");
			ASSERT(_handle_view_projection != nullptr, "�n���h���ǂݍ��݂Ɏ��s���܂����B");
		}

		// �V�F�[�_�[�ɑ��M
		void SendViewProjection(LPD3DXEFFECT effect) const
		{
			effect->SetMatrix(_handle_view_projection, &_view_projection);
		}

		// �~���[�e�[�^
		void SetViewProjection(const D3DXMATRIX& view_projection)
		{
			_view_projection = view_projection;
		}

	private:
		D3DXHANDLE _handle_view_projection;
		D3DXMATRIX _view_projection;
	};

};
