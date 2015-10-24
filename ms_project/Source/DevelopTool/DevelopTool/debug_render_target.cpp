//==============================================================================
//
// レンダーターゲットの表示[debug_render_target.cpp]
// Author : RYUSEI KAJIYA
//          HUMITO KIMURA
//          TOSHIHIKO TSUKAMOTO
//
//==============================================================================
#include "debug_render_target.h"
#include "system/device_holder.h"
#include "resources/interfaces/i_texture.h"

namespace vg {
namespace develop_tool{

DebugRenderTarget::DebugRenderTarget()
{
  for (u32 i = 0; i < kMaxRenderTarget; ++i){
    textures_[i] = nullptr;
  }
  use = true;
}

// レンダーターゲットの設定
bool DebugRenderTarget::SetRenderTarget(
  resources::interfaces::ITexture** texture, 
  u32 target_number)
{
  if (target_number >= kMaxRenderTarget){
    return false;
  }

  // テクスチャのポインタを格納
  textures_[target_number] = texture;

  return true;
}

// レンダーターゲットの描画
void DebugRenderTarget::Draw()
{
#ifndef _RELEASE
  LPDIRECT3DDEVICE9 device = common::Reference::Instance().direct3ddevice();

  if (use)
  {
    device->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_SELECTARG1);
    device->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
    device->SetTextureStageState(1, D3DTSS_COLOROP, D3DTOP_DISABLE);

    float rate = 0.2f;
    float width = rate*common::Reference::Instance().screen_width();
    float height = rate*common::Reference::Instance().screen_height();

    typedef struct
    {
      D3DXVECTOR3 vtx;
      float rhw;
      D3DXVECTOR2 tex;

    } VERTEX_2D;

    for (u32 i = 0; i < kMaxRenderTarget; ++i){

      if (textures_[i] != nullptr)
      {
        VERTEX_2D polygon[4] = {
          // x  y  z rhw tu tv
            { { 0.f, height*i, 0.f }, 1, { 0.f, 0.f } },
            { { width, height*i, 0.f }, 1, { 1.f, 0.f } },
            { { 0.f, height*(i + 1), 0.f }, 1, { 0.f, 1.f } },
            { { width, height*(i + 1), 0.f }, 1, { 1.f, 1.f } },
        };

        device->SetTexture(0, (*textures_[i])->p_texture());
        device->SetFVF(D3DFVF_XYZRHW | D3DFVF_TEX1);
        device->SetPixelShader(0);
        device->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, polygon, sizeof(VERTEX_2D));

        // これをやらないとwarningが出る可能性がある(Yoshimoto Ryo)
        device->SetTexture(0, nullptr);
      }
    }
  }
#endif
}

} // namespace develop_tool
} // namespace vg
// EOF