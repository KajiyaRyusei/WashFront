//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// 汚れ用移動マトリックス
//
// Created by Ryusei Kajiya on 20151103
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
	class DirtMoveMatrix
	{
	public:
		DirtMoveMatrix() : _handle_dirt_move_matrix(nullptr) {}
		virtual ~DirtMoveMatrix() {}

		// ハンドル取得を行います。
		void InitializeDirtMoveMatrix(LPD3DXEFFECT effect)
		{
			_handle_dirt_move_matrix = effect->GetParameterByName(nullptr, "uniform_dirt_move_matrix");
			ASSERT(_handle_dirt_move_matrix != nullptr, "ハンドル読み込みに失敗しました。");
		}

		 // シェーダーに送信
		void SendDirtMoveMatrix(LPD3DXEFFECT effect) const
		{
			effect->SetMatrix(_handle_dirt_move_matrix, &_dirt_move_matrix);
		}

		// ミューテータ
		void SetDirtMoveMatrix(const D3DXMATRIX& dirt_move_matrix)
		{
			_dirt_move_matrix = dirt_move_matrix;
		}

	private:
		D3DXHANDLE _handle_dirt_move_matrix;
		D3DXMATRIX _dirt_move_matrix;
	};

};
