//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// �V�[���F���U���g
//
// Created by Ryusei Kajiya on 20151029
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//*****************************************************************************
// �C���N���[�h
#include "scene_result.h"
#include "DevelopTool/develop_tool_manager.h"
#include "World/world.h"

// input
#include "Input/input_manager.h"

// scene
#include "Scene/scene_manager.h"
#include "Scene/scene_spawner.h"
#include "Scene/Scene/scene_title.h"

// unit
#include "Unit/screen_unit.h"
#include "Unit/dummy_ui.h"

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
	_world = new World();
	std::list<Unit*> unit_list;

	//UI
	DummyUi *dummy_ui;
	dummy_ui = new DummyUi(_application, _world);
	_world->SetUi(dummy_ui);

	unit_list.push_back(new ScreenUnit(_application, _world));
	_world->PushUnit(std::move(unit_list));

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
