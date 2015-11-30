//==============================================================================
//
// �G�t�F�N�g�z�[���_�[���Ǘ�����
//
// Created by Ryusei Kajiya on 20151009
//
//==============================================================================

//*****************************************************************************
// ���d�C���N���[�h�h�~
#pragma once

//*****************************************************************************
// �O���錾
class EffectHandleHolder;
class RendererDevice;
//*****************************************************************************
// �N���X�݌v
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