//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// 静的雲用トゥーンシェーダー
//
// Created by Ryusei Kajiya on 20151215
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//*****************************************************************************
// 多重インクルード防止
#pragma once

//*****************************************************************************
// include
#include "Shader/shader_base.h"
#include "Shader/Component/view_projection.h"
#include "Shader/Component/light_direction.h"
#include "Shader/Component/diffuse_cube_texture.h"
#include "Shader/Component/toon_texture.h"
#include "Shader/Component/view.h"

class ShaderStaticToonCloud : public ShaderBase,
	public component::LightDirection,
	public component::DiffuseCubeMap,
	public component::ViewProjection,
	public component::ToonTexture,
	public component::View
{
public:
	ShaderStaticToonCloud() : ShaderBase(s_effect_id) { Initialize(); }
	virtual ~ShaderStaticToonCloud() {}
	virtual void Initialize() override;
	virtual void AssignExceptMaterial() const override;

	static void S_SetEffectId(u32 effect_id) { s_effect_id = effect_id; }

private:
	static u32 s_effect_id;
};