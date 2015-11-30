//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// フレネル係数
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
	class Fresnel
	{
	public:
		Fresnel() : _handle_fresnel(nullptr) {}
		virtual ~Fresnel() {}

		// ハンドル取得を行います。
		void InitializeFresnel(LPD3DXEFFECT effect)
		{
			_handle_fresnel = effect->GetParameterByName(nullptr, "uniform_fresnel");
			ASSERT(_handle_fresnel != nullptr, "ハンドル読み込みに失敗しました。");
		}

		// シェーダーに送信
		void SendFresnel(LPD3DXEFFECT effect) const
		{
			effect->SetFloat(_handle_fresnel, _fresnel);
		}

		// ミューテータ
		void SetFresnel(const float fresnel)
		{
			_fresnel = fresnel;
		}

	private:
		D3DXHANDLE _handle_fresnel;
		float _fresnel;
	};

};
