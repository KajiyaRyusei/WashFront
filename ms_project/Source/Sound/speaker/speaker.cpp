//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// 
// �X�s�[�J�[
// 
// Created by Ryusei Kajiya on 20151021
// 
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//*****************************************************************************
// include
#include "sound/speaker/speaker.h"
#include "sound/xact/xact_manager.h"
#include "System/application.h"

//=============================================================================
// �Đ�
bool Speaker::Play(void)
{
	// ���ɍĐ����̏ꍇ
	if (_cue != nullptr)
	{
		DWORD _cuestate;
		_cue->GetState(&_cuestate);

		// �L���[���ꎞ��~���̏ꍇ
		if (_cuestate & XACT_CUESTATE_PAUSED) {
			_cue->Pause(FALSE);
			return true;
		}
		return false;
	}

	IXACT3SoundBank* sound_bank = _application->GetXactManager()->GetSoundbank();

	sound_bank->Prepare(static_cast<XACTINDEX>(_cue_index), 0, 0, &_cue);
	HRESULT result = _cue->Play();

	if (result != S_OK)
	{
		return false;
	}

	DWORD _cuestate;
	_cue->GetState(&_cuestate);

	if (_cuestate & XACT_CUESTATE_PLAYING)
	{
		return true;
	}

	return false;
}

//=============================================================================
// ��~
void Speaker::Stop(void)
{
	// �L���[����������Ă��Ȃ��ꍇ
	if (_cue == nullptr)
	{
		return;
	}

	DWORD _cuestate;
	_cue->GetState(&_cuestate);

	if (_cuestate & XACT_CUESTATE_PLAYING)
	{
		// XACT_FLAG__cueSTOP_IMMEDIATE�������Ɏw�肷��Ƌ����I�Ɏ~�߂�
		_cue->Stop(0);
	}
}

//=============================================================================
// �ꎞ��~
void Speaker::Pause(void)
{
	// �L���[����������Ă��Ȃ��ꍇ
	if (_cue == nullptr)
	{
		return;
	}

	DWORD _cuestate;
	_cue->GetState(&_cuestate);

	// Pause()�̈��� TRUE:�ꎞ��~ FALSE:�Đ�
	// �Đ����̏ꍇ
	if (_cuestate & XACT_CUESTATE_PLAYING)
	{
		_cue->Pause(TRUE);
		return;
	}

	// �ꎞ��~���̏ꍇ
	if (_cuestate & XACT_CUESTATE_PAUSED)
	{
		_cue->Pause(FALSE);
		return;
	}
}

//=============================================================================
// �Đ��m�F
bool Speaker::IsPlaying(void) const
{
	// �L���[����������Ă��Ȃ��ꍇ
	if (_cue == nullptr)
	{
		return false;
	}
	DWORD _cuestate;
	_cue->GetState(&_cuestate);

	if (_cuestate & XACT_CUESTATE_PLAYING)
	{
		return true;
	}

	return false;
}

//=============================================================================
// �X�V
void Speaker::Update(void)
{
	// �L���[����������Ă��Ȃ��ꍇ
	if (_cue == nullptr)
	{
		return;
	}

	DWORD _cuestate;
	_cue->GetState(&_cuestate);

	// �L���[�̍Đ����I������ꍇ
	if (_cuestate & XACT_CUESTATE_STOPPED)
	{
		_cue->Destroy();
		_cue = nullptr;
		return;
	}
}
