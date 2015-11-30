//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// 
// 3D�T�E���h�X�s�[�J�[
// 
// Created by Ryusei Kajiya on 20151021
// 
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//*****************************************************************************
// include
#include "sound/speaker/speaker_3d.h"
#include "sound/xact/xact_manager.h"
#include "System/application.h"

//=============================================================================
// �Đ�
bool Speaker3D::Play(void)
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
	X3DAUDIO_LISTENER listener = _application->GetXactManager()->GetListener();
	auto x3daudio = _application->GetXactManager()->GetHandleX3daudio();
	X3DAUDIO_DSP_SETTINGS dsp_setting = _application->GetXactManager()->GetDspSeetting();

	sound_bank->Prepare(static_cast<XACTINDEX>(_cue_index), 0, 0, &_cue);
	XACT3DCalculate(*x3daudio, &listener, &_emitter, &dsp_setting);
	XACT3DApply(&dsp_setting, _cue);
	HRESULT result = _cue->Play();

	if (result != S_OK)
	{
		return false;
	}

	// �Đ��ł��Ă邩�m�F
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
void Speaker3D::Stop(void)
{
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
void Speaker3D::Pause(void)
{
	DWORD cue_state;
	_cue->GetState(&cue_state);

	// Pause()�̈��� TRUE:�ꎞ��~ FALSE:�Đ�
	// �Đ����̏ꍇ
	if (cue_state & XACT_CUESTATE_PLAYING)
	{
		_cue->Pause(TRUE);
		return;
	}

	// �ꎞ��~���̏ꍇ
	if (cue_state & XACT_CUESTATE_PAUSED)
	{
		_cue->Pause(FALSE);
		return;
	}
}

//=============================================================================
// �Đ��m�F
bool Speaker3D::IsPlaying(void) const
{
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
void Speaker3D::Update(void)
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

	// �Đ����ȊO�Ȃ珈�����s��Ȃ�
	if (!(cue_state & XACT_CUESTATE_PLAYING))
	{
		return;
	}

	X3DAUDIO_LISTENER listener = _application->GetXactManager()->GetListener();
	auto x3daudio = _application->GetXactManager()->GetHandleX3daudio();
	X3DAUDIO_DSP_SETTINGS dsp_setting = _application->GetXactManager()->GetDspSeetting();

	XACT3DCalculate((*x3daudio), &listener, &_emitter, &dsp_setting);
	XACT3DApply(&dsp_setting, _cue);
}