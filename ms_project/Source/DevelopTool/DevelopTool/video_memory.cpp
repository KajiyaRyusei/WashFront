//==============================================================================
//
// �r�f�I�������[
// Author : Humito Kimura
//          Yoshimoto Ryo
//
//==============================================================================
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// include
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include "video_memory.h"
#include "debug_print.h"

namespace vg {
namespace develop_tool{
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//constant
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//���K�o�C�g�P��
const float kMegaBytes = 1000000.0f;

//=============================================================================
//������
//=============================================================================
void VideoMemory::Inisialize(HMONITOR handle_monitor){

#ifdef _RELEASE
  UNREFERENCED_PARAMETER(handle_monitor);
#else
  b_got_memory_ = false;
  //�n���h���擾
  handle_dxgi_ = LoadLibraryA("dxgi.dll");
  if (handle_dxgi_)
  {
    //�V�����^ LpCreateDxgiFactory
    typedef HRESULT(WINAPI* LpCreateDxgiFactory)(REFIID, void**);

    LpCreateDxgiFactory p_create_dxgi_factory = NULL;

    //DLL������CreateDXGIFactory�̊֐��A�h���X�擾
    p_create_dxgi_factory = (LpCreateDxgiFactory)GetProcAddress(handle_dxgi_, "CreateDXGIFactory");
    //GUID��DXGI�I�u�W�F�N�g�ݒ�
    p_create_dxgi_factory(__uuidof(IDXGIFactory), (PVOID*)&p_dxgi_factory_);
    
    for (int in = 0;; ++in)
    {
      //�A�_�v�^��v�t���O
      bool b_found_matching_adapter = false;
      //�A�_�v�^�[��(�A�_�v�^�[�擾)
      HRESULT hr = p_dxgi_factory_->EnumAdapters(in, &p_adapter_);
      
      if (hr)
        break;
      
      for (int out = 0;; ++out)
      {
        //�A�_�v�^�[�o��
        IDXGIOutput *p_output = NULL;
        //�o�͂��
        hr = p_adapter_->EnumOutputs(out, &p_output);
        
        if (hr)
          break;
        
        //�A�_�v�^�[�ƃf�o�C�X�Ԃ̏o�́A�����ڑ��̋L�q
        DXGI_OUTPUT_DESC outputDesc;
        ZeroMemory(&outputDesc, sizeof(outputDesc));
        
        //�o�͂̋L�q���擾
        if (SUCCEEDED(p_output->GetDesc(&outputDesc)))
        {
          //���j�^�[����v������A�_�v�^�[��v�t���Otrue
          if (handle_monitor == outputDesc.Monitor)
          {
            b_found_matching_adapter = true;
          }
        }
        
        p_output->Release();
        p_output = NULL;
      }
      
      //���j�^�[��v������
      if (b_found_matching_adapter)
      {
        //�A�_�v�^�[�܂��̓r�f�I�J�[�h�̋L�q
        DXGI_ADAPTER_DESC adapter_desc;
        ZeroMemory(&adapter_desc, sizeof(DXGI_ADAPTER_DESC));
        //�o�͂̋L�q�擾
        if (SUCCEEDED(p_adapter_->GetDesc(&adapter_desc)))
        {
          b_got_memory_ = true;
          break;
        }
      }
    }//for (int in = 0; ; ++in)
  }//if(handle_dxgi)
#endif // _RELEASE
}
//=============================================================================
//�I��
//=============================================================================
void VideoMemory::Finalize(){

#ifdef _RELEASE
#else
  //�f�B�X�v���C�T�u�V�X�e��
  common::SafeRelease(p_adapter_);
  
  //DXGI�C���^�[�t�F�[�X_
  common::SafeRelease(p_dxgi_factory_);
  
  //DXGI���
  FreeLibrary(handle_dxgi_);
#endif // _RELEASE
}
//=============================================================================
//�r�f�I�������[�c�ʕ\��
//=============================================================================
void VideoMemory::DispVideoMemoryViaDXGI(HMONITOR handle_monitor){

#ifdef _RELEASE
  UNREFERENCED_PARAMETER(handle_monitor);
#else
  if (handle_dxgi_ && b_got_memory_)
  {
    //�A�_�v�^��v�t���O
    bool b_found_matching_adapter = false;

    for (int out = 0;; ++out)
    {
      //�A�_�v�^�[�o��
      IDXGIOutput *p_output = NULL;
      //�o�͂��
      HRESULT hr = p_adapter_->EnumOutputs(out, &p_output);

      if (hr)
        break;

      //�A�_�v�^�[�ƃf�o�C�X�Ԃ̏o�́A�����ڑ��̋L�q
      DXGI_OUTPUT_DESC outputDesc;
      ZeroMemory(&outputDesc, sizeof(outputDesc));

      //�o�͂̋L�q���擾
      if (SUCCEEDED(p_output->GetDesc(&outputDesc)))
      {
        //���j�^�[����v������A�_�v�^�[��v�t���Otrue
        if (handle_monitor == outputDesc.Monitor)
        {
          b_found_matching_adapter = true;
        }
      }
    
      p_output->Release();
      p_output = NULL;
    }
  
    //���j�^�[��v������
    if (b_found_matching_adapter)
    {
      //�A�_�v�^�[�܂��̓r�f�I�J�[�h�̋L�q
      DXGI_ADAPTER_DESC adapter_desc;
      ZeroMemory(&adapter_desc, sizeof(DXGI_ADAPTER_DESC));
      //�o�͂̋L�q�擾
      if (SUCCEEDED(p_adapter_->GetDesc(&adapter_desc)))
      {
        //�e�������̕\��
        DebugPrint::PrintDebug(TEXT("\nDedicatedVideoMemory:%fMB"), (float)(adapter_desc.DedicatedVideoMemory / kMegaBytes));
        DebugPrint::PrintDebug(TEXT("\nDedicatedSystemMemory:%fMB"), (float)(adapter_desc.DedicatedSystemMemory / kMegaBytes));
        DebugPrint::PrintDebug(TEXT("\nSharedSystemMemory:%fMB"), (float)(adapter_desc.SharedSystemMemory / kMegaBytes));
      }
    }

  }//if(handle_dxgi)
#endif // _RELEASE
}
}// namespace develop_tool
}// namespace vg
//EOF