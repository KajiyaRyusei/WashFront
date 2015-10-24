//==============================================================================
//
// アニメーションシェーダ
//
// Created by Ryusei Kajiya on 20151014
//
//==============================================================================

//*****************************************************************************
// 多重インクルード防止
#pragma once

//*****************************************************************************
// include
#include "Shader/shader_base.h"
#include "Shader/Component/light_direction.h"
#include "Shader/Component/world_view_projection.h"
#include "Shader/Component/animation_matrix.h"


class ShaderAnimation : public ShaderBase, public component::LightDirection, public component::WorldViewProjection,public component::AnimationMatrix
{
public:
	ShaderAnimation() : ShaderBase(s_effect_id) { Initialize(); }
	virtual ~ShaderAnimation() {}
	virtual void Initialize() override;
	virtual void AssignExceptMaterial() const override;

	static void S_SetEffectId(u32 effect_id) { s_effect_id = effect_id; }

private:
	static u32 s_effect_id;
};