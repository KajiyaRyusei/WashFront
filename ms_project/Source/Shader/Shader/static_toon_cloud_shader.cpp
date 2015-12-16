//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// 静的雲用トゥーンシェーダー
//
// Created by Ryusei Kajiya on 20151215
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//*****************************************************************************
// include
#include "static_toon_cloud_shader.h"
#include "Shader/effect_handle_holder.h"


// static
u32 ShaderStaticToonCloud::s_effect_id = 0;

void ShaderStaticToonCloud::Initialize()
{
	InitializeLightDirection(_effect_handle_holder->effect_handle());
	InitializeDiffuseCubeMap(_effect_handle_holder->effect_handle());
	InitializeToonTexture(_effect_handle_holder->effect_handle());
	InitializeView(_effect_handle_holder->effect_handle());
	InitializeViewProjection(_effect_handle_holder->effect_handle());
}

void ShaderStaticToonCloud::AssignExceptMaterial() const
{
	SendLightDirection(_effect_handle_holder->effect_handle());
	SendDiffuseCubeMap(_effect_handle_holder->effect_handle());
	SendToonTexture(_effect_handle_holder->effect_handle());
	SendView(_effect_handle_holder->effect_handle());
	SendViewProjection(_effect_handle_holder->effect_handle());
}