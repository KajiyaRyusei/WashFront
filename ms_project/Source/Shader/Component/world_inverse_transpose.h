//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// ワールド
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
	class WorldInverseTranspose
	{
	public:
		WorldInverseTranspose() : _handle_world_inverse_transpose(nullptr) {}
		virtual ~WorldInverseTranspose() {}

		// ハンドル取得を行います。
		void InitializeWorldInverseTranspose(LPD3DXEFFECT effect)
		{
			_handle_world_inverse_transpose = effect->GetParameterByName(nullptr, "uniform_world_inverse_transpose");
			ASSERT(_handle_world_inverse_transpose != nullptr, "ハンドル読み込みに失敗しました。");
		}

		 // シェーダーに送信
		void SendWorldInverseTranspose(LPD3DXEFFECT effect) const
		{
			effect->SetMatrix(_handle_world_inverse_transpose, &_world_inverse_transpose);
		}

		// ミューテータ
		void SetWorldInverseTranspose(const D3DXMATRIX& world_inverse_transpose)
		{
			_world_inverse_transpose = world_inverse_transpose;
		}

	private:
		D3DXHANDLE _handle_world_inverse_transpose;
		D3DXMATRIX _world_inverse_transpose;
	};

};
