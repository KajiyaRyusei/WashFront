//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// アンビエント色
//
// Created by Ryusei Kajiya on 20151013
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
	class AmbientTexture
	{
	public:
		AmbientTexture() : _handle_ambient_texture(nullptr) {}
		virtual ~AmbientTexture() {}

		// ハンドル取得を行います。
		void InitializeAmbientTexture(LPD3DXEFFECT effect)
		{
			_handle_ambient_texture = effect->GetParameterByName(nullptr, "uniform_screen_texture");
			ASSERT(_handle_ambient_texture != nullptr, "ハンドル読み込みに失敗しました。");
		}

		// シェーダーに送信
		void SendAmbientTexture(LPD3DXEFFECT effect) const
		{
			effect->SetTexture(_handle_ambient_texture, _ambient_texture);
		}

		// ミューテータ
		void SetAmbientTexture(const LPDIRECT3DTEXTURE9 ambient_texture)
		{
			_ambient_texture = ambient_texture;
		}

	private:
		D3DXHANDLE _handle_ambient_texture;
		LPDIRECT3DTEXTURE9 _ambient_texture;
	};

};
