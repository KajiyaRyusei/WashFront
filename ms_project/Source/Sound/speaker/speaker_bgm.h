//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// BGMスピーカー
//
// Created by Ryusei Kajiya on 20151021
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//*****************************************************************************
// 多重インクルード防止
#pragma once

//*****************************************************************************
// include
#include "speaker.h"

//*****************************************************************************
// 前方宣言
class Application;

//*****************************************************************************
// クラス設計
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
