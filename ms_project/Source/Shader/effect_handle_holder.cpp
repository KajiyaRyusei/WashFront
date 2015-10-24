//==============================================================================
//
// エフェクトのハンドルを作成し持っておく
//
// Created by Ryusei Kajiya on 20151008
//
//==============================================================================

//******************************************************************************
// include
#include "effect_handle_holder.h"
#include "Renderer/directx9.h"

//==============================================================================
// コンストラクタ
EffectHandleHolder::EffectHandleHolder(const char *effect_file_name, RendererDevice* renderer_device) :
	is_dead_(false)
{
	ID3DXBuffer* error = NULL;

	LPDIRECT3DDEVICE9 device = renderer_device->GetDevice();

	HRESULT handle_result = S_OK;

	handle_result = D3DXCreateEffectFromFileA(
		device,
		effect_file_name,
		nullptr,
		nullptr,
		D3DXSHADER_DEBUG,
		nullptr,
		&_effect_handle,
		&error);

	if( FAILED(handle_result) )
	{
		// デバッグ用の文字出力
		OutputDebugStringA((char*)error->GetBufferPointer());
		// 解放
		error->Release();
		return;
	}

	ASSERT(SUCCEEDED(handle_result), "シェーダつくれませんでした");

	SafeRelease(error);

	// ハンドル取得
	_handle_technique = _effect_handle->GetTechniqueByName("Techniques");

	// とりあえずテクニック設定
	_effect_handle->SetTechnique(_handle_technique);
}

//==============================================================================
// デストラクタ
EffectHandleHolder::~EffectHandleHolder()
{
	SafeRelease(_effect_handle);
}

//==============================================================================
// シェーダ開始
void EffectHandleHolder::Begin(u32* pass) const
{
	_effect_handle->Begin(reinterpret_cast<u32*>(pass), 0);
}

//==============================================================================
// シェーダ終了
void EffectHandleHolder::End() const
{
	_effect_handle->End();
}

//==============================================================================
// シェーダパス開始
void EffectHandleHolder::BeginPass(u32 pass_number) const
{
	_effect_handle->BeginPass(pass_number);
}

//==============================================================================
// シェーダパス終了
void EffectHandleHolder::EndPass() const
{
	_effect_handle->EndPass();
}

//==============================================================================
// 値をシェーダにコミットする
void EffectHandleHolder::CommitChanges() const
{
	_effect_handle->CommitChanges();
}