//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// 
// インプットイベント
// 
// Created by Ryusei Kajiya on 20151006
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//*****************************************************************************
// インクルード
#include "input_event_buffer.h"

//=============================================================================
// コンストラクタ
InputEventBuffer::InputEventBuffer():
	_direct_input(nullptr),
	_handle_window(nullptr),
	_handle_instance(nullptr)
{
	ZeroMemory(_input_event_list, sizeof(_input_event_list));
	ZeroMemory(_input_event_value_list, sizeof(_input_event_value_list));
}

//=============================================================================
// 初期化
void InputEventBuffer::Initialize(
	HWND window_handle,
	HINSTANCE instance_handle)
{
	_handle_window = window_handle;
	_handle_instance = instance_handle;

	HRESULT result_handle = DirectInput8Create(
		instance_handle,
		DIRECTINPUT_VERSION,
		IID_IDirectInput8,
		(void **)&_direct_input,
		nullptr);

	ASSERT(result_handle == S_OK, "インプットデバイスの作成失敗");
}

//=============================================================================
// 終了
void InputEventBuffer::Finalize()
{
	SafeRelease(_direct_input);
}