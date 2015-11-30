//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// 水変化用行列
//
// Created by Ryusei Kajiya on 20151114
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//*****************************************************************************
// 多重インクルード防止
#pragma once

//*****************************************************************************
// クラス設計
namespace component
{

	// 詳しくはファイル先頭のコメントを参照してください。
	class WaterMatrix
	{
	public:
		WaterMatrix() : _handle_water_matrix(nullptr)
		{

		}
		virtual ~WaterMatrix() {}

		// ハンドル取得を行います。
		void InitializeWaterMatrix(LPD3DXEFFECT effect)
		{
			_handle_water_matrix = effect->GetParameterByName(nullptr, "uniform_water_matrix");
			ASSERT(_handle_water_matrix != nullptr, "ハンドル読み込みに失敗しました。");
		}

		// シェーダーに送信
		void SendWaterMatrix(LPD3DXEFFECT effect) const
		{
			effect->SetMatrixArray(_handle_water_matrix, _water_matrix_list, kMatrixMax);
		}

		// ミューテータ
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
