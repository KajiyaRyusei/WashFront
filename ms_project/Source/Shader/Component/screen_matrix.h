//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// スクリーン上での座標
//
// Created by Ryusei Kajiya on 20151012
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
	class ScreenMatrix
	{
	public:
		ScreenMatrix() : _handle_screen_matrix(nullptr) {}
		virtual ~ScreenMatrix() {}

		// ハンドル取得を行います。
		void InitializeScreenMatrix(LPD3DXEFFECT effect)
		{
			_handle_screen_matrix = effect->GetParameterByName(nullptr, "uniform_screen_matrix");
			ASSERT(_handle_screen_matrix != nullptr, "ハンドル読み込みに失敗しました。");
		}

		 // シェーダーに送信
		void SendScreenMatrix(LPD3DXEFFECT effect) const
		{
			effect->SetMatrix(_handle_screen_matrix, &_screen_matrix);
		}

		// ミューテータ
		void SetScreenMatrix(const D3DXMATRIX& screen_matrix)
		{
			_screen_matrix = screen_matrix;
		}

	private:
		D3DXHANDLE _handle_screen_matrix;
		D3DXMATRIX _screen_matrix;
	};

};
