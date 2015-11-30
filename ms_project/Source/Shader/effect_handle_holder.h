//==============================================================================
//
// エフェクトのハンドルを作成し持っておく
//
// Created by Ryusei Kajiya on 20151008
//
//==============================================================================

//*****************************************************************************
// 多重インクルード防止
#pragma once

//*****************************************************************************
// 前方宣言
class RendererDevice;

//*****************************************************************************
// クラス設計
class EffectHandleHolder
{
public:
	EffectHandleHolder(const char *effect_file_path, RendererDevice* renderer_device);
	virtual ~EffectHandleHolder();

	// エフェクトハンドル取得
	LPD3DXEFFECT effect_handle(void) const { return _effect_handle; }


	// ただやるだけ
	void Begin(u32* pass) const;
	void End() const;
	void BeginPass(u32 pass_number) const;
	void EndPass() const;
	void CommitChanges() const;

	//削除チェック
	virtual bool IsDead(void) const { return is_dead_; }

	//削除可能に設定
	virtual void KillMySelf(void) { is_dead_ = true; }

private:

	LPD3DXEFFECT _effect_handle;
	D3DXHANDLE _handle_technique;
	bool is_dead_;

};