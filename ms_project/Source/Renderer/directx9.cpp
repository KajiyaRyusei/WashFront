//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// directx9機構
//
// Created by Ryusei Kajiya on 20151006
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//*****************************************************************************
// インクルード
#include "directx9.h"
//#include "reference.h"

//=============================================================================
// 初期化
HRESULT RendererDevice::Initialize(
	const HWND handle_window,
	const u32 size_window_width,
	const u32 size_window_height,
	const bool is_full_screen)
{
	D3DDISPLAYMODE display_mode;

	// Direct3Dオブジェクトの作成
	_direct3d = Direct3DCreate9(D3D_SDK_VERSION);
	if (_direct3d == nullptr)
	{
		return E_FAIL;
	}

	// 現在のディスプレイモードを取得
	if (FAILED(_direct3d->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &display_mode)))
	{
		return E_FAIL;
	}

	// デバイスのプレゼンテーションパラメータの設定
	ZeroMemory(&_present_parameters, sizeof(_present_parameters));	// ワークをゼロクリア
	_present_parameters.BackBufferCount = 1;						// バックバッファの数
	_present_parameters.BackBufferWidth = size_window_width;		// ゲーム画面サイズ(幅)
	_present_parameters.BackBufferHeight = size_window_height;		// ゲーム画面サイズ(高さ)
	_present_parameters.BackBufferFormat = display_mode.Format;		// バックバッファフォーマットはディスプレイモードに合わせて使う
	_present_parameters.SwapEffect = D3DSWAPEFFECT_DISCARD;			// 映像信号に同期してフリップする
	_present_parameters.Windowed = true;							// ウィンドウモード
	_present_parameters.EnableAutoDepthStencil = TRUE;				// デプスバッファ（Ｚバッファ）とステンシルバッファを作成
	_present_parameters.AutoDepthStencilFormat = D3DFMT_D24S8;		// デプスバッファとして24bit・ステンシルに8bit使用
	_present_parameters.MultiSampleType = D3DMULTISAMPLE_4_SAMPLES;	// マルチサンプリング
	DWORD multi_sample_quality = 0;
	_direct3d->CheckDeviceMultiSampleType(D3DADAPTER_DEFAULT,D3DDEVTYPE_HAL,D3DFMT_X8R8G8B8,true,D3DMULTISAMPLE_4_SAMPLES,&multi_sample_quality);
	_present_parameters.MultiSampleQuality = multi_sample_quality-1;

	if( is_full_screen == false)
	{// ウィンドウモード
		_present_parameters.FullScreen_RefreshRateInHz = 0;							// リフレッシュレート
		_present_parameters.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;	// インターバル
	}
	else
	{// フルスクリーンモード
		_present_parameters.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;	// リフレッシュレート
		_present_parameters.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;		// インターバル
	}

	// デバイスオブジェクトの生成
	if (FAILED(_direct3d->CreateDevice(
		D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		handle_window,
		D3DCREATE_HARDWARE_VERTEXPROCESSING,
		//D3DCREATE_HARDWARE_VERTEXPROCESSING | D3DCREATE_MULTITHREADED,// マルチスレッド使用時
		&_present_parameters,
		&_direct_device)))
	{
		// 上記の設定が失敗したら
		// [デバイス作成制御]<描画>をハードウェアで行い、<頂点処理>はCPUで行なう
		if (FAILED(_direct3d->CreateDevice(
			D3DADAPTER_DEFAULT,
			D3DDEVTYPE_HAL,
			handle_window,
			//D3DCREATE_SOFTWARE_VERTEXPROCESSING | D3DCREATE_MULTITHREADED,// マルチスレッド使用時
			D3DCREATE_SOFTWARE_VERTEXPROCESSING,
			&_present_parameters,
			&_direct_device)))
		{
			// 上記の設定が失敗したら
			// [デバイス作成制御]<描画>と<頂点処理>をCPUで行なう
			if (FAILED(_direct3d->CreateDevice(
				D3DADAPTER_DEFAULT,
				D3DDEVTYPE_REF,
				handle_window,
				//D3DCREATE_SOFTWARE_VERTEXPROCESSING | D3DCREATE_MULTITHREADED,// マルチスレッド使用時
				D3DCREATE_SOFTWARE_VERTEXPROCESSING,
				&_present_parameters,
				&_direct_device)))
			{
				// 初期化失敗
				return E_FAIL;
			}
		}
	}

	// レンダーステートパラメータの設定
	InitializeRenderState();
	// サンプラーステートパラメータの設定
	InitializeSamplerState();
	// テクスチャステージステートの設定
	InitializeTextureStageState();
	// デバイス能力の調査
	ExamineDeviceCapacity();


	// バックバッファと初期デプスステンシルを取得
	_direct_device->GetRenderTarget(0, &_back_buffer);
	_direct_device->GetDepthStencilSurface(&_depth_stencil_surface);

	// 登録
	//Reference::GetInstance().SetDevice(_direct_device);

	return S_OK;
}
//=============================================================================
// 終了
void RendererDevice::Finalize()
{
	SafeRelease(_direct3d);
	SafeRelease(_direct_device);
}
//=============================================================================
// レンダリングターゲットのクリア
void RendererDevice::Clear(const u8 clear_flag, const u8* clear_colors)
{
	_direct_device->Clear(0, nullptr, clear_flag, D3DCOLOR_RGBA(clear_colors[0], clear_colors[1], clear_colors[2], clear_colors[3]), 1.f, 0);
}
//=============================================================================
// 描画の開始
void RendererDevice::Begin()
{
	if( FAILED(_direct_device->BeginScene()) )
	{
		OutputDebugStringA("描画開始失敗");
		return;
	}
}
//=============================================================================
// 描画の終了
void RendererDevice::End()
{
	_direct_device->EndScene();
}

