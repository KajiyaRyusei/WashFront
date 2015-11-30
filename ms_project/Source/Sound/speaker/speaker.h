//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// 
// スピーカー
// 
// Created by Ryusei Kajiya on 20151021
// 
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//*****************************************************************************
// 多重インクルード防止
#pragma once

//*****************************************************************************
// 前方宣言
class Application;

//*****************************************************************************
// 音源一覧
enum XactCueIndex
{// 鳴らすサウンド一覧
	XACTCUEINDEX_DECIDE = 0,
	XACTCUEINDEX_CANCEL,
	XACTCUEINDEX_WATER ,
	XACTCUEINDEX_WALK_GRASS ,
	XACTCUEINDEX_WALK,
	XACTCUEINDEX_ELECTRIC,
	XACTCUEINDEX_SHOT,
	XACTCUEINDEX_EXPLOSION ,
	XACTCUEINDEXBGM_LOSE,
	XACTCUEINDEXBGM_GAME,
	XACTCUEINDEXBGM_WIN ,
	XACTCUEINDEXBGM_TITLE,
	XACTCUEINDEXBGM_LOAD,
	XACTCUEINDEX_MAX,
};

//*****************************************************************************
// クラス設計
class Speaker
{
public:
	Speaker(XactCueIndex cue_index, Application* application) :
		_cue_index(cue_index),
		_cue(nullptr),
		_application(application){}

	virtual ~Speaker()
	{
		if( _cue != nullptr )
		{
			_cue->Destroy();
			_cue = nullptr;
		}
	}

	virtual bool Play(void);
	virtual void Pause(void);
	virtual void Stop(void);
	virtual bool IsPlaying (void) const;
	virtual void Update(void);

protected:

	IXACT3Cue* _cue;
	XactCueIndex _cue_index;
	Application* _application;
};
