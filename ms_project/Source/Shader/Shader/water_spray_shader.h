//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// 水しぶきパーティクル用シェーダ
//
// Created by Ryusei Kajiya on 20151125
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//*****************************************************************************
// 多重インクルード防止
#pragma once

//*****************************************************************************
// include
#include "Shader/shader_base.h"
#include "Shader/Component/albedo_texture.h"
#include "Shader/Component/view_projection.h"


class ShaderWaterSpray : public ShaderBase, public component::AlbedoMap, public component::ViewProjection
{
public:
	ShaderWaterSpray() : ShaderBase(s_effect_id) { Initialize(); }
	virtual ~ShaderWaterSpray() {}
	virtual void Initialize() override;
	virtual void AssignExceptMaterial() const override;

	static void S_SetEffectId(u32 effect_id) { s_effect_id = effect_id; }

private:
	static u32 s_effect_id;
};