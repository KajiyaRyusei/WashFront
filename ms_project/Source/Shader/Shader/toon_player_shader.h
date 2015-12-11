//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// プレイヤー用トゥーンシェーダー
//
// Created by Ryusei Kajiya on 20151202
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//*****************************************************************************
// 多重インクルード防止
#pragma once

//*****************************************************************************
// include
#include "Shader/shader_base.h"
#include "Shader/Component/world_view_projection.h"
#include "Shader/Component/world.h"
#include "Shader/Component/light_direction.h"
#include "Shader/Component/eye_position.h"
#include "Shader/Component/diffuse_cube_texture.h"
#include "Shader/Component/specular_cube_texture.h"
#include "Shader/Component/albedo_texture.h"
#include "Shader/Component/toon_texture.h"
#include "Shader/Component/animation_matrix.h"

class ShaderToonPlayer : public ShaderBase,
	public component::WorldViewProjection,
	public component::World,
	public component::LightDirection,
	public component::EyePosition,
	public component::DiffuseCubeMap,
	public component::SpecularCubeMap,
	public component::AlbedoMap,
	public component::AnimationMatrix,
	public component::ToonTexture
{
public:
	ShaderToonPlayer() : ShaderBase(s_effect_id) { Initialize(); }
	virtual ~ShaderToonPlayer() {}
	virtual void Initialize() override;
	virtual void AssignExceptMaterial() const override;

	static void S_SetEffectId(u32 effect_id) { s_effect_id = effect_id; }

private:
	static u32 s_effect_id;
};