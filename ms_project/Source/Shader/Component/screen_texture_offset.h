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
	class ScreenTextureOffset
	{
	public:
		ScreenTextureOffset() : _handle_screen_texture_offset(nullptr){}
		virtual ~ScreenTextureOffset() {}


		// オフセットハンドル取得を行います。
		void InitializeScreenTextureOffset(LPD3DXEFFECT effect)
		{
			_handle_screen_texture_offset = effect->GetParameterByName(nullptr, "uniform_texture_offset");
			ASSERT(_handle_screen_texture_offset != nullptr, "ハンドル読み込みに失敗しました。");
		}

		// オフセット値をシェーダーに送信
		void SendScreenTextureOffset(LPD3DXEFFECT effect) const
		{
			fx32 tmp[2] = { _screen_texture_offset.x, _screen_texture_offset.y };
			effect->SetFloatArray(_handle_screen_texture_offset, tmp, 2);
		}

		// テクスチャオフセットミューテータ
		void SetScreenTextureOffset(const D3DXVECTOR2& screen_texture_offset)
		{
			_screen_texture_offset = screen_texture_offset;
		}


	private:
		D3DXHANDLE _handle_screen_texture_offset;

		D3DXVECTOR2 _screen_texture_offset;

	};

};
