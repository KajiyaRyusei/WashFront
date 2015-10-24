//=============================================================================
//
//
// シェーダーベースクラス
//
// Created by Ryusei Kajiya on 20151008
//
// このクラスはシェーダのベースクラスです。
// シェーダクラスを作成する場合には、このクラスを絶対にpublic継承してください。
//
//=============================================================================

//*****************************************************************************
// 多重インクルード防止
#pragma once

//*****************************************************************************
// 前方宣言
class EffectHandleManager;
class EffectHandleHolder;

//*****************************************************************************
// クラス設計
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