//==============================================================================
//
// デバッグ表示[debug_print.h]
// Author : Shirakawa Taiga
//
//==============================================================================
#pragma once
#ifndef VG_DEVELOP_TOOL_DEBUG_PRINT_H_
#define VG_DEVELOP_TOOL_DEBUG_PRINT_H_

namespace vg {
namespace resources {
class ContainerManager;
}
}

namespace vg {
namespace device_resource {
namespace dx_font {
class DXFontHolder;
}
}
}

namespace vg {
namespace develop_tool {

//==============================================================================
// デバッグ表示クラス
//==============================================================================
class DebugPrint
{
 public:
  static HRESULT Initialize(IDirect3DDevice9* pDevice);
  static HRESULT Initialize(IDirect3DDevice9* pDevice, s32 sizeBuffer,
                            LONG left, LONG top, LONG right, LONG bottom,
                            D3DXCOLOR color, s32 sizeFont);
  static HRESULT Initialize(ID3DXFont* pFont, s32 sizeBuffer,
                            LONG left, LONG top, LONG right, LONG bottom,
                            D3DXCOLOR color);
  static void Finalize(void);
  static void Update(void);
  static void Draw(void);
  static void ClearBuffer(void);
  static void PrintDebug(const TCHAR *pFormat, ...);
#ifndef _RELEASE
  static void SetShow(bool isVisible)                                     { isVisible_ = isVisible; }
  static void SetShowRect(LONG left, LONG top, LONG right, LONG bottom)   {
    rectShow_.left = left; rectShow_.top = top; rectShow_.right = right; rectShow_.bottom = bottom;
  }
  static void SetShowRect(RECT rectShow)                                  { rectShow_ = rectShow; }
  static void SetColor(D3DXCOLOR color)                                   { color_ = color; }
#else
  static void SetShow(bool isVisible)                                     { UNREFERENCED_PARAMETER(isVisible); }
  static void SetShowRect(LONG left, LONG top, LONG right, LONG bottom)   {
    UNREFERENCED_PARAMETER(left); UNREFERENCED_PARAMETER(top); UNREFERENCED_PARAMETER(right); UNREFERENCED_PARAMETER(bottom);
  }
  static void SetShowRect(RECT rectShow)                                  { UNREFERENCED_PARAMETER(rectShow); }
  static void SetColor(D3DXCOLOR color)                                   { UNREFERENCED_PARAMETER(color); }
#endif

  static void set_container_manager(
      vg::resources::ContainerManager* container_manager) {
    container_manager_ = container_manager;
  }

private:
  static vg::resources::ContainerManager* container_manager_;
#ifndef _RELEASE
  static const s32  MAX_LENGTH_ONCE;    // 一度に送れる文字数

  DebugPrint(void) {}     // コンストラクタ
  ~DebugPrint(void) {}    // デストラクタ

  static void InitializeCommon(s32 sizeBuffer,
                               LONG left, LONG top, LONG right, LONG bottom,
                               D3DXCOLOR color);

  static vg::device_resource::dx_font::DXFontHolder* font_holder_;
  static TCHAR*     pBuffer_;           // 描画文字列バッファ
  static bool       isVisible_;         // デバッグ情報表示フラグ
  static bool       createFont;         // フォント生成フラグ ( true : このクラス内で生成 )
  static bool       warninged;          // 警告フラグ
  static RECT       rectShow_;          // 表示領域
  static D3DXCOLOR  color_;             // 表示文字色
  static s32        sizeBuffer_;        // バッファのサイズ
  static s32        cursorBuffer_;      // バッファのカーソル
#endif
};
} // namespace develop_tool
} // namespace vg

#endif // VG_DEVELOP_TOOL_DEBUG_PRINT_H_