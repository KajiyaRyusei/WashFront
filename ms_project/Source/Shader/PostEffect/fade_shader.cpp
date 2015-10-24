//==============================================================================
//
// フェードのシェーダー
//
// Created by Ryusei Kajiya on 20151013
//
//==============================================================================

//*****************************************************************************
// include
#include "fade_shader.h"
#include "Shader/effect_handle_holder.h"


// static
u32 ShaderFade::s_effect_id = 0;

void ShaderFade::Initialize()
{
	InitializeScreenMatrix(_effect_handle_holder->effect_handle());
	InitializeScreenSize(_effect_handle_holder->effect_handle());
	InitializeAmbientColor(_effect_handle_holder->effect_handle());
}

void ShaderFade::AssignExceptMaterial() const
{
	SendScreenMatrix(_effect_handle_holder->effect_handle());
	SendScreenSize(_effect_handle_holder->effect_handle());
	SendAmbientColor(_effect_handle_holder->effect_handle());
}