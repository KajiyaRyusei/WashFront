//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// TOONテクスチャ
//
// Created by Ryusei Kajiya on 20151202
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
	class ToonTexture
	{
	public:
		ToonTexture() : _handle_toon_texture(nullptr) {}
		virtual ~ToonTexture() {}

		// ハンドル取得を行います。
		void InitializeToonTexture(LPD3DXEFFECT effect)
		{
			_handle_toon_texture = effect->GetParameterByName(nullptr, "uniform_toon_texture");
			ASSERT(_handle_toon_texture != nullptr, "ハンドル読み込みに失敗しました。");
		}

		// シェーダーに送信
		void SendToonTexture(LPD3DXEFFECT effect) const
		{
			effect->SetTexture(_handle_toon_texture, _toon_texture);
		}

		// ミューテータ
		void SetToonTexture(const LPDIRECT3DTEXTURE9& toon_texture)
		{
			_toon_texture = toon_texture;
		}

	private:
		D3DXHANDLE _handle_toon_texture;
		LPDIRECT3DTEXTURE9 _toon_texture;
	};
};
