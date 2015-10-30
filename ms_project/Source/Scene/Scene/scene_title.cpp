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
	unit_list.push_back(new ScreenUnit(_application, _world));
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
