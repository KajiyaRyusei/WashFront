//==============================================================================
//
// レンダーターゲットの表示[debug_render_target.h]
// Author : RYUSEI KAJIYA
//          HUMITO KIMURA
//          TOSHIHIKO TSUKAMOTO
//
// [概要]
// レンダリングターゲットを画面に表示します。
//
//==============================================================================
#pragma once
#ifndef VG_DEVELOPTOOL_DEBUG_RENDER_TARGET_H_
#define VG_DEVELOPTOOL_DEBUG_RENDER_TARGET_H_

namespace vg {
namespace resources {
namespace interfaces {
class ITexture;
}
}
}

namespace vg {
namespace develop_tool{

class DebugRenderTarget{
public:

  DebugRenderTarget();

  // レンダーターゲットの設定
  bool SetRenderTarget(resources::interfaces::ITexture** texture,
                       u32 target_number);

  // レンダーターゲットの描画
  void Draw();

  // フラグ切り替え
  void ChangeUseFlg(){
    use = !use;
  }

private:

  enum{kMaxRenderTarget = 4};

  resources::interfaces::ITexture** textures_[kMaxRenderTarget];
  bool use;

};

} // namespace develop_tool
} // namespace vg

#endif  // VG_DEVELOPTOOL_DEBUG_RENDER_TARGET_H_
