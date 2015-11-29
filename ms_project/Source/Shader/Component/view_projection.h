//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// ビュープロジェクション
//
// Created by Ryusei Kajiya on 20151125
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
	class ViewProjection
	{
	public:
		ViewProjection() : _handle_view_projection(nullptr) {}
		virtual ~ViewProjection() {}

		// ハンドル取得を行います。
		void InitializeViewProjection(LPD3DXEFFECT effect)
		{
			_handle_view_projection = effect->GetParameterByName(nullptr, "uniform_view_projection");
			ASSERT(_handle_view_projection != nullptr, "ハンドル読み込みに失敗しました。");
		}

		// シェーダーに送信
		void SendViewProjection(LPD3DXEFFECT effect) const
		{
			effect->SetMatrix(_handle_view_projection, &_view_projection);
		}

		// ミューテータ
		void SetViewProjection(const D3DXMATRIX& view_projection)
		{
			_view_projection = view_projection;
		}

	private:
		D3DXHANDLE _handle_view_projection;
		D3DXMATRIX _view_projection;
	};

};
