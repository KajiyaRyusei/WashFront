//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// ビュー
//
// Created by Ryusei Kajiya on 20151212
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//*****************************************************************************
// 多重インクルード防止
#pragma once

//*****************************************************************************
// クラス設計
namespace component
{

	class TexcoordMatrix
	{
	public:
		TexcoordMatrix() : _handle_texcoord_matrix(nullptr) {}
		virtual ~TexcoordMatrix() {}

		// ハンドル取得を行います。
		void InitializeTexcoordMatrix(LPD3DXEFFECT effect)
		{
			_handle_texcoord_matrix = effect->GetParameterByName(nullptr, "uniform_texcoord_matrix");
			ASSERT(_handle_texcoord_matrix != nullptr, "ハンドル読み込みに失敗しました。");
		}

		 // シェーダーに送信
		void SendTexcoordMatrix(LPD3DXEFFECT effect) const
		{
			effect->SetMatrix(_handle_texcoord_matrix, &_texcoord_matrix);
		}

		// ミューテータ
		void SetTexcoordMatrix(const D3DXMATRIX& texcoord_matrix)
		{
			_texcoord_matrix = texcoord_matrix;
		}

	private:
		D3DXHANDLE _handle_texcoord_matrix;
		D3DXMATRIX _texcoord_matrix;
	};

};
