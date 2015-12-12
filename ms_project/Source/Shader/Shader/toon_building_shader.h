//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// ビル用トゥーンシェーダー
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
#include "Shader/Component/ambient_color.h"
#include "Shader/Component/diffuse_cube_texture.h"
#include "Shader/Component/albedo_texture.h"
#include "Shader/Component/dirty_texture.h"
#include "Shader/Component/normal_texture.h"
#include "Shader/Component/toon_texture.h"
#include "Shader/Component/texcoord_move.h"
#include "Shader/Component/view.h"

class ShaderToonBuilding : public ShaderBase,
	public component::WorldViewProjection,
	public component::World,
	public component::LightDirection,
	public component::EyePosition,
	public component::AmbientColor,
	public component::DiffuseCubeMap,
	public component::AlbedoMap,
	public component::DirtyMap,
	public component::NormalMap,
	public component::ToonTexture,
	public component::TexcoordMove,
	public component::View
{
public:
	ShaderToonBuilding() : ShaderBase(s_effect_id) { Initialize(); }
	virtual ~ShaderToonBuilding() {}
	virtual void Initialize() override;
	virtual void AssignExceptMaterial() const override;

	static void S_SetEffectId(u32 effect_id) { s_effect_id = effect_id; }

private:
	static u32 s_effect_id;
};