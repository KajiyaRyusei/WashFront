//==============================================================================
//
// エフェクトホールダーを管理する
//
// Created by Ryusei Kajiya on 20151009
//
//==============================================================================

//*****************************************************************************
// 多重インクルード防止
#pragma once

//*****************************************************************************
// 前方宣言
class EffectHandleHolder;
class RendererDevice;
//*****************************************************************************
// クラス設計
class EffectHandleManager
{
public:
	explicit EffectHandleManager(RendererDevice* renderer_device);
	virtual ~EffectHandleManager();

	EffectHandleHolder* GetEffectHandleHolder(u32 effect_handle_id) const;

 private:
	std::vector<EffectHandleHolder*> _effect_handle_holder_list;

	template<class _T>
	void EntryList(const char* filename, RendererDevice* renderer_device);
};