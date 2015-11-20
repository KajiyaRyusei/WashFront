//=============================================================================
//
// デバッグクラス [Debug.cpp]
// Author : KEITA OHUCHI
//
//=============================================================================

#include "Debug.h"
#include "Manager.h"
#include "Main.h"
#include <stdio.h>
#include <tchar.h>


//-----------------------------------------------------------------------------
// 静的メンバ変数
//-----------------------------------------------------------------------------
LPD3DXFONT DebugProc::font_ = nullptr;
char DebugProc::string_[STR_MAX] = {};


//=============================================================================
// コンストラクタ
//=============================================================================
DebugProc::DebugProc()
{
	font_ = nullptr;
	memset(string_, 0, sizeof(string_));
}

//=============================================================================
// デストラクタ
//
// DATE : 2014/05/13
//=============================================================================
DebugProc::~DebugProc()
{

	// フォントポインタの解放
	SafeRelease(font_);

}

//=========================================================================
// 初期化処理
//=========================================================================
HRESULT DebugProc::Init()
{
	// デバイスの取得
	Renderer *renderer = Manager::GetInstance()->GetRenderer();
	LPDIRECT3DDEVICE9 device = renderer->GetDevice();

	// フォントの生成
	D3DXCreateFont(device, 18, 0, 0, 0, FALSE, SHIFTJIS_CHARSET,
				   OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH,
				   "Terminal", &font_);

	return S_OK;
}

//=========================================================================
// 更新処理
//=========================================================================
void DebugProc::Update()
{
	// 文字列初期化
	memset(string_, 0, sizeof(string_));
}

//=========================================================================
// 描画処理
//=========================================================================
void DebugProc::Draw()
{
	// 描画範囲
	RECT rect;
	rect.left = 0;
	rect.top = 0;
	rect.right = SCREEN_WIDTH;
	rect.bottom = SCREEN_HEIGHT;

	// テキスト描画
	font_->DrawText(nullptr, string_, -1, &rect, DT_LEFT,
					 D3DXCOLOR(1.0f, 0.0f, 0.3f, 1.0f));
}

#ifdef _DEBUG
//=========================================================================
// 表示命令
//=========================================================================
void DebugProc::Printf(char *fmt, ...)
{
	// 可変引数リスト
	va_list list;
	char *cur;
	char buf[256] = {0};
	char work[32];

	// 可変引数アクセスの前処理
	va_start(list, fmt);
	// カーソルを引数文字列の先頭へ
	cur = fmt;

	// 引数文字列が終了するまでループ
	for ( ; *cur; ++cur) {
		if (*cur != '%') {
			// 一文字保存
			_stprintf_s(work, "%c", *cur);
		} else {
			cur++;
			switch (*cur) {
			case 'c':
				// 文字列保存
				_stprintf_s(work, "%c", va_arg(list, char));
				break;

			case 'd':
				// 整数値保存
				_stprintf_s(work, "%d", va_arg(list, int));
				break;

			case 'f':
				// ※可変長引数はfloatはdouble型に変換される
				_stprintf_s(work, "%.2lf", va_arg(list, double));
				break;
			}
		}
		// ワークの内容をバッファに付け加える
		strcat_s(buf, work);
	}

	// 可変引数アクセス後処理
	va_end(list);
	// バッファの内容をメンバ変数に付け加える
	strcat_s(string_, buf);
}
#endif


// End of file