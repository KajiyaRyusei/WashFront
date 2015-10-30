//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// 法線マップ
//
// Created by Ryusei Kajiya on 20151029
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
	class NormalMap
	{
	public:
		NormalMap() : _handle_normal_texture(nullptr) {}
		virtual ~NormalMap() {}

		// ハンドル取得を行います。
		void InitializeNormalTexture(LPD3DXEFFECT effect)
		{
			_handle_normal_texture = effect->GetParameterByName(nullptr, "uniform_normal_texture");
			ASSERT(_handle_normal_texture != nullptr, "ハンドル読み込みに失敗しました。");
		}

		// シェーダーに送信
		void SendNormalTexture(LPD3DXEFFECT effect) const
		{
			effect->SetTexture(_handle_normal_texture, _normal_texture);
		}

		// ミューテータ
		void SetNormalTexture(const LPDIRECT3DTEXTURE9& normal_texture)
		{
			_normal_texture = normal_texture;
		}

	private:
		D3DXHANDLE _handle_normal_texture;
		LPDIRECT3DTEXTURE9 _normal_texture;
	};

};
