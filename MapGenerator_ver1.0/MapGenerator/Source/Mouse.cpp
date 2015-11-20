//=============================================================================
//
// マウスの入力処理 [Mouse.cpp]
// Author : KEITA OHUCHI
//
//=============================================================================

#include "Main.h"
#include "Mouse.h"


//=============================================================================
// コンストラクタ
//=============================================================================
Mouse::Mouse()
{
	memset(&pressMouse_, 0, sizeof(DIMOUSESTATE));
	memset(&triggerMouse_, 0, sizeof(DIMOUSESTATE));
}

//=============================================================================
// デストラクタ
//=============================================================================
Mouse::~Mouse()
{
}

//=============================================================================
// 入力情報の初期化
//=============================================================================
HRESULT Mouse::Init(HINSTANCE instance, HWND wnd)
{
	HRESULT hr;

	// 親クラスの初期化処理
	Input::Init(instance, wnd);

	if (!input_) {
		MessageBox(nullptr,
			"DirectInputオブジェクトが作成できませんでした",
			"マウスの初期化", MB_OK);
		
		return S_FALSE;
	}

	// デバイスオブジェクトを作成
	hr = input_->CreateDevice(GUID_SysMouse, &device_, nullptr);
	if (FAILED(hr)) {
		MessageBox(nullptr,
			"デバイスオブジェクトが作成できませんでした",
			"マウスの初期化", MB_OK);
	}

	// データフォーマットを設定
	hr = device_->SetDataFormat(&c_dfDIMouse);
	if (FAILED(hr)) {
		MessageBox(nullptr,
			"データフォーマットが設定できませんでした",
			"マウスの初期化", MB_OK);
	}

	// 協調モードを設定（フォアグラウンド＆非排他モード）
	hr = device_->SetCooperativeLevel(wnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE));
	if (FAILED(hr)) {
		MessageBox(nullptr,
			"強調モードが設定できませんでした",
			"マウスの初期化", MB_OK);
	}


/*
	// マウスハンドルの初期化
	mouse__device_handle = CreateEvent(nullptr, FALSE, FALSE, nullptr);
	if (mouse__device_handle == nullptr) {
		return FALSE;
	}

	// マウスデバイスとの関連付け
	hr = mouse__device->SetEventNotification(mouse__device_handle);
	if (FAILED(hr)) {
		return FALSE;
	}

	// プロパティの初期化
	DIPROPDWORD dipdw;
	// the header
	dipdw.diph.dwSize	   = sizeof(DIPROPDWORD);
	dipdw.diph.dwHeaderSize = sizeof(DIPROPHEADER);
	dipdw.diph.dwObj		= 0;
	dipdw.diph.dwHow		= DIPH_DEVICE;
	// the data
	dipdw.dwData			= 16;

	// プロパティの設定
	hr = mouse__device->SetProperty(DIPROP_BUFFERSIZE, &dipdw.diph);
	if (FAILED(hr)) {
		return FALSE;
	}
*/


	// マウスへのアクセス権を獲得(入力制御開始)
	device_->Acquire();


	return S_OK;
}

//=============================================================================
// 入力情報の更新処理
//=============================================================================
void Mouse::Update()
{
	DIMOUSESTATE mouse_state;
	if (SUCCEEDED(device_->GetDeviceState(sizeof(mouse_state), &mouse_state))) {
		for (int count = 0; count < BUTTON_MAX; ++count) {
			triggerMouse_.rgbButtons[count] =
				~(pressMouse_.rgbButtons[count] & mouse_state.rgbButtons[count]) & mouse_state.rgbButtons[count];  // トリガー生成
		}
		pressMouse_ = mouse_state;  // 情報更新
	} else {
		// キーボードのアクセス権を再取得
		device_->Acquire();
	}
}

//=============================================================================
// マウスの状態の取得
//=============================================================================
DIMOUSESTATE Mouse::GetPressMouse()
{
	return pressMouse_;
}

//=============================================================================
// トリガー情報の取得
//=============================================================================
DIMOUSESTATE Mouse::GetTriggerMouse()
{
	return triggerMouse_;
}

// End of file