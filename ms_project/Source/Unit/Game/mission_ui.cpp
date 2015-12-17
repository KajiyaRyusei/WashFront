//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// �~�b�V����UI
// 
// Created by Chiharu Kamiyama on 20151111
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//*****************************************************************************
// include
#include "mission_ui.h"
#include "Unit/Game/mission_frame.h"
#include "Unit/Game/mission_meter.h"
#include "Unit/Game/mission_ui_title.h"

#include "Windows/window.h"


//=============================================================================
// ������
void MissionUi::Initialize()
{
}


//=============================================================================
// �I��
void MissionUi::Finalize()
{

}

//=============================================================================
// �X�V
void MissionUi::Update()
{

}

//=============================================================================
// �`��
void MissionUi::Draw()
{
}

//=============================================================================
// �����蔻��
void MissionUi::CollisionUpdate()
{
}


//=============================================================================
//���X�g�Z�b�g
void MissionUi::SetMissonCharacterList(std::list<Unit*> *list)
{
	//�~�b�V�����t���[���̍쐬
	for (int i = 0; i < 2; i++)
	{
		//���[�^�[
		_mission_ui[i]._mission_meter = new MissionMeter(_application, _game_world);
		list->push_back(_mission_ui[i]._mission_meter);

		//�t���[��
		_mission_ui[i]._mission_frame = new MissionFrame(_application, _game_world);
		list->push_back(_mission_ui[i]._mission_frame);

		//�~�b�V�����̕���
		_mission_ui[i]._mission_ui_title = new MissionUiTitle(_application, _game_world);
		list->push_back(_mission_ui[i]._mission_ui_title);


	}

	float window_height = (float)_application->GetWindow()->GetSizeWindowHeight();

	//�ʒu����
	float mission_height = window_height - 210.0f / 2;

	_mission_ui[0]._mission_frame->SetPosition(D3DXVECTOR3( 380, mission_height + 50.f, 0.0f));
	_mission_ui[0]._mission_meter->SetPosition(D3DXVECTOR3(380, mission_height + 70.f, 0.0f));
	_mission_ui[0]._mission_ui_title->SetPosition(D3DXVECTOR3(220, mission_height + 48.f, 0.0f));


	float mission_height_center_distance = mission_height - window_height / 2;
	_mission_ui[1]._mission_frame->SetPosition(D3DXVECTOR3(380.0f, mission_height_center_distance + 30.0f, 0.0f));
	_mission_ui[1]._mission_meter->SetPosition(D3DXVECTOR3(380.0f, mission_height_center_distance + 50.0f, 0.0f));
	_mission_ui[1]._mission_ui_title->SetPosition(D3DXVECTOR3(220.0f, mission_height_center_distance + 28.0f, 0.0f));


}