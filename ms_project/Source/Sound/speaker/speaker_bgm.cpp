//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// 
// BGMスピーカー
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
// 再生
bool SpeakerBGM::Play(void)
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
	IXACT3WaveBank* wavebank_streaming = _application->GetXactManager()->GetWavebankStreaming();

	DWORD state = 0;
	// ウェーブバンクの準備完了確認
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
// 停止
void SpeakerBGM::Stop(void)
{
	// キューが生成されていない場合
	if (_cue == nullptr)
	{
		return;
	}

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
void SpeakerBGM::Pause(void)
{
	// キューが生成されていない場合
	if (_cue == nullptr)
	{
		return;
	}

	DWORD cue_state;
	_cue->GetState(&cue_state);

	// Pause()の引数 TRUE:一時停止 FALSE:再生
	// 一時停止中の場合(一時停止をしていると内部フラグ的には再生中|一時停止中になる)
	if (cue_state & XACT_CUESTATE_PAUSED)
	{
		_cue->Pause(FALSE);
		return;
	}

	// 再生中の場合
	if (cue_state & XACT_CUESTATE_PLAYING)
	{
		_cue->Pause(TRUE);
		return;
	}
}

//=============================================================================
// 再生確認
bool SpeakerBGM::IsPlaying(void) const
{
	// キューが生成されていない場合
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
// 更新
void SpeakerBGM::Update(void)
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
}
