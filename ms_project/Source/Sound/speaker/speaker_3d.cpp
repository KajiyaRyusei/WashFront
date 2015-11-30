//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// 
// 3Dサウンドスピーカー
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
// 再生
bool Speaker3D::Play(void)
{
	if (_cue != nullptr)
	{
		DWORD cue_state;
		_cue->GetState(&cue_state);

		// キューが一時停止中の場合
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

	// 再生できてるか確認
	DWORD cue_state;
	_cue->GetState(&cue_state);

	if (cue_state & XACT_CUESTATE_PLAYING)
	{
		return true;
	}

	return false;
}

//=============================================================================
// 停止
void Speaker3D::Stop(void)
{
	DWORD cue_state;
	_cue->GetState(&cue_state);

	if (cue_state & XACT_CUESTATE_PLAYING)
	{
		// XACT_FLAG_CUE_STOP_IMMEDIATEを引数に指定すると強制的に止める
		_cue->Stop(0);
	}
}

//=============================================================================
// 一時停止
void Speaker3D::Pause(void)
{
	DWORD cue_state;
	_cue->GetState(&cue_state);

	// Pause()の引数 TRUE:一時停止 FALSE:再生
	// 再生中の場合
	if (cue_state & XACT_CUESTATE_PLAYING)
	{
		_cue->Pause(TRUE);
		return;
	}

	// 一時停止中の場合
	if (cue_state & XACT_CUESTATE_PAUSED)
	{
		_cue->Pause(FALSE);
		return;
	}
}

//=============================================================================
// 再生確認
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
// 更新
void Speaker3D::Update(void)
{
	// キューが生成されていない場合
	if (_cue == nullptr)
	{
		return;
	}

	DWORD cue_state;
	_cue->GetState(&cue_state);

	// キューの再生が終了していた場合
	if (cue_state & XACT_CUESTATE_STOPPED)
	{
		_cue->Destroy();
		_cue = nullptr;
		return;
	}

	// 再生中以外なら処理を行わない
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