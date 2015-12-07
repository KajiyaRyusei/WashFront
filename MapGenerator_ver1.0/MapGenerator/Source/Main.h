//=============================================================================
//
// メイン処理 [Main.h]
// Author : KEITA OHUCHI
//
//=============================================================================
#ifndef _MAIN_H_
#define _MAIN_H_


//-----------------------------------------------------------------------------
// インクルード
//-----------------------------------------------------------------------------
// Warning対策
#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <windows.h>
#include "Renderer.h"

// メモリリーク検出
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>


//-----------------------------------------------------------------------------
// マクロ定義
//-----------------------------------------------------------------------------
#define SCREEN_WIDTH (640)	// ウインドウの幅
#define SCREEN_HEIGHT (360)	// ウインドウの高さ


//-----------------------------------------------------------------------------
// 列挙型定義
//-----------------------------------------------------------------------------
enum MODE {
	MODE_NONE = (0),
	MODE_OBJECT,
	MODE_ROUTE,
	MODE_DIRT,
	MODE_MAX
};


//-----------------------------------------------------------------------------
// プロトタイプ宣言
//-----------------------------------------------------------------------------
HWND GetWindowHandle();


//-----------------------------------------------------------------------------
// インライン関数定義
//-----------------------------------------------------------------------------
// 角度の正規化
static inline void NormalizeRotation(float &r) {
	if (r < -D3DX_PI) {
		r += D3DX_PI * 2;
	} else if (D3DX_PI < r) {
		r -= D3DX_PI * 2;
	}
};

// ポインタの安全な開放処理
template <class T>
static inline void SafeDelete(T*& p) {
	if (p) {
		delete p;
		p = nullptr;
	}
};
// ポインタ配列の安全な開放処理
template <class T>
static inline void SafeDeleteArray(T*& p) {
	if (p) {
		delete[] p;
		p = nullptr;
	}
};
// リリース族の安全な開放処理
template <class T>
static inline void SafeRelease(T*& p) {
	if (p) {
		p->Release();
		p = nullptr;
	}
};


// メモリリーク検出
#ifdef _DEBUG
//#define new new(_NORMAL_BLOCK, __FILE__, __LINE__)
#endif


//-----------------------------------------------------------------------------
// プロトタイプ宣言
//-----------------------------------------------------------------------------
//=============================================================================
// FPSの取得
//=============================================================================
float GetFps();

HWND GetObjectDialogHandle();
HWND GetRouteDialogHandle();
HWND GetDirtDialogHandle();
MODE GetMode();

#endif


// End of file