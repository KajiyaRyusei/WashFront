//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// �~�b�V����UI
// 
// Created by Chiharu Kamiyama on 20151029
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//*****************************************************************************
// ���d�C���N���[�h�h�~
#pragma once

//*****************************************************************************
// include
#include "Unit/unit.h"

//*****************************************************************************
// �O���錾
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
// �N���X�݌v
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

	//�~�b�V�����L�����N�^�[�ʒu�ݒ�
	void SetMissonCharacterList(std::list<Unit*> *list);

private:
	MISSION_UI _mission_ui[2];
};