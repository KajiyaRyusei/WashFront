//==============================================================================
//
// �t�F�[�h�̃V�F�[�_�[
//
// Created by Ryusei Kajiya on 20151013
//
//==============================================================================

//*****************************************************************************
// ���d�C���N���[�h�h�~
#pragma once

//*****************************************************************************
// include
#include "Shader/shader_base.h"
#include "Shader/Component/screen_size.h"
#include "Shader/Component/screen_matrix.h"
#include "Shader/Component/ambient_color.h"
#include "Shader/Component/albedo_texture.h"
#include "Shader/Component/texcoord_matrix.h"

class ShaderFade : public ShaderBase, public component::ScreenMatrix, public component::ScreenSize, public component::AmbientColor, public component::AlbedoMap, public component::TexcoordMatrix
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