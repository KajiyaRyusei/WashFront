//==============================================================================
//
// ビデオメモリー
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
//メガバイト単位
const float kMegaBytes = 1000000.0f;

//=============================================================================
//初期化
//=============================================================================
void VideoMemory::Inisialize(HMONITOR handle_monitor){

#ifdef _RELEASE
  UNREFERENCED_PARAMETER(handle_monitor);
#else
  b_got_memory_ = false;
  //ハンドル取得
  handle_dxgi_ = LoadLibraryA("dxgi.dll");
  if (handle_dxgi_)
  {
    //新しい型 LpCreateDxgiFactory
    typedef HRESULT(WINAPI* LpCreateDxgiFactory)(REFIID, void**);

    LpCreateDxgiFactory p_create_dxgi_factory = NULL;

    //DLLが持つCreateDXGIFactoryの関数アドレス取得
    p_create_dxgi_factory = (LpCreateDxgiFactory)GetProcAddress(handle_dxgi_, "CreateDXGIFactory");
    //GUIDとDXGIオブジェクト設定
    p_create_dxgi_factory(__uuidof(IDXGIFactory), (PVOID*)&p_dxgi_factory_);
    
    for (int in = 0;; ++in)
    {
      //アダプタ一致フラグ
      bool b_found_matching_adapter = false;
      //アダプター列挙(アダプター取得)
      HRESULT hr = p_dxgi_factory_->EnumAdapters(in, &p_adapter_);
      
      if (hr)
        break;
      
      for (int out = 0;; ++out)
      {
        //アダプター出力
        IDXGIOutput *p_output = NULL;
        //出力を列挙
        hr = p_adapter_->EnumOutputs(out, &p_output);
        
        if (hr)
          break;
        
        //アダプターとデバイス間の出力、物理接続の記述
        DXGI_OUTPUT_DESC outputDesc;
        ZeroMemory(&outputDesc, sizeof(outputDesc));
        
        //出力の記述を取得
        if (SUCCEEDED(p_output->GetDesc(&outputDesc)))
        {
          //モニターを一致したらアダプター一致フラグtrue
          if (handle_monitor == outputDesc.Monitor)
          {
            b_found_matching_adapter = true;
          }
        }
        
        p_output->Release();
        p_output = NULL;
      }
      
      //モニター一致したら
      if (b_found_matching_adapter)
      {
        //アダプターまたはビデオカードの記述
        DXGI_ADAPTER_DESC adapter_desc;
        ZeroMemory(&adapter_desc, sizeof(DXGI_ADAPTER_DESC));
        //出力の記述取得
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
//終了
//=============================================================================
void VideoMemory::Finalize(){

#ifdef _RELEASE
#else
  //ディスプレイサブシステム
  common::SafeRelease(p_adapter_);
  
  //DXGIインターフェース_
  common::SafeRelease(p_dxgi_factory_);
  
  //DXGI解放
  FreeLibrary(handle_dxgi_);
#endif // _RELEASE
}
//=============================================================================
//ビデオメモリー残量表示
//=============================================================================
void VideoMemory::DispVideoMemoryViaDXGI(HMONITOR handle_monitor){

#ifdef _RELEASE
  UNREFERENCED_PARAMETER(handle_monitor);
#else
  if (handle_dxgi_ && b_got_memory_)
  {
    //アダプタ一致フラグ
    bool b_found_matching_adapter = false;

    for (int out = 0;; ++out)
    {
      //アダプター出力
      IDXGIOutput *p_output = NULL;
      //出力を列挙
      HRESULT hr = p_adapter_->EnumOutputs(out, &p_output);

      if (hr)
        break;

      //アダプターとデバイス間の出力、物理接続の記述
      DXGI_OUTPUT_DESC outputDesc;
      ZeroMemory(&outputDesc, sizeof(outputDesc));

      //出力の記述を取得
      if (SUCCEEDED(p_output->GetDesc(&outputDesc)))
      {
        //モニターを一致したらアダプター一致フラグtrue
        if (handle_monitor == outputDesc.Monitor)
        {
          b_found_matching_adapter = true;
        }
      }
    
      p_output->Release();
      p_output = NULL;
    }
  
    //モニター一致したら
    if (b_found_matching_adapter)
    {
      //アダプターまたはビデオカードの記述
      DXGI_ADAPTER_DESC adapter_desc;
      ZeroMemory(&adapter_desc, sizeof(DXGI_ADAPTER_DESC));
      //出力の記述取得
      if (SUCCEEDED(p_adapter_->GetDesc(&adapter_desc)))
      {
        //各メモリの表示
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