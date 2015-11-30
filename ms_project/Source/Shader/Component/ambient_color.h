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
	class AmbientColor
	{
	public:
		AmbientColor() : _handle_ambient_color(nullptr) {}
		virtual ~AmbientColor() {}

		// ハンドル取得を行います。
		void InitializeAmbientColor(LPD3DXEFFECT effect)
		{
			_handle_ambient_color = effect->GetParameterByName(nullptr, "uniform_ambient_color");
			ASSERT(_handle_ambient_color != nullptr, "ハンドル読み込みに失敗しました。");
		}

		// シェーダーに送信
		void SendAmbientColor(LPD3DXEFFECT effect) const
		{
			effect->SetVector(_handle_ambient_color, &_ambient_color);
		}

		// ミューテータ
		void SetAmbientColor(const D3DXVECTOR4& ambient_color)
		{
			_ambient_color = ambient_color;
		}

	private:
		D3DXHANDLE _handle_ambient_color;
		D3DXVECTOR4 _ambient_color;
	};

};
