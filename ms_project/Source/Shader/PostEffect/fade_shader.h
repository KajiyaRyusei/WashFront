//==============================================================================
//
// フェードのシェーダー
//
// Created by Ryusei Kajiya on 20151013
//
//==============================================================================

//*****************************************************************************
// 多重インクルード防止
#pragma once

//*****************************************************************************
// include
#include "Shader/shader_base.h"
#include "Shader/Component/screen_size.h"
#include "Shader/Component/screen_matrix.h"
#include "Shader/Component/ambient_color.h"

class ShaderFade : public ShaderBase, public component::ScreenMatrix, public component::ScreenSize,public component::AmbientColor
{
public:
	ShaderFade() : ShaderBase(s_effect_id) { Initialize(); }
	virtual ~ShaderFade() {}
	virtual void Initialize() override;
	virtual void AssignExceptMaterial() const override;

	static void S_SetEffectId(u32 effect_id) { s_effect_id = effect_id; }

private:
	static u32 s_effect_id;
};