//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// メタルネステクスチャ
//
// Created by Ryusei Kajiya on 20151120
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
	class MetalnessMap
	{
	public:
		MetalnessMap() : _handle_metalness_texture(nullptr) {}
		virtual ~MetalnessMap() {}

		// ハンドル取得を行います。
		void InitializeMetalnessMap(LPD3DXEFFECT effect)
		{
			_handle_metalness_texture = effect->GetParameterByName(nullptr, "uniform_metalness_texture");
			ASSERT(_handle_metalness_texture != nullptr, "ハンドル読み込みに失敗しました。");
		}

		// シェーダーに送信
		void SendMetalnessMap(LPD3DXEFFECT effect) const
		{
			effect->SetTexture(_handle_metalness_texture, _metalness_texture);
		}

		// ミューテータ
		void SetMetalnessMap(const LPDIRECT3DTEXTURE9& metalness_texture)
		{
			_metalness_texture = metalness_texture;
		}

	private:
		D3DXHANDLE _handle_metalness_texture;
		LPDIRECT3DTEXTURE9 _metalness_texture;
	};

};
