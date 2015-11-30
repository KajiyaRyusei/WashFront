//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// ディフューズキューブテクスチャ
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
	class DiffuseCubeMap
	{
	public:
		DiffuseCubeMap() : _handle_diffuse_cube_texture(nullptr) {}
		virtual ~DiffuseCubeMap() {}

		// ハンドル取得を行います。
		void InitializeDiffuseCubeMap(LPD3DXEFFECT effect)
		{
			_handle_diffuse_cube_texture = effect->GetParameterByName(nullptr, "uniform_diffuse_cube_texture");
			ASSERT(_handle_diffuse_cube_texture != nullptr, "ハンドル読み込みに失敗しました。");
		}

		// シェーダーに送信
		void SendDiffuseCubeMap(LPD3DXEFFECT effect) const
		{
			effect->SetTexture(_handle_diffuse_cube_texture, _diffuse_cube_texture);
		}

		// ミューテータ
		void SetDiffuseCubeMap(const LPDIRECT3DCUBETEXTURE9& diffuse_cube_texture)
		{
			_diffuse_cube_texture = diffuse_cube_texture;
		}

	private:
		D3DXHANDLE _handle_diffuse_cube_texture;
		LPDIRECT3DCUBETEXTURE9 _diffuse_cube_texture;
	};

};
