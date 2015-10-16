//==============================================================================
//
// ƒ‰ƒ“ƒo[ƒgÆ–¾
//
// Created by Ryusei Kajiya on 20151008
//
//==============================================================================

//*****************************************************************************
// include
#include "lambert.h"
#include "Shader/effect_handle_holder.h"


// static
u32 ShaderLambert::s_effect_id = 0;

void ShaderLambert::Initialize()
{
	InitializeWorldViewProjection(_effect_handle_holder->effect_handle());
	InitializeLightDirection(_effect_handle_holder->effect_handle());
}

void ShaderLambert::AssignExceptMaterial() const
{
	SendLightDirection(_effect_handle_holder->effect_handle());
	SendWorldViewProjection(_effect_handle_holder->effect_handle());
}