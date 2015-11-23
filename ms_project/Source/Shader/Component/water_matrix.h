//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// ���ω��p�s��
//
// Created by Ryusei Kajiya on 20151114
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
	class WaterMatrix
	{
	public:
		WaterMatrix() : _handle_water_matrix(nullptr)
		{

		}
		virtual ~WaterMatrix() {}

		// �n���h���擾���s���܂��B
		void InitializeWaterMatrix(LPD3DXEFFECT effect)
		{
			_handle_water_matrix = effect->GetParameterByName(nullptr, "uniform_water_matrix");
			ASSERT(_handle_water_matrix != nullptr, "�n���h���ǂݍ��݂Ɏ��s���܂����B");
		}

		// �V�F�[�_�[�ɑ��M
		void SendWaterMatrix(LPD3DXEFFECT effect) const
		{
			effect->SetMatrixArray(_handle_water_matrix, _water_matrix_list, kMatrixMax);
		}

		// �~���[�e�[�^
		void SetWaterMatrix(const D3DXMATRIX* water_matrix_list)
		{
			for( u8 i = 0; i < kMatrixMax; ++i )
			{
				_water_matrix_list[i] = water_matrix_list[i];
			}
		}

		static const u8 kMatrixMax = 3;

	private:
		D3DXHANDLE _handle_water_matrix;
		D3DXMATRIX _water_matrix_list[kMatrixMax];
	};

};
