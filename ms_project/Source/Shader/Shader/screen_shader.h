//==============================================================================
//
// スクリーンに描画する
//
// Created by Ryusei Kajiya on 20151012
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

class ShaderScreen : public ShaderBase, public component::ScreenMatrix, public component::ScreenSize
{
public:
	ShaderScreen() : ShaderBase(s_effect_id) { Initialize(); }
	virtual ~ShaderScreen() {}
	virtual void Initialize() override;
	virtual void AssignExceptMaterial() const override;

	static void S_SetEffectId(u32 effect_id) { s_effect_id = effect_id; }

private:
	static u32 s_effect_id;
};