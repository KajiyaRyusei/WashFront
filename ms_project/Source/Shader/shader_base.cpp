//=============================================================================
//
//
// シェーダーベースクラス
//
// Created by Ryusei Kajiya on 20151005
//
// このクラスはシェーダのベースクラスです。
// シェーダクラスを作成する場合には、このクラスを絶対にpublic継承してください。
//
//=============================================================================

#include "shader_base.h"
#include "effect_handle_manager.h"
#include "effect_handle_holder.h"


EffectHandleManager* ShaderBase::s_effect_handle_manager_ = nullptr;

//=============================================================================
// コンストラクタ
ShaderBase::ShaderBase(u32 effect_handle_id):
	_effect_handle_holder(s_effect_handle_manager_->GetEffectHandleHolder(effect_handle_id)),
	_shader_id(effect_handle_id)
{

}
//=============================================================================
// 開始
void ShaderBase::Begin(u32* pass) const
{
	_effect_handle_holder->Begin(pass);
}
//=============================================================================
// 終了
void ShaderBase::End() const
{
	_effect_handle_holder->End();
}
//=============================================================================
// 描画パス
void ShaderBase::BeginPass(u32 pass_number) const
{
	_effect_handle_holder->BeginPass(pass_number);
}
//=============================================================================
// パスの終了
void ShaderBase::EndPass() const
{
	_effect_handle_holder->EndPass();
}
//=============================================================================
// 更新
void ShaderBase::CommitChanges() const
{
	_effect_handle_holder->CommitChanges();
}