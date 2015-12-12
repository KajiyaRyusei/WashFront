//==============================================================================
//
// Aim—pshader
//
// Created by Ryusei Kajiya on 20151027
//
//==============================================================================

//*****************************************************************************
// include
#include "aim_shader.h"
#include "Shader/effect_handle_holder.h"


// static
u32 ShaderAim::s_effect_id = 0;

void ShaderAim::Initialize()
{
	InitializeWorldViewProjection(_effect_handle_holder->effect_handle());
	InitializeAlbedoTexture(_effect_handle_holder->effect_handle());
	InitializeAmbientColor(_effect_handle_holder->effect_handle());
}

void ShaderAim::AssignExceptMaterial() const
{
	SendWorldViewProjection(_effect_handle_holder->effect_handle());
	SendAlbedoTexture(_effect_handle_holder->effect_handle());
	SendAmbientColor(_effect_handle_holder->effect_handle());
}
