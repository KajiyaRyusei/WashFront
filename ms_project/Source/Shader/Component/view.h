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

	class View
	{
	public:
		View() : _handle_view(nullptr) {}
		virtual ~View() {}

		// ハンドル取得を行います。
		void InitializeView(LPD3DXEFFECT effect)
		{
			_handle_view = effect->GetParameterByName(nullptr, "uniform_view");
			ASSERT(_handle_view != nullptr, "ハンドル読み込みに失敗しました。");
		}

		 // シェーダーに送信
		void SendView(LPD3DXEFFECT effect) const
		{
			effect->SetMatrix(_handle_view, &_view);
		}

		// ミューテータ
		void SetView(const D3DXMATRIX& view)
		{
			_view = view;
		}

	private:
		D3DXHANDLE _handle_view;
		D3DXMATRIX _view;
	};

};
