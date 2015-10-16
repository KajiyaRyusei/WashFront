//==============================================================================
//
// デバッグ表示[debug_print.h]
// Author : Shirakawa Taiga
//
//==============================================================================

//==============================================================================
// インクルード
//==============================================================================
#include <stdarg.h>
#include "develop_tool\debug_print.h"
#include "resources/container_manager.h"
#include "resources/container/resource_container.h"
#include "resources/container/lost_resource_container.h"
#include "device_resource/dx_font/dx_font_holder.h"

using namespace vg::develop_tool;

vg::resources::ContainerManager* DebugPrint::container_manager_ = nullptr;

//==============================================================================
// 静的メンバ変数宣言
//==============================================================================
#ifndef _RELEASE
const s32     DebugPrint::MAX_LENGTH_ONCE = 256;  // 一度に送れる文字数

vg::device_resource::dx_font::DXFontHolder*    DebugPrint::font_holder_ = nullptr;       // フォントへのポインタ
TCHAR*        DebugPrint::pBuffer_ = nullptr;     // 描画文字列バッファ
bool          DebugPrint::isVisible_ = true;      // デバッグ情報表示フラグ
bool          DebugPrint::createFont = true;      // フォント生成フラグ
bool          DebugPrint::warninged = false;      // 警告フラグ
RECT          DebugPrint::rectShow_;              // 表示領域
D3DXCOLOR     DebugPrint::color_;                 // 表示文字色
s32           DebugPrint::sizeBuffer_ = 0;        // バッファのサイズ
s32           DebugPrint::cursorBuffer_ = 0;      // バッファのカーソル
#endif

