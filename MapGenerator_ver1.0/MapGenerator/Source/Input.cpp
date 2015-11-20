//=============================================================================
//
// 入力処理 [Input.cpp]
// Author : KEITA OHUCHI
//
//=============================================================================

#include "Main.h"
#include "Input.h"


//=============================================================================
// コンストラクタ
//=============================================================================
Input::Input()
{
	input_ = nullptr;
	device_ = nullptr;
}

//=============================================================================
// デストラクタ
//=============================================================================
Input::~Input()
{

	// DirectInputオブジェクトの解放
	SafeRelease(input_);
	// デバイスの解放
	SafeRelease(device_);

}

//=============================================================================
// 入力情報の初期化
//=============================================================================
HRESULT Input::Init(HINSTANCE instance, HWND wnd)
{
	HRESULT hr;

	// DirectInputオブジェクトの作成
	if (input_ == nullptr) {
		hr = DirectInput8Create(instance,
								DIRECTINPUT_VERSION,
								IID_IDirectInput8,
								(void **)&input_, nullptr);
		if (FAILED(hr)) {
			MessageBox(nullptr, "DirectInputオブジェクトが作成できませんでした",
					   "インプットの初期化", MB_OK);
			return hr;
		}
	}


	return S_OK;
}


// End of file