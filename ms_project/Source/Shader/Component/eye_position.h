//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// カメラeyeの座標
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
	class EyePosition
	{
	public:
		EyePosition() : _handle_eye_position(nullptr) {}
		virtual ~EyePosition() {}

		// ハンドル取得を行います。
		void InitializeEyePosition(LPD3DXEFFECT effect)
		{
			_handle_eye_position = effect->GetParameterByName(nullptr, "uniform_eye_position");
			ASSERT(_handle_eye_position != nullptr, "ハンドル読み込みに失敗しました。");
		}

		// シェーダーに送信
		void SendEyePosition(LPD3DXEFFECT effect) const
		{
			effect->SetVector(_handle_eye_position, &_eye_position);
		}

		// ミューテータ
		void SetEyePosition(const D3DXVECTOR4& eye_position)
		{
			_eye_position = eye_position;
		}

	private:
		D3DXHANDLE _handle_eye_position;
		D3DXVECTOR4 _eye_position;
	};

};
