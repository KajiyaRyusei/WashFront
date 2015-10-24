//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// 
// BGM�X�s�[�J�[
// 
// Created by Ryusei Kajiya on 20151021
// 
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//*****************************************************************************
// include
#include "sound/speaker/speaker_bgm.h"
#include "sound/xact/xact_manager.h"
#include "System/application.h"

//=============================================================================
// �Đ�
bool SpeakerBGM::Play(void)
{
	if (_cue != nullptr)
	{
		DWORD cue_state;
		_cue->GetState(&cue_state);
		// �L���[���ꎞ��~���̏ꍇ
		if (cue_state & XACT_CUESTATE_PAUSED)
		{
			_cue->Pause(FALSE);
			return true;
		}
		return false;
	}

	
	IXACT3SoundBank* sound_bank = _application->GetXactManager()->GetSoundbank();
	IXACT3WaveBank* wavebank_streaming = _application->GetXactManager()->GetWavebankStreaming();

	DWORD state = 0;
	// �E�F�[�u�o���N�̏��������m�F
	wavebank_streaming->GetState(&state);

	if (!(state & XACT_STATE_PREPARED))
	{
		return false;
	}

	sound_bank->Prepare(static_cast<XACTINDEX>(_cue_index), 0, 0, &_cue);
	HRESULT result = _cue->Play();

	if (result != S_OK)
	{
		return false;
	}

	DWORD cue_state;
	_cue->GetState(&cue_state);

	if (cue_state & XACT_CUESTATE_PLAYING)
	{
		return true;
	}

	return false;
}

//=============================================================================
// ��~
void SpeakerBGM::Stop(void)
{
	// �L���[����������Ă��Ȃ��ꍇ
	if (_cue == nullptr)
	{
		return;
	}

	DWORD cue_state;
	_cue->GetState(&cue_state);

	if (cue_state & XACT_CUESTATE_PLAYING)
	{
		// XACT_FLAG_CUE_STOP_IMMEDIATE�������Ɏw�肷��Ƌ����I�Ɏ~�߂�
		_cue->Stop(0);
	}
}

//=============================================================================
// �ꎞ��~
void SpeakerBGM::Pause(void)
{
	// �L���[����������Ă��Ȃ��ꍇ
	if (_cue == nullptr)
	{
		return;
	}

	DWORD cue_state;
	_cue->GetState(&cue_state);

	// Pause()�̈��� TRUE:�ꎞ��~ FALSE:�Đ�
	// �ꎞ��~���̏ꍇ(�ꎞ��~�����Ă���Ɠ����t���O�I�ɂ͍Đ���|�ꎞ��~���ɂȂ�)
	if (cue_state & XACT_CUESTATE_PAUSED)
	{
		_cue->Pause(FALSE);
		return;
	}

	// �Đ����̏ꍇ
	if (cue_state & XACT_CUESTATE_PLAYING)
	{
		_cue->Pause(TRUE);
		return;
	}
}

//=============================================================================
// �Đ��m�F
bool SpeakerBGM::IsPlaying(void) const
{
	// �L���[����������Ă��Ȃ��ꍇ
	if (_cue == nullptr)
	{
		return false;
	}

	DWORD cue_state;
	_cue->GetState(&cue_state);

	if (cue_state & XACT_CUESTATE_PLAYING)
	{
		return true;
	}

	return false;
}

//=============================================================================
// �X�V
void SpeakerBGM::Update(void)
{
	// �L���[����������Ă��Ȃ��ꍇ
	if (_cue == nullptr)
	{
		return;
	}

	DWORD cue_state;
	_cue->GetState(&cue_state);

	// �L���[�̍Đ����I�����Ă����ꍇ
	if (cue_state & XACT_CUESTATE_STOPPED)
	{
		_cue->Destroy();
		_cue = nullptr;
		return;
	}
}
