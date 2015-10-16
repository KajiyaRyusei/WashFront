//==============================================================================
//
// �����_�[�^�[�Q�b�g�̕\��[debug_render_target.h]
// Author : RYUSEI KAJIYA
//          HUMITO KIMURA
//          TOSHIHIKO TSUKAMOTO
//
// [�T�v]
// �����_�����O�^�[�Q�b�g����ʂɕ\�����܂��B
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

  // �����_�[�^�[�Q�b�g�̐ݒ�
  bool SetRenderTarget(resources::interfaces::ITexture** texture,
                       u32 target_number);

  // �����_�[�^�[�Q�b�g�̕`��
  void Draw();

  // �t���O�؂�ւ�
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
