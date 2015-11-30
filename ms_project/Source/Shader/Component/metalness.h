//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// メタルネス係数
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
	class Metalness
	{
	public:
		Metalness() : _handle_metalness(nullptr) {}
		virtual ~Metalness() {}

		// ハンドル取得を行います。
		void InitializeMetalness(LPD3DXEFFECT effect)
		{
			_handle_metalness = effect->GetParameterByName(nullptr, "uniform_metalness");
			ASSERT(_handle_metalness != nullptr, "ハンドル読み込みに失敗しました。");
		}

		// シェーダーに送信
		void SendMetalness(LPD3DXEFFECT effect) const
		{
			effect->SetFloat(_handle_metalness, _metalness);
		}

		// ミューテータ
		void SetMetalness(const float metalness)
		{
			_metalness = metalness;
		}

	private:
		D3DXHANDLE _handle_metalness;
		float _metalness;
	};

};
