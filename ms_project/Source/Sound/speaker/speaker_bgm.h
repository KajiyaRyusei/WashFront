//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// BGM�X�s�[�J�[
//
// Created by Ryusei Kajiya on 20151021
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//*****************************************************************************
// ���d�C���N���[�h�h�~
#pragma once

//*****************************************************************************
// include
#include "speaker.h"

//*****************************************************************************
// �O���錾
class Application;

//*****************************************************************************
// �N���X�݌v
class SpeakerBGM : public Speaker
{
public:
	SpeakerBGM(XactCueIndex cue_index, Application* application) :
		Speaker(cue_index, application){}
	virtual ~SpeakerBGM(){}
	bool Play(void);
	void Pause(void);
	void Stop(void);

	bool IsPlaying(void) const;

	void Update(void);

private:
	fx32 volume;
};
