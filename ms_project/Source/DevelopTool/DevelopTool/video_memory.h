//==============================================================================
//
// �r�f�I�������[
// Author : Humito Kimura
//          Yoshimoto Ryo
//
// �r�f�I�������[�N���X
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

  //������
  void Inisialize(HMONITOR handle_monitor);

  //�I��
  void Finalize();

  //�r�f�I�������[�c�ʕ\��
  void DispVideoMemoryViaDXGI(HMONITOR handle_monitor);

#ifndef _RELEASE
private:
  //DXGI�n���h��
  HINSTANCE handle_dxgi_;

  //DXGI�C���^�[�t�F�[�X
  IDXGIFactory *p_dxgi_factory_;

  //�f�B�X�v���C�T�u�V�X�e��
  IDXGIAdapter *p_adapter_;

  //�������[�擾�t���O
  bool b_got_memory_;
#endif // _RELEASE
};

}// namespace develop_tool
}// namespace vg
#endif //VG_DEBUG_VIDEO_MEMORY_H_
//EOF