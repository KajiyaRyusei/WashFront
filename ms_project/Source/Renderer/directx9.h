//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// directx9機構
// 
// Created by Ryusei Kajiya on 20151006
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//*****************************************************************************
// 多重インクルード防止
#pragma once

//*****************************************************************************
// クラス設計
class RendererDevice
{
public:

	RendererDevice(
		const HWND handle_window,
		const u32 size_window_width,
		const u32 size_window_height,
		const bool is_full_screen) :
			_direct3d{ nullptr },
			_direct_device{ nullptr }
	{
		Initialize(handle_window,size_window_width,size_window_height,is_full_screen);
	}

	virtual ~RendererDevice(){ Finalize(); }

	// 初期化
	HRESULT Initialize(
		const HWND handle_window,
		const u32 size_window_width,
		const u32 size_window_height,
		const bool is_full_screen);

	// 終了
	void Finalize();

	// レンダリングターゲットのクリア
	void Clear(const u8 clear_flag, const u8* clear_colors);

	// 描画の開始
	void Begin();

	// 描画の終了
	void End();

	// バックバッファのセット
	void Set();

	// バックバッファとフロントバッファの入れ替え
	void Swap();

	// デバイスの取得
	LPDIRECT3DDEVICE9 GetDevice(){ return _direct_device; }

	// デバイスロスト対策
	void DeviceLostCounterPlan();

private:

	//　レンダーステート初期化
	void InitializeRenderState();

	// サンプラーステート初期化
	void InitializeSamplerState();

	// テクスチャステージステート初期化
	void InitializeTextureStageState();

	// デバイスの能力を調査
	void ExamineDeviceCapacity();

	// デバイス
	LPDIRECT3D9 _direct3d;
	// direct3D
	LPDIRECT3DDEVICE9 _direct_device;
	// デバイスのプレゼンテーションパラメータ
	D3DPRESENT_PARAMETERS _present_parameters;

	// バックバッファと初期デプスステンシル
	LPDIRECT3DSURFACE9 _back_buffer;
	LPDIRECT3DSURFACE9 _depth_stencil_surface;
};
