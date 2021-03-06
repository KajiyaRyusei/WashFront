//==============================================================================
//
// Aim用shader
//
// Created by Ryusei Kajiya on 20151027
//
//==============================================================================

//*****************************************************************************
// 多重インクルード防止
#pragma once

//*****************************************************************************
// include
#include "Shader/shader_base.h"
#include "Shader/Component/albedo_texture.h"
#include "Shader/Component/world_view_projection.h"
#include "Shader/Component/ambient_color.h"


class ShaderAim : public ShaderBase, public component::AlbedoMap, public component::WorldViewProjection, public component::AmbientColor
{
public:
	ShaderAim() : ShaderBase(s_effect_id) { Initialize(); }
	virtual ~ShaderAim() {}
	virtual void Initialize() override;
	virtual void AssignExceptMaterial() const override;

	static void S_SetEffectId(u32 effect_id) { s_effect_id = effect_id; }

private:
	static u32 s_effect_id;
};