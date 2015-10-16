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
	class ScreenSize
	{
	public:
		ScreenSize() : _handle_screen_size(nullptr) {}
		virtual ~ScreenSize() {}

		// ハンドル取得を行います。
		void InitializeScreenSize(LPD3DXEFFECT effect)
		{
			_handle_screen_size = effect->GetParameterByName(nullptr, "uniform_screen_size");
			ASSERT(_handle_screen_size != nullptr, "ハンドル読み込みに失敗しました。");
		}

		// シェーダーに送信
		void SendScreenSize(LPD3DXEFFECT effect) const
		{
			fx32 tmp[2] = { _screen_size.x, _screen_size.y };
			effect->SetFloatArray(_handle_screen_size, tmp, 2);
		}

		// ミューテータ
		void SetScreenSize(const D3DXVECTOR2& screen_size)
		{
			_screen_size = screen_size;
		}

	private:
		D3DXHANDLE _handle_screen_size;
		D3DXVECTOR2 _screen_size;
	};

};
