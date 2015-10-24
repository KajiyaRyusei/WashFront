//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// 
// キーボード
// 
// Created by Ryusei Kajiya on 20151006
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//*****************************************************************************
// インクルード
#include "input_keyboard.h"
#include "../input_event_buffer.h"

//=============================================================================
// コンストラクタ
InputKeyboard::InputKeyboard(InputEventBuffer *input_event_buffer) :
	Input(input_event_buffer)
{
	ZeroMemory(_preview_key, sizeof(_preview_key));
}
//=============================================================================
// 初期化
void InputKeyboard::Initialize()
{
	HRESULT handle_result;
	LPDIRECTINPUT8 direct_input = _input_event_buffer->GetDirectInput();

	// デバイスオブジェクトの作成
	handle_result = direct_input->CreateDevice(
		GUID_SysKeyboard,
		&_direct_input_device,
		nullptr);
	ASSERT(handle_result == S_OK, "デバイスオブジェクトの作成に失敗");

	// データフォーマットを設定
	handle_result = _direct_input_device->SetDataFormat(&c_dfDIKeyboard);
	ASSERT(handle_result == S_OK, "データフォーマットの作成に失敗");

	// 協調モードを設定
	handle_result = _direct_input_device->SetCooperativeLevel(
		_input_event_buffer->GetWindowHandle(),
		(DISCL_FOREGROUND | DISCL_NONEXCLUSIVE));
	ASSERT(handle_result == S_OK, "協調モードに失敗");

	// アクセス権を取得
	_direct_input_device->Acquire();


}
//=============================================================================
// 終了
void InputKeyboard::Finalize()
{
	Input::Finalize();
}
//=============================================================================
// 更新
void InputKeyboard::Update()
{
	u8 key_state[kKeyMax] = {0};
	bool press_key = false;
	bool trigger_key = false;
	bool release_key = false;

	HRESULT result_handle = _direct_input_device->GetDeviceState(
		sizeof(key_state),
		key_state);
	if (FAILED(result_handle))
	{// ステート処理がおかしかったら
		ZeroMemory(key_state, sizeof(key_state));
		_direct_input_device->Acquire();
	}

	for (s32 i = 0; i < kKeyMax; ++i)
	{
		// プレスキーの算出
		press_key = (key_state[i] & 0x80) ? true : false;

		// トリガーキーの算出
		trigger_key = (press_key ^ _preview_key[i]) & press_key;

		// リリースキーの算出
		release_key = (press_key ^ _preview_key[i]) & !press_key;

		// プレビューキーの保存
		_preview_key[i] = press_key;

		// イベントバッファにデータを保存方法の検討
		_input_event_buffer->SetInputEventList(
			static_cast<INPUT_EVENT>(i),
			press_key, trigger_key, release_key);
	}
}