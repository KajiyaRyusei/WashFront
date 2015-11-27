//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// シーン：リザルト
//
// Created by Ryusei Kajiya on 20151029
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//*****************************************************************************
// インクルード
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
// コンストラクタ
SceneResult::SceneResult(Application *application) :
	Scene{ application }
{
	Initialize();
}
//=============================================================================
// 初期化
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
// 終了
void SceneResult::Finalize()
{
	SafeDelete(_world);
	Unit::ResetID();
}
//=============================================================================
// 更新
void SceneResult::Update()
{
	Reference::GetInstance().GetDevelopToolManager()->GetDebugPrint().Print("リザルトシーンですよ\n");

	if( _application->GetInputManager()->CheckTrigger(INPUT_EVENT_RETURN) )
	{
		_application->GetSceneManager()->SetNextScene(new SpawnerForScene<SceneTitle>);
	}

	_world->Update();
}
//=============================================================================
// 描画
void SceneResult::Draw()
{
	_world->Draw();
}