//==============================================================================
// 初期化処理
//==============================================================================
HRESULT DebugPrint::Initialize(IDirect3DDevice9* pDevice) {
#ifdef _RELEASE
  UNREFERENCED_PARAMETER(pDevice);
#else
  // 共通の初期化
  InitializeCommon(8192, 0, 0, 1280, 960, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

  // 情報表示用フォントを生成
  LPD3DXFONT pFont = nullptr;
  vg::device_resource::dx_font::DXFontHolder::CREATE_DATA data(
    18, 0, 0, 0, FALSE,
    SHIFTJIS_CHARSET, OUT_DEFAULT_PRECIS,
    DEFAULT_QUALITY, DEFAULT_PITCH,
    "Terminal");
  if (FAILED(D3DXCreateFontA(pDevice, data.height, data.width,
                            data.weight, data.mip_level, data.italic,
                            data.character_set, data.output_precision,
                            data.quality, data.pitch_and_family,
                            data.font_name, &pFont))) {
    return E_FAIL;
  }
  font_holder_ = new vg::device_resource::dx_font::DXFontHolder(pFont, data);
  container_manager_->resource_container()->push_back(font_holder_);
  container_manager_->lost_resource_container()->push_back(font_holder_);

#endif
  // 正常終了
  return S_OK;
}

//==============================================================================
// 初期化処理
//==============================================================================
HRESULT DebugPrint::Initialize(IDirect3DDevice9* pDevice, s32 sizeBuffer,
                                   LONG left, LONG top, LONG right, LONG bottom,
                                   D3DXCOLOR color, s32 sizeFont) {
#ifdef _RELEASE
  UNREFERENCED_PARAMETER(pDevice);
  UNREFERENCED_PARAMETER(sizeBuffer);
  UNREFERENCED_PARAMETER(left);
  UNREFERENCED_PARAMETER(top);
  UNREFERENCED_PARAMETER(right);
  UNREFERENCED_PARAMETER(bottom);
  UNREFERENCED_PARAMETER(color);
  UNREFERENCED_PARAMETER(sizeFont);
#else
  // 共通の初期化
  InitializeCommon(sizeBuffer, left, top, right, bottom, color);

  LPD3DXFONT pFont = nullptr;
  vg::device_resource::dx_font::DXFontHolder::CREATE_DATA data(
    sizeFont, 0, 0, 0, FALSE,
    SHIFTJIS_CHARSET, OUT_DEFAULT_PRECIS,
    DEFAULT_QUALITY, DEFAULT_PITCH,
    "Terminal");
  // 情報表示用フォントを生成
  if (FAILED(D3DXCreateFontA(pDevice, data.height, data.width,
                            data.weight, data.mip_level, data.italic,
                            data.character_set, data.output_precision,
                            data.quality, data.pitch_and_family,
                            data.font_name, &pFont))) {
    return E_FAIL;
  }
  font_holder_ = new vg::device_resource::dx_font::DXFontHolder(pFont, data);
  container_manager_->resource_container()->push_back(font_holder_);
  container_manager_->lost_resource_container()->push_back(font_holder_);
#endif
  // 正常終了
  return S_OK;
}

//==============================================================================
// 初期化処理
//==============================================================================
HRESULT DebugPrint::Initialize(ID3DXFont* pFont, s32 sizeBuffer,
                                   LONG left, LONG top, LONG right, LONG bottom,
                                   D3DXCOLOR color) {
#ifdef _RELEASE
  UNREFERENCED_PARAMETER(pFont);
  UNREFERENCED_PARAMETER(sizeBuffer);
  UNREFERENCED_PARAMETER(left);
  UNREFERENCED_PARAMETER(top);
  UNREFERENCED_PARAMETER(right);
  UNREFERENCED_PARAMETER(bottom);
  UNREFERENCED_PARAMETER(color);
#else
  // 共通の初期化
  InitializeCommon(sizeBuffer, left, top, right, bottom, color);

  vg::device_resource::dx_font::DXFontHolder::CREATE_DATA data(
    18, 0, 0, 0, FALSE,
    SHIFTJIS_CHARSET, OUT_DEFAULT_PRECIS,
    DEFAULT_QUALITY, DEFAULT_PITCH,
    "Terminal");

  // 渡されたフォントを格納
  createFont = false;
  font_holder_ = new vg::device_resource::dx_font::DXFontHolder(pFont, data);
  container_manager_->resource_container()->push_back(font_holder_);
  container_manager_->lost_resource_container()->push_back(font_holder_);
#endif
  // 正常終了
  return S_OK;
}

#ifndef _RELEASE
//==============================================================================
// 共通初期化処理
//==============================================================================
void DebugPrint::InitializeCommon(s32 sizeBuffer,
                                      LONG left, LONG top, LONG right, LONG bottom,
                                      D3DXCOLOR color) {
  // 静的メンバ変数の初期化
  font_holder_ = nullptr;
  pBuffer_ = nullptr;
  isVisible_ = true;
  createFont = true;
  warninged = false;
  rectShow_.left = rectShow_.top = rectShow_.right = rectShow_.bottom = 0;
  color_.r = color_.g = color_.b = color_.a = 0.0f;
  sizeBuffer_ = 0;
  cursorBuffer_ = 0;

  // 引数から設定
  rectShow_.left = left;
  rectShow_.top = top;
  rectShow_.right = right;
  rectShow_.bottom = bottom;
  color_ = color;
  sizeBuffer_ = sizeBuffer;

  // バッファの確保
  pBuffer_ = new TCHAR[sizeBuffer];
  ZeroMemory(pBuffer_, sizeof(TCHAR)* sizeBuffer);
}
#endif

//==============================================================================
// 終了処理
//==============================================================================
void DebugPrint::Finalize(void) {
#ifndef _RELEASE
  // フォントの開放
  if (font_holder_) {
    font_holder_->KillMySelf();
    font_holder_ = nullptr;
  }

  // バッファの開放
  delete[] pBuffer_;
  pBuffer_ = nullptr;
#endif
}

//==============================================================================
// 更新処理
//==============================================================================
void DebugPrint::Update(void) {
}

//==============================================================================
// 描画処理
//==============================================================================
void DebugPrint::Draw(void) {
#ifndef _RELEASE
  // デバッグ情報非表示
  if (!isVisible_) {
    return;
  }

  // テキスト描画
  font_holder_->font()->DrawText(nullptr, pBuffer_, -1, &rectShow_, DT_LEFT, color_);
#endif
}

//==============================================================================
// バッファクリア処理
//==============================================================================
void DebugPrint::ClearBuffer(void) {
#ifndef _RELEASE
  // バッファクリア
  ZeroMemory(pBuffer_, sizeof(TCHAR)* sizeBuffer_);
  cursorBuffer_ = 0;
#endif
}

//==============================================================================
// 表示デバッグ文字列格納処理
//==============================================================================
void DebugPrint::PrintDebug(const TCHAR *pFormat, ...) {
#ifdef _RELEASE
  UNREFERENCED_PARAMETER(pFormat);
#else
  TCHAR   argumentBuffer[MAX_LENGTH_ONCE] = _T("");   // 引数込の文字列
  va_list args;                                       // 引数

  // デバッグ情報非表示
  if (!isVisible_) {
    return;
  }

#ifdef _RELEASE
  if (!warninged) {
    // 暫定 ( Assertの代わり )
    MessageBox(nullptr, _T("DebugPrint::Print()を使用してください"), _T("エラー"), MB_OK);
    warninged = true;
    _asm int 3;
  }
#endif

  // エラーチェック
  if (font_holder_ == nullptr || font_holder_->font() == nullptr) {
    return;
  }

  // 表示文字列作成
  va_start(args, pFormat);
  _vsntprintf_s(&argumentBuffer[0], MAX_LENGTH_ONCE, _TRUNCATE, pFormat, args);
  va_end(args);

  // 表示文字列記録
  _tcscat_s(pBuffer_, sizeBuffer_, &argumentBuffer[0]);
#endif
}