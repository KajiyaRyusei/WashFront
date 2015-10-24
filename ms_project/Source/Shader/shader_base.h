//=============================================================================
//
//
// �V�F�[�_�[�x�[�X�N���X
//
// Created by Ryusei Kajiya on 20151008
//
// ���̃N���X�̓V�F�[�_�̃x�[�X�N���X�ł��B
// �V�F�[�_�N���X���쐬����ꍇ�ɂ́A���̃N���X���΂�public�p�����Ă��������B
//
//=============================================================================

//*****************************************************************************
// ���d�C���N���[�h�h�~
#pragma once

//*****************************************************************************
// �O���錾
class EffectHandleManager;
class EffectHandleHolder;

//*****************************************************************************
// �N���X�݌v
class ShaderBase
{
public:
	
	explicit ShaderBase(u32 effect_handle_id);
	virtual ~ShaderBase(){}

	virtual void Initialize() = 0;
	virtual void Finalize(){}

	void Begin(u32* pass) const;
	void End() const;
	void BeginPass(u32 pass_number) const;
	void EndPass() const;
	void CommitChanges() const;
	virtual void AssignExceptMaterial() const = 0;

	static void S_SetEffectHandleManager(EffectHandleManager* effect_handle_manager)
	{
		s_effect_handle_manager_ = effect_handle_manager;
	}

	u32 shader_id() { return _shader_id; }


protected:
	const EffectHandleHolder* _effect_handle_holder;
	static EffectHandleManager* s_effect_handle_manager_;

private:
	u32 _shader_id;
};