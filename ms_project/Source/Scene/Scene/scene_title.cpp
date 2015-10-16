//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// シーン：タイトル
//
// Created by Ryusei Kajiya on 20151011
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//*****************************************************************************
// インクルード
#include "scene_title.h"
#include "DevelopTool/develop_tool_manager.h"
#include "World/world.h"
#include "World/space_grid.h"

// input
#include "Input/input_manager.h"

// scene
#include "Scene/scene_manager.h"
#include "Scene/scene_spawner.h"
#include "Scene/Scene/scene_game.h"

// unit
#include "Unit/test_unit.h"

//=============================================================================
// コンストラクタ
SceneTitle::SceneTitle(Application *application) :
	Scene{ application }
{
	Initialize();
}
//=============================================================================
// 初期化
void SceneTitle::Initialize()
{
	SpaceGrid* grid = new SpaceGrid();
	std::list<Unit*> unit_list;
	unit_list.push_back(new TestUnit(_application, grid));

	_world = new World(std::move(unit_list), grid);

}
//=============================================================================
// 終了
void SceneTitle::Finalize()
{
	SafeDelete(_world);
}
//=============================================================================
// 更新
void SceneTitle::Update()
{
	Reference::GetInstance().GetDevelopToolManager()->GetDebugPrint().Print("タイトルシーンですよ\n");

	if( _application->GetInputManager()->CheckTrigger(INPUT_EVENT_RETURN) )
	{
		_application->GetSceneManager()->SetNextScene(new SpawnerForScene<SceneGame>);
	}

	_world->Update();
}
//=============================================================================
// 描画
void SceneTitle::Draw()
{
	_world->Draw();
}
