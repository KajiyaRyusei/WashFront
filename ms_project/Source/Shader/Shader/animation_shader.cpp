//==============================================================================
//
// アニメーションシェーダ
//
// Created by Ryusei Kajiya on 20151014
//
//==============================================================================

//*****************************************************************************
// include
#include "animation_shader.h"
#include "Shader/effect_handle_holder.h"


// static
u32 ShaderAnimation::s_effect_id = 0;

void ShaderAnimation::Initialize()
{
	InitializeWorldViewProjection(_effect_handle_holder->effect_handle());
	InitializeLightDirection(_effect_handle_holder->effect_handle());
	InitializeAnimationMatrix(_effect_handle_holder->effect_handle());
}

void ShaderAnimation::AssignExceptMaterial() const
{
	SendLightDirection(_effect_handle_holder->effect_handle());
	SendWorldViewProjection(_effect_handle_holder->effect_handle());
	SendAnimationMatrix(_effect_handle_holder->effect_handle());
}