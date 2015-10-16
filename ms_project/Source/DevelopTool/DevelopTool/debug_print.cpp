//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// デバッグ描画
// 
// Created by Ryusei Kajiya on 20151007
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//*****************************************************************************
// インクルード
#include "debug_print.h"
#include "Renderer/directx9.h"
#include "Common/reference.h"

//==============================================================================
// 初期化
void DebugPrint::Initialize()
{
#ifndef _RELEASE
	LPDIRECT3DDEVICE9 device = Reference::GetInstance().GetRenderer()->GetDevice();

	D3DXCreateFont(
		device,				// インタフェースへのポインタ
		18, 0, 0,			// 高さ、幅、フォントの太さ
		0,					// みっぷマップレベル
		FALSE,				// インタリックフォントであるかどうか
		SHIFTJIS_CHARSET,	// フォントの文字セット
		OUT_DEFAULT_PRECIS,	// windowsでのフォントサイズおよび特性の一致方法
		DEFAULT_QUALITY,	// windowsでのフォントの一致方法
		DEFAULT_PITCH,		// ピッチとファミリインデックス
		L"Terminal",		// フォントの種類
		&_d3dx_font);		// 格納するポインタ

	// デバッグ情報バッファの初期化
	memset(_string, 0, sizeof(char)* kStringMax);
#endif
}

//==============================================================================
// 終了
void DebugPrint::Finalize()
{
#ifndef _RELEASE
	SafeRelease(_d3dx_font);
#endif
}

//==============================================================================
// 描画
void DebugPrint::Draw()
{
#ifndef _RELEASE
	u32 width = Reference::GetInstance().GetSizeScreenWidth();
	u32 height = Reference::GetInstance().GetSizeScreenHeight();

	RECT rect = { 0, 0, width, height };

	_d3dx_font->DrawTextA(nullptr,_string,-1,&rect,DT_RIGHT,D3DCOLOR_ARGB(0xff,0xff,0x00,0xff));

	memset(_string, 0, sizeof(char)* kStringMax);

	_current_string_index = 0;

#endif
}

//==============================================================================
// デバッグ情報登録
void DebugPrint::Print(const char* string, ...)
{
#ifndef _RELEASE

	if( _current_string_index  > kStringMax )
	{
		OutputDebugStringA("=========================================================\n");
		OutputDebugStringA("デバッグ文字のサイズを超えました。サイズ拡張するか、あきらめてください\n");
		OutputDebugStringA("=========================================================\n");
		return;
	}

	va_list args;

	va_start(args, string);

	_current_string_index += vsprintf(&_string[_current_string_index], string, args);

	va_end(args);
#endif
}