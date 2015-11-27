//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// プリコンパイル済みヘッダ
//
// Created by Ryusei Kajiya on 20151005
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//*****************************************************************************
// 多重インクルード防止
#pragma once

//*****************************************************************************
// C システムファイル

// エラー消し
#define _CRT_SECURE_NO_WARNINGS

// ワーニング抑制
#pragma warning( disable :4201 )
#pragma warning( disable :4127 )

#include <stdio.h>
#include <wchar.h>
#include <stdarg.h>

//*****************************************************************************
// C++システムファイル
// STLのデバッグ機能をOFFにする
#ifndef _SECURE_SCL
#define _SECURE_SCL (0)
#endif  // _SECURE_SCL
#ifndef _HAS_ITERATOR_DEBUGGING
#define _HAS_ITERATOR_DEBUGGING (0)
#endif  // _HAS_ITERATOR_DEBUGGING
#ifndef  _ITERATOR_DEBUG_LEVEL
#define  _ITERATOR_DEBUG_LEVEL 0
#endif  // _ITERATOR_DEBUG_LEVEL

#include <list>
#include <vector>
#include <algorithm>
#include <map>
#include <string>
#include <fstream>
#include <iostream>
#include <memory>
#include <cstdint>
#include <typeinfo>
#include <random>

//*****************************************************************************
// その他のライブラリのファイル

// directX9
#include <d3d9.h>
#include <d3dx9.h>
#ifndef _RELEASE
#include <DxErr.h>
#endif // _RELEASE

#pragma comment (lib, "d3d9.lib")
#if defined(DEBUG) || defined(_DEBUG)
#pragma comment (lib,"d3dx9d.lib")
#else
#pragma comment (lib, "d3dx9.lib")
#endif
#pragma comment (lib, "winmm.lib")
#pragma comment (lib, "dxerr.lib")

// input
#define DIRECTINPUT_VERSION (0x0800)
#include <dinput.h>
#pragma comment (lib, "dinput8.lib")// input関係
#pragma comment (lib, "dxguid.lib")

// sound
#include <xact3.h>
#include <xact3d3.h>
#pragma comment (lib, "X3daudio.lib")

// デバッグ時のみメモリリーク検出を行う
#ifndef _RELEASE
#define _CRTDBG_MAP_ALLOC
#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <crtdbg.h>
#endif  // _RELEASE

// デバッグ時のみメモリリークの位置検出を行う。
#ifndef _RELEASE
#define new					new(_NORMAL_BLOCK, __FILE__, __LINE__)
#define malloc(s)			_malloc_dbg(s, _NORMAL_BLOCK, __FILE__, __LINE__)
#define calloc(c, s)		_calloc_dbg(c, s, _NORMAL_BLOCK, __FILE__, __LINE__)
#define realloc(p, s)		_realloc_dbg(p, s, _NORMAL_BLOCK, __FILE__, __LINE__)
#define _recalloc(p, c, s)	_recalloc_dbg(p, c, s, _NORMAL_BLOCK, __FILE__, __LINE__)
#define _expand(p, s)		_expand_dbg(p, s, _NORMAL_BLOCK, __FILE__, __LINE__)
#endif  // _RELEASE


// 書式付きOutputDebugString
#define MyOutputDebugString( str, ... ) \
{ \
	wchar_t c[256]; \
	swprintf_s(c, str, __VA_ARGS__); \
	OutputDebugString(c); \
}



//*****************************************************************************
// 自作ヘッダインクルード
#include "type_alias.h"
#include "Common/safe_delete.h"
#include "Common/safe_release.h"
#include "Common/reference.h"
#include "Error/assert.h"

