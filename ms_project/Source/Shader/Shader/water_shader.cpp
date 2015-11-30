//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// …
//
// Created by Ryusei Kajiya on 20151114
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//*****************************************************************************
// include
#include "water_shader.h"
#include "Shader/effect_handle_holder.h"


// static
u32 ShaderWater::s_effect_id = 0;

void ShaderWater::Initialize()
{
	InitializeWorldViewProjection(_effect_handle_holder->effect_handle());
	InitializeWorld(_effect_handle_holder->effect_handle());
	InitializeLightDirection(_effect_handle_holder->effect_handle());
	InitializeEyePosition(_effect_handle_holder->effect_handle());
	InitializeRoughness(_effect_handle_holder->effect_handle());
	InitializeMetalness(_effect_handle_holder->effect_handle());
	InitializeFresnel(_effect_handle_holder->effect_handle());
	InitializeAmbientColor(_effect_handle_holder->effect_handle());
	InitializeAlbedoTexture(_effect_handle_holder->effect_handle());
	InitializeTexcoordMove(_effect_handle_holder->effect_handle());
	InitializeWaterMatrix(_effect_handle_holder->effect_handle());
	InitializeNormalTexture(_effect_handle_holder->effect_handle());
}

void ShaderWater::AssignExceptMaterial() const
{
	SendWorldViewProjection(_effect_handle_holder->effect_handle());
	SendWorld(_effect_handle_holder->effect_handle());
	SendLightDirection(_effect_handle_holder->effect_handle());
	SendEyePosition(_effect_handle_holder->effect_handle());
	SendRoughness(_effect_handle_holder->effect_handle());
	SendMetalness(_effect_handle_holder->effect_handle());
	SendFresnel(_effect_handle_holder->effect_handle());
	SendAmbientColor(_effect_handle_holder->effect_handle());
	SendAlbedoTexture(_effect_handle_holder->effect_handle());
	SendTexcoordMove(_effect_handle_holder->effect_handle());
	SendWaterMatrix(_effect_handle_holder->effect_handle());
	SendNormalTexture(_effect_handle_holder->effect_handle());
}