//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// ミッションUI
// 
// Created by Chiharu Kamiyama on 20151029
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//*****************************************************************************
// 多重インクルード防止
#pragma once

//*****************************************************************************
// include
#include "Unit/unit.h"

//*****************************************************************************
// 前方宣言
class MissionFrame;
class MissionMeter;
class MissionUiTitle;

typedef struct
{
	MissionFrame *_mission_frame;
	MissionMeter *_mission_meter;
	MissionUiTitle *_mission_ui_title;

}MISSION_UI;


//*****************************************************************************
// クラス設計
class MissionUi : public Unit
{
public:

	MissionUi(Application* application, World* world) : Unit(application, world)
	{
		Initialize();
	}
	virtual ~MissionUi(){ Finalize(); }

	virtual void Initialize() override;
	virtual void Finalize() override;
	virtual void Update() override;
	virtual void Draw() override;
	virtual void CollisionUpdate() override;

	//ミッションキャラクター位置設定
	void SetMissonCharacterList(std::list<Unit*> *list);

private:
	MISSION_UI _mission_ui[2];
};