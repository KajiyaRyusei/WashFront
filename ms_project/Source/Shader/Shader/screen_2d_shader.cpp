//==============================================================================
//
// ƒXƒNƒŠ[ƒ“‚É•`‰æ‚·‚é
//
// Created by Ryusei Kajiya on 20151012
//
//==============================================================================

//*****************************************************************************
// include
#include "screen_2d_shader.h"
#include "Shader/effect_handle_holder.h"


// static
u32 Shader2D::s_effect_id = 0;

void Shader2D::Initialize()
{
	InitializeScreenMatrix(_effect_handle_holder->effect_handle());
	InitializeScreenSize(_effect_handle_holder->effect_handle());
	InitializeScreenTextureUv(_effect_handle_holder->effect_handle());
	InitializeScreenTextureOffset(_effect_handle_holder->effect_handle());
	InitializeScreenTextureAlpha(_effect_handle_holder->effect_handle());
	InitializeAlbedoTexture(_effect_handle_holder->effect_handle());
	InitializeAmbientColor(_effect_handle_holder->effect_handle());
}

void Shader2D::AssignExceptMaterial() const
{
	SendScreenMatrix(_effect_handle_holder->effect_handle());
	SendScreenSize(_effect_handle_holder->effect_handle());
	SendScreenTextureUv(_effect_handle_holder->effect_handle());
	SendScreenTextureOffset(_effect_handle_holder->effect_handle());
	SendScreenTextureAlpha(_effect_handle_holder->effect_handle());
	SendAlbedoTexture(_effect_handle_holder->effect_handle());
	SendAmbientColor(_effect_handle_holder->effect_handle());
}