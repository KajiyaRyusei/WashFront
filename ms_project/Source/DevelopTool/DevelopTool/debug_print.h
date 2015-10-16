﻿//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// デバッグ描画
// 
// Created by Ryusei Kajiya on 20151007
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//*****************************************************************************
// 多重インクルード防止
#pragma once

//==============================================================================
// デバッグ表示クラス
class DebugPrint
{
public:

	DebugPrint() : 
		_d3dx_font(nullptr),
		_current_string_index(0)
	{}

	virtual ~DebugPrint(){}

	void Initialize();
	void Finalize();
	void Draw();

	void Print(const char* fmt, ...);

private:

#ifndef _RELEASE

	static const u64 kStringMax= 1024;
	LPD3DXFONT _d3dx_font;
	char _string[kStringMax];
	u64 _current_string_index;

#endif
};