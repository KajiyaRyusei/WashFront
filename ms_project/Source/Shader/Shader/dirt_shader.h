//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// 汚れ用シェーダ
//
// Created by Ryusei Kajiya on 20151103
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
#include "Shader/Component/roughness.h"
#include "Shader/Component/metalness.h"
#include "Shader/Component/fresnel.h"
#include "Shader/Component/ambient_color.h"
#include "Shader/Component/normal_texture.h"
#include "Shader/Component/dirt_move_matrix.h"
#include "Shader/Component/texcoord_move.h"
#include "Shader/Component/world_inverse_transpose.h"

class ShaderDirt : public ShaderBase,
	public component::WorldViewProjection,
	public component::World,
	public component::LightDirection,
	public component::EyePosition,
	public component::Roughness,
	public component::Metalness,
	public component::Fresnel,
	public component::AmbientColor,
	public component::NormalMap,
	public component::DirtMoveMatrix,
	public component::TexcoordMove,
	public component::WorldInverseTranspose
{
public:
	ShaderDirt() : ShaderBase(s_effect_id) { Initialize(); }
	virtual ~ShaderDirt() {}
	virtual void Initialize() override;
	virtual void AssignExceptMaterial() const override;

	static void S_SetEffectId(u32 effect_id) { s_effect_id = effect_id; }

private:
	static u32 s_effect_id;
};