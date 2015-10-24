//==============================================================================
//
// 背景専用シェーダー
//
// Created by Ryusei Kajiya on 20151022
//
//==============================================================================

//*****************************************************************************
// include
#include "back_ground_shader.h"
#include "Shader/effect_handle_holder.h"


// static
u32 ShaderBackGround::s_effect_id = 0;

void ShaderBackGround::Initialize()
{
	InitializeWorldViewProjection(_effect_handle_holder->effect_handle());
	InitializeAlbedoCubeTexture(_effect_handle_holder->effect_handle());
}

void ShaderBackGround::AssignExceptMaterial() const
{
	SendAlbedoCubeTexture(_effect_handle_holder->effect_handle());
	SendWorldViewProjection(_effect_handle_holder->effect_handle());
}