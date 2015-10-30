//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// 
// 入力の管理
// 
// Created by Ryusei Kajiya on 20151006
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//*****************************************************************************
// インクルード
#include "input_manager.h"
#include "input_event_buffer.h"
#include "keyboard/input_keyboard.h"
#include "xinput\input_x.h"

//*****************************************************************************
// 定数
namespace
{
	static const char kPressBit		= 0x01;
	static const char kTriggerBit	= 0x02;
	static const char kReleaseBit	= 0x04;
	static const char kRepeateBit	= 0x08;
};

//=============================================================================
// 初期化
void InputManager::Initialize(
	HWND handle_window,
	HINSTANCE handle_instance)
{
	// イベントバッファ生成
	_input_event_buffer = new InputEventBuffer();
	ASSERT(_input_event_buffer != nullptr,"イベントバッファ初期化失敗");
	_input_event_buffer->Initialize(handle_window, handle_instance);

	// キーボード生成
	_input_device_list.push_back(new InputKeyboard(_input_event_buffer));

	// XInput
	_input_device_list.push_back( new InputX( _input_event_buffer ) );

	for (auto it = _input_device_list.begin(); it < _input_device_list.end(); ++it)
	{// デバイスの初期化
		(*it)->Initialize();
	}
	// リファレンス登録
}

//=============================================================================
// 終了
void InputManager::Finalize()
{

	for (auto it = _input_device_list.begin(); it < _input_device_list.end(); ++it)
	{// デバイスの終了
		(*it)->Finalize();
		SafeDelete((*it));
	}
	_input_device_list.clear();

	if (_input_event_buffer != nullptr)
	{// イベントバッファの終了
		_input_event_buffer->Finalize();
		SafeDelete(_input_event_buffer);
	}
}

//=============================================================================
// 更新
void InputManager::Update()
{
	for (auto it = _input_device_list.begin(); it < _input_device_list.end(); ++it)
	{// デバイスの更新
		(*it)->Update();
	}
}

//=============================================================================
// プレス
bool InputManager::CheckPress(INPUT_EVENT input_event)
{
	return _input_event_buffer->GetInputEventList(input_event) & kPressBit ? true : false;
}
//=============================================================================
// トリガー
bool InputManager::CheckTrigger(INPUT_EVENT input_event)
{
	return _input_event_buffer->GetInputEventList(input_event) & kTriggerBit ? true : false;
}
//=============================================================================
// リリース
bool InputManager::CheckRelease(INPUT_EVENT input_event)
{
	return _input_event_buffer->GetInputEventList(input_event) & kReleaseBit ? true : false;
}
//=============================================================================
// リピート
bool InputManager::CheckRepeat(INPUT_EVENT input_event)
{
	return _input_event_buffer->GetInputEventList(input_event) & kRepeateBit ? true : false;
}
//=============================================================================
// データセット
void InputManager::SetEventValue(INPUT_EVENT_VALUE input_event_value ,s32 Value)
{
	_input_event_buffer->SetInputEventValue( input_event_value , Value );
}
//=============================================================================
// データ取得
s32 InputManager::GetEventValue(INPUT_EVENT_VALUE input_event_value)
{
	return _input_event_buffer->GetInputEventValue( input_event_value );
}