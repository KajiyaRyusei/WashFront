//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// �V�[���F�^�C�g��
//
// Created by Ryusei Kajiya on 20151029
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//*****************************************************************************
// �C���N���[�h
#include "scene_title.h"
#include "DevelopTool/develop_tool_manager.h"
#include "World/world.h"

// input
#include "Input/input_manager.h"

// scene
#include "Scene/scene_manager.h"
#include "Scene/scene_spawner.h"
#include "Scene/Scene/scene_game.h"

// unit
#include "Unit/screen_unit.h"
#include "Unit\Title\text.h"
#include "Unit\Title/logo_bg.h"
#include "Unit\Title\logo.h"
#include "Unit/Game/player.h"
#include "Unit/Game/back_ground.h"
#include "Unit/Game/building.h"

#include "World/collision_grid.h"

//=============================================================================
// �R���X�g���N�^
SceneTitle::SceneTitle(Application *application) :
	Scene{ application }
{
	Initialize();
}
//=============================================================================
// ������
void SceneTitle::Initialize()
{
	_world = new World();
	std::list<Unit*> unit_list;
	
	// �I�u�W�F�N�g����

	// 2D�I�u�W�F�N�g
	unit_list.push_back(new TextUnit(_application, _world));
	unit_list.push_back(new Logo_BGUnit(_application, _world));
	unit_list.push_back(new LogoUnit(_application, _world));

	// �r��
	BuildingUnit* bill_0 = new BuildingUnit(_application, _world);
	BuildingUnit* bill_1 = new BuildingUnit(_application, _world);
	BuildingUnit* bill_2 = new BuildingUnit(_application, _world);
	BuildingUnit* bill_3 = new BuildingUnit(_application, _world);
	BuildingUnit* bill_4 = new BuildingUnit(_application, _world);
	BuildingUnit* bill_5 = new BuildingUnit(_application, _world);
	BuildingUnit* bill_6 = new BuildingUnit(_application, _world);
	BuildingUnit* bill_7 = new BuildingUnit(_application, _world);
	BuildingUnit* bill_8 = new BuildingUnit(_application, _world);
	BuildingUnit* bill_9 = new BuildingUnit(_application, _world);
	BuildingUnit* bill_10 = new BuildingUnit(_application, _world);
	BuildingUnit* bill_11 = new BuildingUnit(_application, _world);
	BuildingUnit* bill_12 = new BuildingUnit(_application, _world);
	BuildingUnit* bill_13 = new BuildingUnit(_application, _world);
	BuildingUnit* bill_14 = new BuildingUnit(_application, _world);
	BuildingUnit* bill_15 = new BuildingUnit(_application, _world);
	BuildingUnit* bill_16 = new BuildingUnit(_application, _world);

	D3DXVECTOR3 bull_position = _world->GetCollisionGrid()->CellCenterPoint(0, 0);
	bill_0->SetPosition(bull_position);
	bull_position = _world->GetCollisionGrid()->CellCenterPoint(1, 0);
	bill_1->SetPosition(bull_position);
	bull_position = _world->GetCollisionGrid()->CellCenterPoint(2, 0);
	bill_2->SetPosition(bull_position);
	bull_position = _world->GetCollisionGrid()->CellCenterPoint(3, 0);
	bill_3->SetPosition(bull_position);
	bull_position = _world->GetCollisionGrid()->CellCenterPoint(4, 0);
	bill_4->SetPosition(bull_position);
	bull_position = _world->GetCollisionGrid()->CellCenterPoint(0, 1);
	bill_5->SetPosition(bull_position);
	bull_position = _world->GetCollisionGrid()->CellCenterPoint(0, 2);
	bill_6->SetPosition(bull_position);
	bull_position = _world->GetCollisionGrid()->CellCenterPoint(0, 3);
	bill_7->SetPosition(bull_position);
	bull_position = _world->GetCollisionGrid()->CellCenterPoint(0, 4);
	bill_8->SetPosition(bull_position);
	bull_position = _world->GetCollisionGrid()->CellCenterPoint(2, 2);
	bill_9->SetPosition(bull_position);
	bull_position = _world->GetCollisionGrid()->CellCenterPoint(1, 4);
	bill_10->SetPosition(bull_position);
	bull_position = _world->GetCollisionGrid()->CellCenterPoint(2, 4);
	bill_11->SetPosition(bull_position);
	bull_position = _world->GetCollisionGrid()->CellCenterPoint(3, 4);
	bill_12->SetPosition(bull_position);
	bull_position = _world->GetCollisionGrid()->CellCenterPoint(4, 4);
	bill_13->SetPosition(bull_position);
	bull_position = _world->GetCollisionGrid()->CellCenterPoint(4, 1);
	bill_14->SetPosition(bull_position);
	bull_position = _world->GetCollisionGrid()->CellCenterPoint(4, 2);
	bill_15->SetPosition(bull_position);
	bull_position = _world->GetCollisionGrid()->CellCenterPoint(4, 3);
	bill_16->SetPosition(bull_position);

	unit_list.push_back(bill_0);
	unit_list.push_back(bill_1);
	unit_list.push_back(bill_2);
	unit_list.push_back(bill_3);
	unit_list.push_back(bill_4);
	unit_list.push_back(bill_5);
	unit_list.push_back(bill_6);
	unit_list.push_back(bill_7);
	unit_list.push_back(bill_8);
	unit_list.push_back(bill_9);
	unit_list.push_back(bill_10);
	unit_list.push_back(bill_11);
	unit_list.push_back(bill_12);
	unit_list.push_back(bill_13);
	unit_list.push_back(bill_14);
	unit_list.push_back(bill_15);
	unit_list.push_back(bill_16);

	// �v���C���[
	unit_list.push_back(new PlayerUnit(_application, _world));
	// �w�i
	unit_list.push_back(new BackGroundUnit(_application, _world));

	_world->PushUnit(std::move(unit_list));

}
//=============================================================================
// �I��
void SceneTitle::Finalize()
{
	SafeDelete(_world);
	Unit::ResetID();
}
//=============================================================================
// �X�V
void SceneTitle::Update()
{
	Reference::GetInstance().GetDevelopToolManager()->GetDebugPrint().Print("�^�C�g���V�[���ł���\n");

	if( _application->GetInputManager()->CheckTrigger(INPUT_EVENT_RETURN) )
	{
		_application->GetSceneManager()->SetNextScene(new SpawnerForScene<SceneGame>);
	}

	_world->Update();
}
//=============================================================================
// �`��
void SceneTitle::Draw()
{
	_world->Draw();
}
