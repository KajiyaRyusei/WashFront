//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// 静的ビル用トゥーンシェーダー
//
// Created by Ryusei Kajiya on 20151215
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//*****************************************************************************
// include
#include "static_toon_building_shader.h"
#include "Shader/effect_handle_holder.h"


// static
u32 ShaderStaticToonBuilding::s_effect_id = 0;

void ShaderStaticToonBuilding::Initialize()
{
	InitializeWorldViewProjection(_effect_handle_holder->effect_handle());
	InitializeLightDirection(_effect_handle_holder->effect_handle());
	InitializeDiffuseCubeMap(_effect_handle_holder->effect_handle());
	InitializeAlbedoTexture(_effect_handle_holder->effect_handle());
	InitializeNormalTexture(_effect_handle_holder->effect_handle());
	InitializeToonTexture(_effect_handle_holder->effect_handle());
	InitializeView(_effect_handle_holder->effect_handle());
	InitializeWorld(_effect_handle_holder->effect_handle());
}

void ShaderStaticToonBuilding::AssignExceptMaterial() const
{
	SendWorldViewProjection(_effect_handle_holder->effect_handle());
	SendLightDirection(_effect_handle_holder->effect_handle());
	SendDiffuseCubeMap(_effect_handle_holder->effect_handle());
	SendAlbedoTexture(_effect_handle_holder->effect_handle());
	SendNormalTexture(_effect_handle_holder->effect_handle());
	SendToonTexture(_effect_handle_holder->effect_handle());
	SendView(_effect_handle_holder->effect_handle());
	SendWorld(_effect_handle_holder->effect_handle());
}