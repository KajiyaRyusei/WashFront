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
	class ScreenTextureUv
	{
	public:
		ScreenTextureUv() : _handle_screen_texture_uv(nullptr){}
		virtual ~ScreenTextureUv() {}

		// UVハンドル取得を行います。
		void InitializeScreenTextureUv(LPD3DXEFFECT effect)
		{
			_handle_screen_texture_uv = effect->GetParameterByName(nullptr, "uniform_texture_uv");
			ASSERT(_handle_screen_texture_uv != nullptr, "ハンドル読み込みに失敗しました。");
		}


		// UV値をシェーダーに送信
		void SendScreenTextureUv(LPD3DXEFFECT effect) const
		{
			fx32 tmp[2] = { _screen_texture_uv.x, _screen_texture_uv.y };
			effect->SetFloatArray(_handle_screen_texture_uv, tmp, 2);
		}


		// テクスチャUVミューテータ
		void SetScreenTextureUv(const D3DXVECTOR2& screen_texture_uv)
		{
			_screen_texture_uv = screen_texture_uv;
		}


	private:
		D3DXHANDLE _handle_screen_texture_uv;

		D3DXVECTOR2 _screen_texture_uv;

	};

};
