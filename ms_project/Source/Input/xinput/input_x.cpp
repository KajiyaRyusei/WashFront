//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// 
// XInput
// 
// Created by Toshiki Mochizuki on 20151021
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//*****************************************************************************
// インクルード
#include "input_x.h"
#include "../input_event_buffer.h"

//=============================================================================
// コンストラクタ
InputX::InputX(InputEventBuffer *input_event_buffer) :
	Input(input_event_buffer)
{
	_device_num		= 0;
	_preview_state	= nullptr;
}
//=============================================================================
// 初期化
void InputX::Initialize()
{	
	XINPUT_STATE	x_state;
	HRESULT			hr;

	for( DWORD i = 0; i < kControllMax; i++ )
	{
		hr = XInputGetState( i , &x_state );
		if( hr == ERROR_SUCCESS )
		{
			// デバイス数カウント
			_device_num++;
		}
	}
	
	if( _device_num != 0 )
	{
		// デバイス数分メモリ確保
		_preview_state = new XINPUT_STATE[ _device_num ];
		ASSERT( _preview_state != nullptr , "メモリ確保失敗" );
	}
	
}
//=============================================================================
// 終了
void InputX::Finalize()
{
	SafeDelete( _preview_state );
}
//=============================================================================
// 更新
void InputX::Update()
{
	XINPUT_STATE state;
	bool press_key		= false;
	bool trigger_key	= false;
	bool release_key	= false;
	WORD checkBit		= 1;

	for( DWORD i = 0; i < _device_num; i++ )
	{
		// XInputの全情報取得
		XInputGetState( i , &state );
		// 比較用
		checkBit = 1;

		// ボタン
		for( int j = 0; j < kBitMax; j++ )
		{
			// プレス
			press_key	=	( state.Gamepad.wButtons & checkBit ) ? true : false;

			// トリガー
			trigger_key =	( ( _preview_state[ i ].Gamepad.wButtons ^ state.Gamepad.wButtons ) &
							state.Gamepad.wButtons ) == checkBit ? true : false;
			// リリース
			release_key =	( ( _preview_state[ i ].Gamepad.wButtons ^ state.Gamepad.wButtons ) &
							_preview_state[ i ].Gamepad.wButtons ) == checkBit ? true : false;

			// イベントバッファにデータを保存方法の検討
			_input_event_buffer->SetInputEventList(
				static_cast<INPUT_EVENT>( INPUT_EVENT_PAD0_0 + j + ( i * kBitMax ) ),
				press_key, trigger_key, release_key);

			// チェック用変数シフト
			checkBit = checkBit << 1;
		}

		// スティック未使用時0初期化
		if( (	state.Gamepad.sThumbLX < XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE	&& 
				state.Gamepad.sThumbLX > -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE ) && 
			(	state.Gamepad.sThumbLY < XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE && 
				state.Gamepad.sThumbLY > -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE ) )
		{	
			state.Gamepad.sThumbLX = 0;
			state.Gamepad.sThumbLY = 0;
		}

		if( (	state.Gamepad.sThumbRX < XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE && 
				state.Gamepad.sThumbRX > -XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE ) && 
			(	state.Gamepad.sThumbRY < XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE && 
				state.Gamepad.sThumbRY > -XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE ) ) 
		{
			state.Gamepad.sThumbRX = 0;
			state.Gamepad.sThumbRY = 0;
		}

		// 左スティック
		_input_event_buffer->SetInputEventValue(
			static_cast<INPUT_EVENT_VALUE>( INPUT_EVENT_VALUE_PAD0_LSTICK_X + ( i * kOptionNum ) ),
			state.Gamepad.sThumbLX);

		_input_event_buffer->SetInputEventValue(
			static_cast<INPUT_EVENT_VALUE>( INPUT_EVENT_VALUE_PAD0_LSTICK_Y + ( i * kOptionNum ) ),
			state.Gamepad.sThumbLY);

		// 右スティック
		_input_event_buffer->SetInputEventValue(
			static_cast<INPUT_EVENT_VALUE>( INPUT_EVENT_VALUE_PAD0_RSTICK_X + ( i * kOptionNum ) ),
			state.Gamepad.sThumbRX);

		_input_event_buffer->SetInputEventValue(
			static_cast<INPUT_EVENT_VALUE>( INPUT_EVENT_VALUE_PAD0_RSTICK_Y + ( i * kOptionNum ) ),
			state.Gamepad.sThumbRY);

		// トリガー( L2 R2 )
		_input_event_buffer->SetInputEventValue(
			static_cast<INPUT_EVENT_VALUE>( INPUT_EVENT_VALUE_PAD0_LTRIGGER + ( i * kOptionNum ) ),
			state.Gamepad.bLeftTrigger);

		_input_event_buffer->SetInputEventValue(
			static_cast<INPUT_EVENT_VALUE>( INPUT_EVENT_VALUE_PAD0_RTRIGGER + ( i * kOptionNum ) ),
			state.Gamepad.bRightTrigger);

		// 
		XINPUT_VIBRATION vib;
		vib.wLeftMotorSpeed		= (WORD)_input_event_buffer->GetInputEventValue( 
									static_cast<INPUT_EVENT_VALUE>( INPUT_EVENT_VALUE_PAD0_LVIBRATION +
 									( i * kOptionNum ) ) );

		vib.wRightMotorSpeed	= (WORD)_input_event_buffer->GetInputEventValue( 
									static_cast<INPUT_EVENT_VALUE>( INPUT_EVENT_VALUE_PAD0_RVIBRATION +
									( i * kOptionNum ) ) );

		XInputSetState( i , &vib );

		// 前情報保存
		_preview_state[ i ] = state;
	}
}