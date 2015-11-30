//==============================================================================
//
// ビデオメモリー
// Author : Humito Kimura
//          Yoshimoto Ryo
//
// ビデオメモリークラス
//
//==============================================================================
#pragma once
#ifndef VG_DEBUG_VIDEO_MEMORY_H_
#define VG_DEBUG_VIDEO_MEMORY_H_

namespace vg {
namespace develop_tool{
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// class definition
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
class VideoMemory{
public:
  VideoMemory(){};
 virtual ~VideoMemory(){};

  //初期化
  void Inisialize(HMONITOR handle_monitor);

  //終了
  void Finalize();

  //ビデオメモリー残量表示
  void DispVideoMemoryViaDXGI(HMONITOR handle_monitor);

#ifndef _RELEASE
private:
  //DXGIハンドル
  HINSTANCE handle_dxgi_;

  //DXGIインターフェース
  IDXGIFactory *p_dxgi_factory_;

  //ディスプレイサブシステム
  IDXGIAdapter *p_adapter_;

  //メモリー取得フラグ
  bool b_got_memory_;
#endif // _RELEASE
};

}// namespace develop_tool
}// namespace vg
#endif //VG_DEBUG_VIDEO_MEMORY_H_
//EOF