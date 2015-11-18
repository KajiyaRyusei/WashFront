//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// スクリーンテクスチャ設定
//
// Created by Chiharu Kamiyama on 20151111
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
	class ScreenTextureAlpha
	{
	public:
		ScreenTextureAlpha() : _handle_screen_texture_alpha(nullptr){}
		virtual ~ScreenTextureAlpha() {}

		// アルファ値ハンドル取得を行います。
		void InitializeScreenTextureAlpha(LPD3DXEFFECT effect)
		{
			_handle_screen_texture_alpha = effect->GetParameterByName(nullptr, "uniform_texture_alpha");
			ASSERT(_handle_screen_texture_alpha != nullptr, "ハンドル読み込みに失敗しました。");
		}


		// アルファ値をシェーダーに送信
		void SendScreenTextureAlpha(LPD3DXEFFECT effect) const
		{
			effect->SetFloat(_handle_screen_texture_alpha, _screen_texture_alpha);
		}


		// テクスチャアルファューテータ
		void SetScreenTextureAlpha(const float& screen_texture_alpha)
		{
			_screen_texture_alpha = screen_texture_alpha;
		}


	private:
		D3DXHANDLE _handle_screen_texture_alpha;

		float _screen_texture_alpha;

	};

};
