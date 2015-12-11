//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// ビル用トゥーンシェーダー
//
// Created by Ryusei Kajiya on 20151202
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//*****************************************************************************
// include
#include "toon_building_shader.h"
#include "Shader/effect_handle_holder.h"


// static
u32 ShaderToonBuilding::s_effect_id = 0;

void ShaderToonBuilding::Initialize()
{
	InitializeWorldViewProjection(_effect_handle_holder->effect_handle());
	InitializeWorld(_effect_handle_holder->effect_handle());
	InitializeLightDirection(_effect_handle_holder->effect_handle());
	InitializeEyePosition(_effect_handle_holder->effect_handle());
	InitializeAmbientColor(_effect_handle_holder->effect_handle());
	InitializeDiffuseCubeMap(_effect_handle_holder->effect_handle());
	InitializeSpecularCubeMap(_effect_handle_holder->effect_handle());
	InitializeAlbedoTexture(_effect_handle_holder->effect_handle());
	InitializeMetalnessMap(_effect_handle_holder->effect_handle());
	InitializeDirtyTexture(_effect_handle_holder->effect_handle());
	InitializeNormalTexture(_effect_handle_holder->effect_handle());
	InitializeToonTexture(_effect_handle_holder->effect_handle());
	InitializeTexcoordMove(_effect_handle_holder->effect_handle());
}

void ShaderToonBuilding::AssignExceptMaterial() const
{
	SendWorldViewProjection(_effect_handle_holder->effect_handle());
	SendWorld(_effect_handle_holder->effect_handle());
	SendLightDirection(_effect_handle_holder->effect_handle());
	SendEyePosition(_effect_handle_holder->effect_handle());
	SendAmbientColor(_effect_handle_holder->effect_handle());
	SendDiffuseCubeMap(_effect_handle_holder->effect_handle());
	SendSpecularCubeMap(_effect_handle_holder->effect_handle());
	SendAlbedoTexture(_effect_handle_holder->effect_handle());
	SendMetalnessMap(_effect_handle_holder->effect_handle());
	SendDirtyTexture(_effect_handle_holder->effect_handle());
	SendNormalTexture(_effect_handle_holder->effect_handle());
	SendToonTexture(_effect_handle_holder->effect_handle());
	SendTexcoordMove(_effect_handle_holder->effect_handle());
}