//=============================================================================
// バックバッファとフロントバッファの入れ替え
void RendererDevice::Swap()
{
	if( _direct_device->Present(nullptr, nullptr, nullptr, nullptr) == D3DERR_DEVICELOST)
	{
		DeviceLostCounterPlan();
	}
}

//=============================================================================
// バックバッファとZバッファのセット
void RendererDevice::Set()
{
	_direct_device->SetRenderTarget(0, _back_buffer);
	_direct_device->SetDepthStencilSurface(_depth_stencil_surface);
}
//=============================================================================
//　レンダーステート初期化
void RendererDevice::InitializeRenderState()
{
	_direct_device->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);			// ポリゴン面を表示
	//_direct_device->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);		// ワイヤーフレームを表示
	_direct_device->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);				// 裏面をカリング
	_direct_device->SetRenderState(D3DRS_COLORWRITEENABLE, 0xffff);			// 全てのカラー書き込みを行う
	_direct_device->SetRenderState(D3DRS_FOGENABLE, FALSE);					// フォグ不使用
	_direct_device->SetRenderState(D3DRS_LIGHTING, FALSE);					// ライトを不使用
	_direct_device->SetRenderState(D3DRS_STENCILENABLE, FALSE);				// ステンシルに書き込まない
	_direct_device->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);				// αテストを行う
	_direct_device->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);			// αブレンドを行う
	_direct_device->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);			// αブレンドの種類
	_direct_device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);		// αソースカラーの指定
	_direct_device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);	// αデスティネーションカラーの指定
}

//=============================================================================
// サンプラーステート初期化
void RendererDevice::InitializeSamplerState()
{
	_direct_device->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);	// テクスチャアドレッシング方法(U値)を設定
	_direct_device->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);	// テクスチャアドレッシング方法(V値)を設定
	_direct_device->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);	// テクスチャ縮小フィルタモードを設定
	_direct_device->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);	// テクスチャ拡大フィルタモードを設定
}

//=============================================================================
// テクスチャステージステート初期化
void RendererDevice::InitializeTextureStageState()
{
	_direct_device->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);	// アルファブレンディング処理を設定
	_direct_device->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);	// 最初のアルファ引数
	_direct_device->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CURRENT);	// ２番目のアルファ引数
}

//=============================================================================
// デバイスの能力を調査
void RendererDevice::ExamineDeviceCapacity()
{
	D3DCAPS9 capacity;
	_direct_device->GetDeviceCaps(&capacity);
	MyOutputDebugString(L"頂点ブレンドの行列の最大数：%d\n",capacity.MaxVertexBlendMatrices);
	if( capacity.VertexShaderVersion >= D3DVS_VERSION(3,0))
	{
		OutputDebugStringA("頂点シェーダバージョン3.0対応です\n");
	}
	
	if( capacity.PixelShaderVersion >= D3DPS_VERSION(3,0))
	{
		OutputDebugStringA("ピクセルシェーダバージョン3.0対応です\n");
	}
	MyOutputDebugString(L"頂点定数レジスタの最大数：%d\n", capacity.MaxVertexShaderConst);
	MyOutputDebugString(L"ピクセルシェーダ浮動小数点レジスタは：%d\n", 224);
	//MyOutputDebugString(L"マルチサンプリングのクオリティは：%d\n", capacity.);
}

//=============================================================================
// デバイスロスト対策
void RendererDevice::DeviceLostCounterPlan()
{
	// 復帰可能かチェック
	HRESULT handle_result = _direct_device->TestCooperativeLevel();

	OutputDebugStringA("=========================================================\n");
	OutputDebugStringA("デバイスロストしました\n");
	OutputDebugStringA("=========================================================\n");

	ASSERT(handle_result == D3DERR_DEVICELOST,"デバイス復帰無理\n");

	if( handle_result == D3DERR_DEVICENOTRESET )
	{
		_direct_device->Reset(&_present_parameters);
	}
}
