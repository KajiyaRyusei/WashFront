//==============================================================================
//
// 背景専用シェーダー
//
// Created by Ryusei Kajiya on 20151022
//
//==============================================================================

//*****************************************************************************
// 多重インクルード防止
#pragma once

//*****************************************************************************
// include
#include "Shader/shader_base.h"
#include "Shader/Component/world_view_projection.h"
#include "Shader/Component/albedo_cube_texture.h"
#include "Shader/Component/world.h"


class ShaderBackGround : public ShaderBase, public component::AlbedoCubeMap, public component::WorldViewProjection, public component::World
{
public:
	ShaderBackGround() : ShaderBase(s_effect_id) { Initialize(); }
	virtual ~ShaderBackGround() {}
	virtual void Initialize() override;
	virtual void AssignExceptMaterial() const override;

	static void S_SetEffectId(u32 effect_id) { s_effect_id = effect_id; }

private:
	static u32 s_effect_id;
};