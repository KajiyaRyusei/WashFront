//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// ライトの方向
//
// Created by Ryusei Kajiya on 20151009
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
	class LightDirection
	{
	public:
		LightDirection() : _handle_light_direction(nullptr) {}
		virtual ~LightDirection() {}

		// ハンドル取得を行います。
		void InitializeLightDirection(LPD3DXEFFECT effect)
		{
			_handle_light_direction = effect->GetParameterByName(nullptr, "uniform_light_direction");
			ASSERT(_handle_light_direction != nullptr, "ハンドル読み込みに失敗しました。");
		}

		// シェーダーに送信
		void SendLightDirection(LPD3DXEFFECT effect) const
		{
			effect->SetVector(_handle_light_direction, &_light_direction);
		}

		// ミューテータ
		void SetLightDirection(const D3DXVECTOR4& light_direction)
		{
			_light_direction = light_direction;
		}

	private:
		D3DXHANDLE _handle_light_direction;
		D3DXVECTOR4 _light_direction;
	};

};
