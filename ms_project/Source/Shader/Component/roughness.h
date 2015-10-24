//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// ラフネス係数
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
	class Roughness
	{
	public:
		Roughness() : _handle_roughness(nullptr) {}
		virtual ~Roughness() {}

		// ハンドル取得を行います。
		void InitializeRoughness(LPD3DXEFFECT effect)
		{
			_handle_roughness = effect->GetParameterByName(nullptr, "uniform_roughness");
			ASSERT(_handle_roughness != nullptr, "ハンドル読み込みに失敗しました。");
		}

		// シェーダーに送信
		void SendRoughness(LPD3DXEFFECT effect) const
		{
			effect->SetFloat(_handle_roughness, _roughness);
		}

		// ミューテータ
		void SetRoughness(const float roughness)
		{
			_roughness = roughness;
		}

	private:
		D3DXHANDLE _handle_roughness;
		float _roughness;
	};

};
