//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// スペキュラキューブテクスチャ
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
	class SpecularCubeMap
	{
	public:
		SpecularCubeMap() : _handle_specular_cube_texure(nullptr) {}
		virtual ~SpecularCubeMap() {}

		// ハンドル取得を行います。
		void InitializeSpecularCubeMap(LPD3DXEFFECT effect)
		{
			_handle_specular_cube_texure = effect->GetParameterByName(nullptr, "uniform_specular_cube_texture");
			ASSERT(_handle_specular_cube_texure != nullptr, "ハンドル読み込みに失敗しました。");
		}

		// シェーダーに送信
		void SendSpecularCubeMap(LPD3DXEFFECT effect) const
		{
			effect->SetTexture(_handle_specular_cube_texure, _specular_cube_texure);
		}

		// ミューテータ
		void SetSpecularCubeMap(const LPDIRECT3DCUBETEXTURE9& specular_cube_texure)
		{
			_specular_cube_texure = specular_cube_texure;
		}

	private:
		D3DXHANDLE _handle_specular_cube_texure;
		LPDIRECT3DCUBETEXTURE9 _specular_cube_texure;
	};

};
