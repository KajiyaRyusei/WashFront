//==============================================================================
//
// エフェクトホールダーを管理する
//
// Created by Ryusei Kajiya on 20151009
//
//==============================================================================

//******************************************************************************
// include
#include "effect_handle_manager.h"
#include "effect_handle_holder.h"
#include "shader_base.h"
#include "Renderer/directx9.h"

//******************************************************************************
// 一個づつシェーダincludeしてね
#include "Shader/Shader/lambert.h"
#include "Shader/Shader/screen_shader.h"
#include "Shader/PostEffect/fade_shader.h"
#include "Shader/Shader/animation_shader.h"
#include "Shader/Shader/back_ground_shader.h"
#include "Shader/Shader/PBL_animation_shader.h"
#include "Shader/Shader/PBL_static_shader.h"
#include "Shader/Shader/aim_shader.h"
#include "Shader/Shader/screen_2d_shader.h"

//==============================================================================
// コンストラクタ
EffectHandleManager::EffectHandleManager(RendererDevice* renderer_device)
{
	// シェーダベースに自分を登録
	ShaderBase::S_SetEffectHandleManager(this);

	// 0番は無いこととする
	_effect_handle_holder_list.push_back(nullptr);

	//シェーダを全て作っていく
	EntryList<ShaderLambert>("Data/Shader/lambert_lighting.cso",renderer_device);
	EntryList<ShaderScreen>("Data/Shader/screen_shader.cso", renderer_device);
	EntryList<ShaderFade>("Data/Shader/fade.cso", renderer_device);
	EntryList<ShaderAnimation>("Data/Shader/animation.cso", renderer_device);
	EntryList<ShaderBackGround>("Data/Shader/back_ground.cso", renderer_device);
	EntryList<ShaderPBLAnimation>("Data/Shader/PBL_animation.cso", renderer_device);
	EntryList<ShaderPBLStatic>("Data/Shader/PBL_static.cso", renderer_device);
	EntryList<ShaderAim>("Data/Shader/aim.cso", renderer_device);
	EntryList<Shader2D>("Data/Shader/shader_2d.cso", renderer_device);


}

//==============================================================================
// デストラクタ
EffectHandleManager::~EffectHandleManager()
{
	for( EffectHandleHolder* handle : _effect_handle_holder_list )
	{
		SafeDelete(handle);
	}
	_effect_handle_holder_list.clear();
}

//==============================================================================
// エフェクトハンドルホルダを取得する
EffectHandleHolder* EffectHandleManager::GetEffectHandleHolder(const u32 effect_handle_id) const
{
	return _effect_handle_holder_list[effect_handle_id];
}

//==============================================================================
// エフェクトハンドルホルダを設定
template<class _T>
void EffectHandleManager::EntryList(const char* filename, RendererDevice* renderer_device)
{
	EffectHandleHolder* holder;
	holder = new EffectHandleHolder(filename, renderer_device);
	_T::S_SetEffectId(_effect_handle_holder_list.size());
	_effect_handle_holder_list.push_back(holder);
}
