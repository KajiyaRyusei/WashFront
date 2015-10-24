//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// �V�[���F���U���g
//
// Created by Ryusei Kajiya on 20151011
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//*****************************************************************************
// �C���N���[�h
#include "scene_result.h"
#include "DevelopTool/develop_tool_manager.h"
#include "World/world.h"
#include "World/space_grid.h"

// input
#include "Input/input_manager.h"

// scene
#include "Scene/scene_manager.h"
#include "Scene/scene_spawner.h"
#include "Scene/Scene/scene_title.h"

// unit
#include "Unit/test_unit.h"

//=============================================================================
// �R���X�g���N�^
SceneResult::SceneResult(Application *application) :
	Scene{ application }
{
	Initialize();
}
//=============================================================================
// ������
void SceneResult::Initialize()
{
	SpaceGrid* grid = new SpaceGrid();
	std::list<Unit*> unit_list;
	unit_list.push_back(new TestUnit(_application, grid));

	_world = new World(std::move(unit_list), grid);

}
//=============================================================================
// �I��
void SceneResult::Finalize()
{
	SafeDelete(_world);
	Unit::ResetID();
}
//=============================================================================
// �X�V
void SceneResult::Update()
{
	Reference::GetInstance().GetDevelopToolManager()->GetDebugPrint().Print("���U���g�V�[���ł���\n");

	if( _application->GetInputManager()->CheckTrigger(INPUT_EVENT_RETURN) )
	{
		_application->GetSceneManager()->SetNextScene(new SpawnerForScene<SceneTitle>);
	}

	_world->Update();
}
//=============================================================================
// �`��
void SceneResult::Draw()
{
	_world->Draw();
}
