//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// 
// ウィンドウに対する操作のラッパー群
// 
// Created by Ryusei Kajiya on 20151005
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//*****************************************************************************
// インクルード
#include "window_operation_wrapper.h"

namespace wow
{
	//====================================
	// ウィンドウを真ん中に持ってくる
	//------------------------------------
	void WindowCenter(HWND handle_window)
	{
		HWND handle_window_owener;
		RECT rect_child, rect_owener;

		// 親ウィンドウのハンドルを取得
		handle_window_owener = GetParent(handle_window);

		if (handle_window_owener == nullptr)
		{// 親のウィンドウが存在しなかったらシステム全体におけるパラメータを取得または設定する
			SystemParametersInfo(
				SPI_GETWORKAREA,// 取得または設定すべきシステムパラメータ
				0,				// 実施する操作
				&rect_child,	// 実施する操作２
				0);				// ユーザープロファイルの更新オプション   
		}
		else
		{// クライアント座標の取得
			GetClientRect(
				handle_window_owener,// ウィンドウハンドル
				&rect_child);		 // クライアント座標

		}

		// スクリーン座標を取得
		GetWindowRect(
			handle_window,
			&rect_owener);

		// ウィンドウの位置計算
		s32 x = ((rect_child.right - rect_child.left) - (rect_owener.right - rect_owener.left)) / 2 + rect_child.left;
		s32 y = ((rect_child.bottom - rect_child.top) - (rect_owener.bottom - rect_owener.top)) / 2 + rect_child.top;

		// ウィンドウのポジション設定
		SetWindowPos(
			handle_window,// ウィンドウハンドル
			HWND_TOP,	  // 配置順序のハンドル
			x, y,		  // 縦横方向のハンドル
			0, 0,		  // 幅、高さ
			SWP_NOSIZE);  // ウィンドウ位置のオプション(サイズの変更はなし)
	}
};

