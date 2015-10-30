//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// アルベドキューブテクスチャ
//
// Created by Ryusei Kajiya on 20151022
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
	class AlbedoCubeMap
	{
	public:
		AlbedoCubeMap() : _handle_albedo_cube_texture(nullptr) {}
		virtual ~AlbedoCubeMap() {}

		// ハンドル取得を行います。
		void InitializeAlbedoCubeTexture(LPD3DXEFFECT effect)
		{
			_handle_albedo_cube_texture = effect->GetParameterByName(nullptr, "uniform_albedo_cube_texture");
			ASSERT(_handle_albedo_cube_texture != nullptr, "ハンドル読み込みに失敗しました。");
		}

		// シェーダーに送信
		void SendAlbedoCubeTexture(LPD3DXEFFECT effect) const
		{
			effect->SetTexture(_handle_albedo_cube_texture, _albedo_cube_texture);
		}

		// ミューテータ
		void SetAlbedoCubeTexture(const LPDIRECT3DCUBETEXTURE9& albedo_cube_texture)
		{
			_albedo_cube_texture = albedo_cube_texture;
		}

	private:
		D3DXHANDLE _handle_albedo_cube_texture;
		LPDIRECT3DCUBETEXTURE9 _albedo_cube_texture;
	};

};
