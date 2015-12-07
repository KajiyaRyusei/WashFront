//=============================================================================
//
// レンダラークラス [Renderer.cpp]
// Author : KEITA OHUCHI
//
//=============================================================================

#include "Renderer.h"
#include "Main.h"
#include "Scene.h"
#include "Debug.h"
#include "Manager.h"
#include "Keyboard.h"


//=============================================================================
// コンストラクタ
//=============================================================================
Renderer::Renderer()
{
	// メンバ変数のクリア
	direct3D_ = nullptr;
	device_ = nullptr;

#ifdef _DEBUG
	wireframe_ = false;
#endif
}

//=============================================================================
// デストラクタ
//=============================================================================
Renderer::~Renderer()
{

	// デバイスオブジェクトの開放
	SafeRelease(device_);
	// Direct3Dオブジェクトの開放
	SafeRelease(direct3D_);

}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT Renderer::Init(HINSTANCE instance, HWND wnd, BOOL window)
{
	D3DPRESENT_PARAMETERS d3dpp;
	D3DDISPLAYMODE d3ddm;

	// Direct3Dオブジェクトの作成
	direct3D_ = Direct3DCreate9(D3D_SDK_VERSION);
	if (direct3D_ == nullptr) {
		return E_FAIL;
	}

	// 現在のディスプレイモードを取得
	if (FAILED(direct3D_->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm))) {
		return E_FAIL;
	}

	// デバイスのプレゼンテーションパラメータの設定
	ZeroMemory(&d3dpp, sizeof(d3dpp));  // ワークをゼロクリア
	d3dpp.BackBufferCount = 1;  // バックバッファの数
	d3dpp.BackBufferWidth = SCREEN_WIDTH;  // ゲーム画面サイズ(幅)
	d3dpp.BackBufferHeight = SCREEN_HEIGHT;  // ゲーム画面サイズ(高さ)
	d3dpp.BackBufferFormat = d3ddm.Format;  // バックバッファフォーマットはディスプレイモードに合わせて使う
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;  // 映像信号に同期してフリップする
	d3dpp.Windowed = window;  // ウィンドウモード
	d3dpp.EnableAutoDepthStencil = TRUE;  // デプスバッファ（Ｚバッファ）とステンシルバッファを作成
	d3dpp.AutoDepthStencilFormat = D3DFMT_D24S8;  // デプスバッファとして24bit, ステンシルバッファとして8bitを使う

	if (window) {  // ウィンドウモード
		d3dpp.FullScreen_RefreshRateInHz = 0;  // リフレッシュレート
		d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE; // インターバル
	} else {  // フルスクリーンモード
		d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;  // リフレッシュレート
		d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;  // インターバル
	}

	// デバイスオブジェクトの生成
	// [デバイス作成制御]<描画>と<頂点処理>をハードウェアで行なう
	if (FAILED(direct3D_->CreateDevice(D3DADAPTER_DEFAULT, 
										D3DDEVTYPE_HAL,
										wnd, 
										D3DCREATE_HARDWARE_VERTEXPROCESSING, 
										&d3dpp, &device_))) {
		// 上記の設定が失敗したら
		// [デバイス作成制御]<描画>をハードウェアで行い、<頂点処理>はCPUで行なう
		if (FAILED(direct3D_->CreateDevice(D3DADAPTER_DEFAULT, 
											D3DDEVTYPE_HAL, 
											wnd, 
											D3DCREATE_SOFTWARE_VERTEXPROCESSING, 
											&d3dpp, &device_))) {
		// 上記の設定が失敗したら
		// [デバイス作成制御]<描画>と<頂点処理>をCPUで行なう
		if (FAILED(direct3D_->CreateDevice(D3DADAPTER_DEFAULT, 
											D3DDEVTYPE_REF,
											wnd, 
											D3DCREATE_SOFTWARE_VERTEXPROCESSING, 
											&d3dpp, &device_))) {
				// 初期化失敗
				return E_FAIL;
			}
		}
	}

	// レンダーステートパラメータの設定
	device_->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);  // 裏面をカリング
	device_->SetRenderState(D3DRS_ZENABLE, TRUE);  // Zバッファを使用
	device_->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);  // αブレンドを行う
	device_->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);  // αソースカラーの指定
	device_->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);  // αデスティネーションカラーの指定

	// サンプラーステートパラメータの設定
	device_->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);  // テクスチャアドレッシング方法(U値)を設定
	device_->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);  // テクスチャアドレッシング方法(V値)を設定
	device_->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);  // テクスチャ縮小フィルタモードを設定
	device_->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);  // テクスチャ拡大フィルタモードを設定

	// テクスチャステージステートの設定
	//device_->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);
	//device_->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
	//device_->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_CURRENT);
	device_->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);  // アルファブレンディング処理を設定
	device_->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);  // 最初のアルファ引数
	device_->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CURRENT);  // ２番目のアルファ引数


    // フォグ
	/*
    device_->SetRenderState(D3DRS_FOGENABLE, TRUE);
    device_->SetRenderState(D3DRS_FOGCOLOR, D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.1f));
	device_->SetRenderState(D3DRS_FOGTABLEMODE, D3DFOG_LINEAR);
    float start = 50;
    float end = 200;
    device_->SetRenderState(D3DRS_FOGSTART, *(DWORD *)(&start));
    device_->SetRenderState(D3DRS_FOGEND, *(DWORD *)(&end));
	*/

	return S_OK;
}

//=============================================================================
// 更新処理
//=============================================================================
void Renderer::Update()
{
#ifdef _DEBUG
	Keyboard *key = Manager::GetInstance()->GetKeyboard();
	if (key->GetTriggerKey(DIK_F2)) {
		if (wireframe_) {
			wireframe_ = false;
			device_->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
			//device_->SetRenderState(D3DRS_LIGHTING, TRUE);
		} else {
			wireframe_ = true;
			device_->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
			//device_->SetRenderState(D3DRS_LIGHTING, FALSE);
		}
	}
#endif
}

//=========================================================================
// 描画開始処理
//=========================================================================
bool Renderer::BeginDraw()
{
	// バックバッファ＆Ｚバッファのクリア
	device_->Clear(0, nullptr, (D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL),
					D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f), 1.0f, 0);

	// 描画の開始
	return SUCCEEDED(device_->BeginScene());
}

//=========================================================================
// 描画終了処理
//=========================================================================
void Renderer::EndDraw()
{

	// 描画の終了
	device_->EndScene();

	// バックバッファとフロントバッファの入れ替え
	device_->Present(nullptr, nullptr, nullptr, nullptr);

}


// End of file