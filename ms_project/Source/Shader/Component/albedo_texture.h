//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// アルベドテクスチャ
//
// Created by Ryusei Kajiya on 20151023
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
	class AlbedoMap
	{
	public:
		AlbedoMap() : _handle_albedo_texture(nullptr) {}
		virtual ~AlbedoMap() {}

		// ハンドル取得を行います。
		void InitializeAlbedoTexture(LPD3DXEFFECT effect)
		{
			_handle_albedo_texture = effect->GetParameterByName(nullptr, "uniform_diffuse_texture");
			ASSERT(_handle_albedo_texture != nullptr, "ハンドル読み込みに失敗しました。");
		}

		// シェーダーに送信
		void SendAlbedoTexture(LPD3DXEFFECT effect) const
		{
			effect->SetTexture(_handle_albedo_texture, _albedo_texture);
		}

		// ミューテータ
		void SetAlbedoTexture(const LPDIRECT3DTEXTURE9& albedo_texture)
		{
			_albedo_texture = albedo_texture;
		}

	private:
		D3DXHANDLE _handle_albedo_texture;
		LPDIRECT3DTEXTURE9 _albedo_texture;
	};

};
