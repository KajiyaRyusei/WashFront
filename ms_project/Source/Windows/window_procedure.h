//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// 
// ウィンドウプロシージャ
// 
// Created by Ryusei Kajiya on 20151005
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//*****************************************************************************
// 多重インクルード防止
#pragma once

//*****************************************************************************
// プロトタイプ宣言
LRESULT CALLBACK WindowProcedure(
	HWND handle_window,
	UINT message,
	WPARAM w_paramater,
	LPARAM l_paramater);
