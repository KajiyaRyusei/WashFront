//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// 
// スピーカー
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
// 再生
bool Speaker::Play(void)
{
	// 既に再生中の場合
	if (_cue != nullptr)
	{
		DWORD _cuestate;
		_cue->GetState(&_cuestate);

		// キューが一時停止中の場合
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
// 停止
void Speaker::Stop(void)
{
	// キューが生成されていない場合
	if (_cue == nullptr)
	{
		return;
	}

	DWORD _cuestate;
	_cue->GetState(&_cuestate);

	if (_cuestate & XACT_CUESTATE_PLAYING)
	{
		// XACT_FLAG__cueSTOP_IMMEDIATEを引数に指定すると強制的に止める
		_cue->Stop(0);
	}
}

//=============================================================================
// 一時停止
void Speaker::Pause(void)
{
	// キューが生成されていない場合
	if (_cue == nullptr)
	{
		return;
	}

	DWORD _cuestate;
	_cue->GetState(&_cuestate);

	// Pause()の引数 TRUE:一時停止 FALSE:再生
	// 再生中の場合
	if (_cuestate & XACT_CUESTATE_PLAYING)
	{
		_cue->Pause(TRUE);
		return;
	}

	// 一時停止中の場合
	if (_cuestate & XACT_CUESTATE_PAUSED)
	{
		_cue->Pause(FALSE);
		return;
	}
}

//=============================================================================
// 再生確認
bool Speaker::IsPlaying(void) const
{
	// キューが生成されていない場合
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
// 更新
void Speaker::Update(void)
{
	// キューが生成されていない場合
	if (_cue == nullptr)
	{
		return;
	}

	DWORD _cuestate;
	_cue->GetState(&_cuestate);

	// キューの再生が終わった場合
	if (_cuestate & XACT_CUESTATE_STOPPED)
	{
		_cue->Destroy();
		_cue = nullptr;
		return;
	}
}
