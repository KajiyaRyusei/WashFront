//=============================================================================
//
//
// �V�F�[�_�[�x�[�X�N���X
//
// Created by Ryusei Kajiya on 20151005
//
// ���̃N���X�̓V�F�[�_�̃x�[�X�N���X�ł��B
// �V�F�[�_�N���X���쐬����ꍇ�ɂ́A���̃N���X���΂�public�p�����Ă��������B
//
//=============================================================================

#include "shader_base.h"
#include "effect_handle_manager.h"
#include "effect_handle_holder.h"


EffectHandleManager* ShaderBase::s_effect_handle_manager_ = nullptr;

//=============================================================================
// �R���X�g���N�^
ShaderBase::ShaderBase(u32 effect_handle_id):
	_effect_handle_holder(s_effect_handle_manager_->GetEffectHandleHolder(effect_handle_id)),
	_shader_id(effect_handle_id)
{

}
//=============================================================================
// �J�n
void ShaderBase::Begin(u32* pass) const
{
	_effect_handle_holder->Begin(pass);
}
//=============================================================================
// �I��
void ShaderBase::End() const
{
	_effect_handle_holder->End();
}
//=============================================================================
// �`��p�X
void ShaderBase::BeginPass(u32 pass_number) const
{
	_effect_handle_holder->BeginPass(pass_number);
}
//=============================================================================
// �p�X�̏I��
void ShaderBase::EndPass() const
{
	_effect_handle_holder->EndPass();
}
//=============================================================================
// �X�V
void ShaderBase::CommitChanges() const
{
	_effect_handle_holder->CommitChanges();
}