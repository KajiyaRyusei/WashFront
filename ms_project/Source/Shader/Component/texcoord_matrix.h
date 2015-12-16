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

	class TexcoordMatrix
	{
	public:
		TexcoordMatrix() : _handle_texcoord_matrix(nullptr) {}
		virtual ~TexcoordMatrix() {}

		// �n���h���擾���s���܂��B
		void InitializeTexcoordMatrix(LPD3DXEFFECT effect)
		{
			_handle_texcoord_matrix = effect->GetParameterByName(nullptr, "uniform_texcoord_matrix");
			ASSERT(_handle_texcoord_matrix != nullptr, "�n���h���ǂݍ��݂Ɏ��s���܂����B");
		}

		 // �V�F�[�_�[�ɑ��M
		void SendTexcoordMatrix(LPD3DXEFFECT effect) const
		{
			effect->SetMatrix(_handle_texcoord_matrix, &_texcoord_matrix);
		}

		// �~���[�e�[�^
		void SetTexcoordMatrix(const D3DXMATRIX& texcoord_matrix)
		{
			_texcoord_matrix = texcoord_matrix;
		}

	private:
		D3DXHANDLE _handle_texcoord_matrix;
		D3DXMATRIX _texcoord_matrix;
	};

};
