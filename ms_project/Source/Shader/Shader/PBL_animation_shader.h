//==============================================================================
//
// PBLアニメーションシェーダ
//
// Created by Ryusei Kajiya on 20151023
//
//==============================================================================

//*****************************************************************************
// 多重インクルード防止
#pragma once

//*****************************************************************************
// include
#include "Shader/shader_base.h"
#include "Shader/Component/world_view_projection.h"
#include "Shader/Component/world.h"
#include "Shader/Component/light_direction.h"
#include "Shader/Component/animation_matrix.h"
#include "Shader/Component/eye_position.h"
#include "Shader/Component/roughness.h"
#include "Shader/Component/metalness.h"
#include "Shader/Component/fresnel.h"
#include "Shader/Component/ambient_color.h"
#include "Shader/Component/diffuse_cube_texture.h"
#include "Shader/Component/specular_cube_texture.h"
#include "Shader/Component/albedo_texture.h"
#include "Shader/Component/metalness_texture.h"

class ShaderPBLAnimation : public ShaderBase,
	public component::WorldViewProjection,
	public component::World,
	public component::LightDirection,
	public component::AnimationMatrix,
	public component::EyePosition,
	public component::Roughness,
	public component::Metalness,
	public component::Fresnel,
	public component::AmbientColor,
	public component::DiffuseCubeMap,
	public component::SpecularCubeMap,
	public component::AlbedoMap,
	public component::MetalnessMap
{
public:
	ShaderPBLAnimation() : ShaderBase(s_effect_id) { Initialize(); }
	virtual ~ShaderPBLAnimation() {}
	virtual void Initialize() override;
	virtual void AssignExceptMaterial() const override;

	static void S_SetEffectId(u32 effect_id) { s_effect_id = effect_id; }

private:
	static u32 s_effect_id;
};