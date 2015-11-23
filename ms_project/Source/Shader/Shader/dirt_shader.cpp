//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// 汚れ用シェーダ
//
// Created by Ryusei Kajiya on 20151103
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//*****************************************************************************
// include
#include "dirt_shader.h"
#include "Shader/effect_handle_holder.h"


// static
u32 ShaderDirt::s_effect_id = 0;

void ShaderDirt::Initialize()
{
	InitializeWorldViewProjection(_effect_handle_holder->effect_handle());
	InitializeWorld(_effect_handle_holder->effect_handle());
	InitializeLightDirection(_effect_handle_holder->effect_handle());
	InitializeEyePosition(_effect_handle_holder->effect_handle());
	InitializeRoughness(_effect_handle_holder->effect_handle());
	InitializeMetalness(_effect_handle_holder->effect_handle());
	InitializeFresnel(_effect_handle_holder->effect_handle());
	InitializeAmbientColor(_effect_handle_holder->effect_handle());
	InitializeNormalTexture(_effect_handle_holder->effect_handle());
	InitializeDirtMoveMatrix(_effect_handle_holder->effect_handle());
	InitializeTexcoordMove(_effect_handle_holder->effect_handle());
	InitializeWorldInverseTranspose(_effect_handle_holder->effect_handle());
}

void ShaderDirt::AssignExceptMaterial() const
{
	SendWorldViewProjection(_effect_handle_holder->effect_handle());
	SendWorld(_effect_handle_holder->effect_handle());
	SendLightDirection(_effect_handle_holder->effect_handle());
	SendEyePosition(_effect_handle_holder->effect_handle());
	SendRoughness(_effect_handle_holder->effect_handle());
	SendMetalness(_effect_handle_holder->effect_handle());
	SendFresnel(_effect_handle_holder->effect_handle());
	SendAmbientColor(_effect_handle_holder->effect_handle());
	SendNormalTexture(_effect_handle_holder->effect_handle());
	SendDirtMoveMatrix(_effect_handle_holder->effect_handle());
	SendWorldInverseTranspose(_effect_handle_holder->effect_handle());
	SendTexcoordMove(_effect_handle_holder->effect_handle());
}