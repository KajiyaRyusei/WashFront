//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// 水しぶきパーティクル用シェーダ
//
// Created by Ryusei Kajiya on 20151125
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//*****************************************************************************
// include
#include "Shader/Shader/water_spray_shader.h"
#include "Shader/effect_handle_holder.h"


u32 ShaderWaterSpray::s_effect_id = 0;

void ShaderWaterSpray::Initialize()
{
	InitializeAlbedoTexture(_effect_handle_holder->effect_handle());
	InitializeViewProjection(_effect_handle_holder->effect_handle());
}

void ShaderWaterSpray::AssignExceptMaterial() const
{
	SendAlbedoTexture(_effect_handle_holder->effect_handle());
	SendViewProjection(_effect_handle_holder->effect_handle());
}
