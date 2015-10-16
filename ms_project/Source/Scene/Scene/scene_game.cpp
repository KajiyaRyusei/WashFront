//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// シーン：ゲーム
//
// Created by Ryusei Kajiya on 20151011
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//*****************************************************************************
// インクルード
#include "scene_game.h"
#include "DevelopTool/develop_tool_manager.h"
#include "World/world.h"
#include "World/space_grid.h"

// input
#include "Input/input_manager.h"

// scene
#include "Scene/scene_manager.h"
#include "Scene/scene_spawner.h"
#include "Scene/Scene/scene_result.h"

// unit
#include "Unit/test_unit.h"
#include "Unit/screen_unit.h"
#include "Unit/static_model_unit.h"
#include "Unit/animation_model_unit.h"

//=============================================================================
// コンストラクタ
SceneGame::SceneGame(Application *application) :
	Scene{ application }
{
	Initialize();
}
//=============================================================================
// 初期化
void SceneGame::Initialize()
{
	SpaceGrid* grid = new SpaceGrid();
	std::list<Unit*> unit_list;
	unit_list.push_back(new AnimationModelUnit(_application, grid));
	unit_list.push_back(new ScreenUnit(_application, grid));

	_world = new World(std::move(unit_list), grid);

}
//=============================================================================
// 終了
void SceneGame::Finalize()
{
	SafeDelete(_world);
}
//=============================================================================
// 更新
void SceneGame::Update()
{
	Reference::GetInstance().GetDevelopToolManager()->GetDebugPrint().Print("ゲームシーンですよ\n");

	if( _application->GetInputManager()->CheckTrigger(INPUT_EVENT_RETURN) )
	{
		_application->GetSceneManager()->SetNextScene(new SpawnerForScene<SceneResult>);
	}

	_world->Update();
}
//=============================================================================
// 描画
void SceneGame::Draw()
{
	_world->Draw();
}
