//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// テクスチャ座標の移動
//
// Created by Ryusei Kajiya on 20151103
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
	class TexcoordMove
	{
	public:
		TexcoordMove() : _handle_texcoord_move(nullptr) {}
		virtual ~TexcoordMove() {}

		// ハンドル取得を行います。
		void InitializeTexcoordMove(LPD3DXEFFECT effect)
		{
			_handle_texcoord_move = effect->GetParameterByName(nullptr, "uniform_texcoord_move");
			ASSERT(_handle_texcoord_move != nullptr, "ハンドル読み込みに失敗しました。");
		}

		// シェーダーに送信
		void SendTexcoordMove(LPD3DXEFFECT effect) const
		{
			fx32 tmp[2] = { _texcoord_move.x, _texcoord_move.y };
			effect->SetFloatArray(_handle_texcoord_move, tmp, 2);
		}

		// ミューテータ
		void SetTexcoordMove(const D3DXVECTOR2& texcoord_move)
		{
			_texcoord_move = texcoord_move;
		}

	private:
		D3DXHANDLE _handle_texcoord_move;
		D3DXVECTOR2 _texcoord_move;
	};

};
