//==============================================================================
//
// ƒXƒNƒŠ[ƒ“‚É•`‰æ‚·‚é
//
// Created by Ryusei Kajiya on 20151012
//
//==============================================================================

//*****************************************************************************
// include
#include "screen_shader.h"
#include "Shader/effect_handle_holder.h"


// static
u32 ShaderScreen::s_effect_id = 0;

void ShaderScreen::Initialize()
{
	InitializeScreenMatrix(_effect_handle_holder->effect_handle());
	InitializeScreenSize(_effect_handle_holder->effect_handle());
}

void ShaderScreen::AssignExceptMaterial() const
{
	SendScreenMatrix(_effect_handle_holder->effect_handle());
	SendScreenSize(_effect_handle_holder->effect_handle());
}