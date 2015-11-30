//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// 
// XInput
// 
// Created by Toshiki Mochizuki on 20151021
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//*****************************************************************************
// �C���N���[�h
#include "input_x.h"
#include "../input_event_buffer.h"

//=============================================================================
// �R���X�g���N�^
InputX::InputX(InputEventBuffer *input_event_buffer) :
	Input(input_event_buffer)
{
	_device_num		= 0;
	_preview_state	= nullptr;
}
//=============================================================================
// ������
void InputX::Initialize()
{	
	XINPUT_STATE	x_state;
	HRESULT			hr;

	for( DWORD i = 0; i < kControllMax; i++ )
	{
		hr = XInputGetState( i , &x_state );
		if( hr == ERROR_SUCCESS )
		{
			// �f�o�C�X���J�E���g
			_device_num++;
		}
	}
	
	if( _device_num != 0 )
	{
		// �f�o�C�X�����������m��
		_preview_state = new XINPUT_STATE[ _device_num ];
		ASSERT( _preview_state != nullptr , "�������m�ێ��s" );
	}
	
}
//=============================================================================
// �I��
void InputX::Finalize()
{
	SafeDelete( _preview_state );
}
//=============================================================================
// �X�V
void InputX::Update()
{
	XINPUT_STATE state;
	bool press_key		= false;
	bool trigger_key	= false;
	bool release_key	= false;
	WORD checkBit		= 1;

	for( DWORD i = 0; i < _device_num; i++ )
	{
		// XInput�̑S���擾
		XInputGetState( i , &state );
		// ��r�p
		checkBit = 1;

		// �{�^��
		for( int j = 0; j < kBitMax; j++ )
		{
			// �v���X
			press_key	=	( state.Gamepad.wButtons & checkBit ) ? true : false;

			// �g���K�[
			trigger_key =	( ( _preview_state[ i ].Gamepad.wButtons ^ state.Gamepad.wButtons ) &
							state.Gamepad.wButtons ) == checkBit ? true : false;
			// �����[�X
			release_key =	( ( _preview_state[ i ].Gamepad.wButtons ^ state.Gamepad.wButtons ) &
							_preview_state[ i ].Gamepad.wButtons ) == checkBit ? true : false;

			// �C�x���g�o�b�t�@�Ƀf�[�^��ۑ����@�̌���
			_input_event_buffer->SetInputEventList(
				static_cast<INPUT_EVENT>( INPUT_EVENT_PAD0_0 + j + ( i * kBitMax ) ),
				press_key, trigger_key, release_key);

			// �`�F�b�N�p�ϐ��V�t�g
			checkBit = checkBit << 1;
		}

		// �X�e�B�b�N���g�p��0������
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

		// ���X�e�B�b�N
		_input_event_buffer->SetInputEventValue(
			static_cast<INPUT_EVENT_VALUE>( INPUT_EVENT_VALUE_PAD0_LSTICK_X + ( i * kOptionNum ) ),
			state.Gamepad.sThumbLX);

		_input_event_buffer->SetInputEventValue(
			static_cast<INPUT_EVENT_VALUE>( INPUT_EVENT_VALUE_PAD0_LSTICK_Y + ( i * kOptionNum ) ),
			state.Gamepad.sThumbLY);

		// �E�X�e�B�b�N
		_input_event_buffer->SetInputEventValue(
			static_cast<INPUT_EVENT_VALUE>( INPUT_EVENT_VALUE_PAD0_RSTICK_X + ( i * kOptionNum ) ),
			state.Gamepad.sThumbRX);

		_input_event_buffer->SetInputEventValue(
			static_cast<INPUT_EVENT_VALUE>( INPUT_EVENT_VALUE_PAD0_RSTICK_Y + ( i * kOptionNum ) ),
			state.Gamepad.sThumbRY);

		// �g���K�[( L2 R2 )
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

		// �O���ۑ�
		_preview_state[ i ] = state;
	}
}