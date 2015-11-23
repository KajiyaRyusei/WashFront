//==============================================================================
//
// PBLスタティックシェーダ
//
// Created by Ryusei Kajiya on 20151028
//
//==============================================================================

//*****************************************************************************
// include
#include "PBL_static_shader.h"
#include "Shader/effect_handle_holder.h"


// static
u32 ShaderPBLStatic::s_effect_id = 0;

void ShaderPBLStatic::Initialize()
{
	InitializeWorldViewProjection(_effect_handle_holder->effect_handle());
	InitializeWorld(_effect_handle_holder->effect_handle());
	InitializeLightDirection(_effect_handle_holder->effect_handle());
	InitializeEyePosition(_effect_handle_holder->effect_handle());
	InitializeRoughness(_effect_handle_holder->effect_handle());
	InitializeMetalness(_effect_handle_holder->effect_handle());
	InitializeFresnel(_effect_handle_holder->effect_handle());
	InitializeAmbientColor(_effect_handle_holder->effect_handle());
	InitializeDiffuseCubeMap(_effect_handle_holder->effect_handle());
	InitializeSpecularCubeMap(_effect_handle_holder->effect_handle());
	InitializeAlbedoTexture(_effect_handle_holder->effect_handle());
	InitializeMetalnessMap(_effect_handle_holder->effect_handle());
	InitializeDirtyTexture(_effect_handle_holder->effect_handle());
}

void ShaderPBLStatic::AssignExceptMaterial() const
{
	SendWorldViewProjection(_effect_handle_holder->effect_handle());
	SendWorld(_effect_handle_holder->effect_handle());
	SendLightDirection(_effect_handle_holder->effect_handle());
	SendEyePosition(_effect_handle_holder->effect_handle());
	SendRoughness(_effect_handle_holder->effect_handle());
	SendMetalness(_effect_handle_holder->effect_handle());
	SendFresnel(_effect_handle_holder->effect_handle());
	SendAmbientColor(_effect_handle_holder->effect_handle());
	SendDiffuseCubeMap(_effect_handle_holder->effect_handle());
	SendSpecularCubeMap(_effect_handle_holder->effect_handle());
	SendAlbedoTexture(_effect_handle_holder->effect_handle());
	SendMetalnessMap(_effect_handle_holder->effect_handle());
	SendDirtyTexture(_effect_handle_holder->effect_handle());
}