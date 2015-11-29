//==============================================================================
//
// スクリーンに描画する
//
// Created by Ryusei Kajiya on 20151012
//
//==============================================================================

//*****************************************************************************
// 多重インクルード防止
#pragma once

//*****************************************************************************
// include
#include "Shader/shader_base.h"
#include "Shader/Component/screen_size.h"
#include "Shader/Component/screen_matrix.h"
#include "Shader/Component/screen_texture_uv.h"
#include "Shader/Component/screen_texture_offset.h"
#include "Shader/Component/screen_texture_alpha.h"
#include "Shader/Component/ambient_texture.h"

class Shader2D : public ShaderBase, public component::ScreenMatrix, public component::ScreenSize, public component::ScreenTextureUv, 
					public component::ScreenTextureOffset, public component::ScreenTextureAlpha, public component::AmbientTexture
{
public:
	Shader2D() : ShaderBase(s_effect_id) { Initialize(); }
	virtual ~Shader2D() {}
	virtual void Initialize() override;
	virtual void AssignExceptMaterial() const override;

	static void S_SetEffectId(u32 effect_id) { s_effect_id = effect_id; }

private:
	static u32 s_effect_id;
};