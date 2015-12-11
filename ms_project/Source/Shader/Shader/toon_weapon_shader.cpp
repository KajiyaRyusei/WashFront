//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// 武器用トゥーンシェーダー
//
// Created by Ryusei Kajiya on 20151209
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//*****************************************************************************
// include
#include "toon_weapon_shader.h"
#include "Shader/effect_handle_holder.h"


// static
u32 ShaderToonWeapon::s_effect_id = 0;

void ShaderToonWeapon::Initialize()
{
	InitializeWorldViewProjection(_effect_handle_holder->effect_handle());
	InitializeWorld(_effect_handle_holder->effect_handle());
	InitializeLightDirection(_effect_handle_holder->effect_handle());
	InitializeEyePosition(_effect_handle_holder->effect_handle());
	InitializeDiffuseCubeMap(_effect_handle_holder->effect_handle());
	InitializeSpecularCubeMap(_effect_handle_holder->effect_handle());
	InitializeAlbedoTexture(_effect_handle_holder->effect_handle());
	InitializeToonTexture(_effect_handle_holder->effect_handle());
	InitializeAnimationMatrix(_effect_handle_holder->effect_handle());
}

void ShaderToonWeapon::AssignExceptMaterial() const
{
	SendWorldViewProjection(_effect_handle_holder->effect_handle());
	SendWorld(_effect_handle_holder->effect_handle());
	SendLightDirection(_effect_handle_holder->effect_handle());
	SendEyePosition(_effect_handle_holder->effect_handle());
	SendDiffuseCubeMap(_effect_handle_holder->effect_handle());
	SendSpecularCubeMap(_effect_handle_holder->effect_handle());
	SendAlbedoTexture(_effect_handle_holder->effect_handle());
	SendToonTexture(_effect_handle_holder->effect_handle());
	SendAnimationMatrix(_effect_handle_holder->effect_handle());
}