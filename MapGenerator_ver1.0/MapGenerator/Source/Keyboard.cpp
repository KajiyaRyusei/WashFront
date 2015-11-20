//=============================================================================
//
// キーボード入力処理 [Keyboard.cpp]
// Author : KEITA OHUCHI
//
//=============================================================================
#include "Main.h"
#include "Keyboard.h"


//-----------------------------------------------------------------------------
// マクロ定義
//-----------------------------------------------------------------------------
#define REPEAT_FRAME (20)
#define KEY_MASK (0x0080)


//=============================================================================
// コンストラクタ
//=============================================================================
Keyboard::Keyboard()
{
	// メンバ変数初期化
	memset(pressKey_, 0, sizeof(pressKey_));
	memset(triggerKey_, 0, sizeof(triggerKey_));
	memset(releaseKey_, 0, sizeof(releaseKey_));
	memset(repeatKey_, 0, sizeof(repeatKey_));
	memset(keyCounter_, 0, sizeof(keyCounter_));
}

//=============================================================================
// デストラクタ
//=============================================================================
Keyboard::~Keyboard()
{
}

//=============================================================================
// 入力情報の初期化
//=============================================================================
HRESULT Keyboard::Init(HINSTANCE instance, HWND wnd)
{
	HRESULT hr;

	// 親クラスの初期化処理
	Input::Init(instance, wnd);

	// デバイスオブジェクトを作成
	hr = input_->CreateDevice(GUID_SysKeyboard, &device_, nullptr);
	if (FAILED(hr)) {
		MessageBox(nullptr,
			"デバイスオブジェクトが作成できませんでした",
			"キーボードの初期化", MB_OK);
	}

	// データフォーマットを設定
	hr = device_->SetDataFormat(&c_dfDIKeyboard);
	if (FAILED(hr)) {
		MessageBox(nullptr,
			"データフォーマットが設定できませんでした",
			"キーボードの初期化", MB_OK);
	}

	// 協調モードを設定（フォアグラウンド＆非排他モード）
	hr = device_->SetCooperativeLevel(wnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE));
	if (FAILED(hr)) {
		MessageBox(nullptr,
			"強調モードが設定できませんでした",
			"キーボードの初期化", MB_OK);
	}


	// キーボードへのアクセス権を獲得(入力制御開始)
	device_->Acquire();


	return S_OK;
}

//=============================================================================
// 入力情報の更新処理
//=============================================================================
void Keyboard::Update()
{
	BYTE key_state[KEY_MAX];
	anykeyFlag_ = false;


	if (SUCCEEDED(device_->GetDeviceState(sizeof(key_state), &key_state))) {
		// 各種キー入力状態の作成と保存
		for (int nKey = 0; nKey < KEY_MAX; nKey++) {

			// 押下時間のカウントアップ
			if (key_state[nKey]) {
				keyCounter_[nKey]++;
				anykeyFlag_ = true;
			} else {
				keyCounter_[nKey] = 0;
			}


			triggerKey_[nKey] = ~(pressKey_[nKey] & key_state[nKey]) & key_state[nKey];  // トリガーキー
			releaseKey_[nKey] = ~(pressKey_[nKey] & key_state[nKey]) & pressKey_[nKey];  // リリースキー

			// リピートキー
			if (keyCounter_[nKey] < REPEAT_FRAME) {
				repeatKey_[nKey] = triggerKey_[nKey];
			} else {
				repeatKey_[nKey] = key_state[nKey];
			}

			pressKey_[nKey] = key_state[nKey];  // プレスキー
		}
	} else {
		// キーボードのアクセス権を再取得
		device_->Acquire();
	}
}

//=============================================================================
// キーボードのプレス状態を取得
//=============================================================================
bool Keyboard::GetPressKey(int key)
{
	if (pressKey_[key] & KEY_MASK) {
		return true;
	}


	return false;
}

//=============================================================================
// キーボードのトリガー状態を取得
//=============================================================================
bool Keyboard::GetTriggerKey(int key)
{
	if (triggerKey_[key] & KEY_MASK) {
		return true;
	}


	return false;
}

//=============================================================================
// キーボードのリピート状態を取得
//=============================================================================
bool Keyboard::GetRepeatKey(int key)
{
	if (repeatKey_[key] & KEY_MASK) {
		return true;
	}


	return false;
}

//=============================================================================
// キーボードのリリ－ス状態を取得
//=============================================================================
bool Keyboard::GetReleaseKey(int key)
{
	if (releaseKey_[key] & KEY_MASK) {
		return true;
	}


	return false;
}


// End of file