//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// シーン：ゲーム
//
// Created by Ryusei Kajiya on 20151123
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//*****************************************************************************
// インクルード
#include "scene_game.h"
#include "DevelopTool/develop_tool_manager.h"
#include "World/world.h"

// input
#include "Input/input_manager.h"

// scene
#include "Scene/scene_manager.h"
#include "Scene/scene_spawner.h"
#include "Scene/Scene/scene_result.h"

// unit
#include "Unit/Game/player.h"
#include "Unit/Game/back_ground.h"
#include "Unit/Game/building.h"
#include "Unit/Game/dirt.h"


// 空間
#include "World/collision_grid.h"

// resource
#include "Resource/animation_mesh_resource.h"
#include "Resource/static_mesh_resource.h"
#include "Resource/cube_texture_resource.h"
#include "Resource/texture_resource.h"
#include "Resource/mesh_resource.h"

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
	_world = new World();
	ResourceGeneration();
	MapGeneration();
}
//=============================================================================
// 終了
void SceneGame::Finalize()
{
	SafeDelete(_world);
	Unit::ResetID();
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


//=============================================================================
// マップの作成
void SceneGame::MapGeneration()
{
	std::list<Unit*> unit_list;
	unit_list.push_back(new PlayerUnit(_application, _world));
	unit_list.push_back(new BackGroundUnit(_application, _world));

	// ビル
	D3DXVECTOR3 bill_position = _world->GetCollisionGrid()->CellCenterPoint(0, 0);
	D3DXVECTOR3 bill_rotation(0.f, 0.f, 0.f);
	D3DXVECTOR3 bill_scaling(0.1f, 0.1f, 0.1f);
	BuildingUnit* bill_0 = new BuildingUnit(_application, _world, bill_position, bill_rotation, bill_scaling);
	bill_position = _world->GetCollisionGrid()->CellCenterPoint(1, 0);
	BuildingUnit* bill_1 = new BuildingUnit(_application, _world, bill_position, bill_rotation, bill_scaling);
	bill_position = _world->GetCollisionGrid()->CellCenterPoint(2, 0);
	BuildingUnit* bill_2 = new BuildingUnit(_application, _world, bill_position, bill_rotation, bill_scaling);
	bill_position = _world->GetCollisionGrid()->CellCenterPoint(3, 0);
	BuildingUnit* bill_3 = new BuildingUnit(_application, _world, bill_position, bill_rotation, bill_scaling);
	bill_position = _world->GetCollisionGrid()->CellCenterPoint(4, 0);
	BuildingUnit* bill_4 = new BuildingUnit(_application, _world, bill_position, bill_rotation, bill_scaling);
	bill_position = _world->GetCollisionGrid()->CellCenterPoint(0, 1);
	BuildingUnit* bill_5 = new BuildingUnit(_application, _world, bill_position, bill_rotation, bill_scaling);
	bill_position = _world->GetCollisionGrid()->CellCenterPoint(0, 2);
	BuildingUnit* bill_6 = new BuildingUnit(_application, _world, bill_position, bill_rotation, bill_scaling);
	bill_position = _world->GetCollisionGrid()->CellCenterPoint(0, 3);
	BuildingUnit* bill_7 = new BuildingUnit(_application, _world, bill_position, bill_rotation, bill_scaling);
	bill_position = _world->GetCollisionGrid()->CellCenterPoint(0, 4);
	BuildingUnit* bill_8 = new BuildingUnit(_application, _world, bill_position, bill_rotation, bill_scaling);
	bill_position = _world->GetCollisionGrid()->CellCenterPoint(2, 2);
	BuildingUnit* bill_9 = new BuildingUnit(_application, _world, bill_position, bill_rotation, bill_scaling);
	bill_position = _world->GetCollisionGrid()->CellCenterPoint(1, 4);
	BuildingUnit* bill_10 = new BuildingUnit(_application, _world, bill_position, bill_rotation, bill_scaling);
	bill_position = _world->GetCollisionGrid()->CellCenterPoint(2, 4);
	BuildingUnit* bill_11 = new BuildingUnit(_application, _world, bill_position, bill_rotation, bill_scaling);
	bill_position = _world->GetCollisionGrid()->CellCenterPoint(3, 4);
	BuildingUnit* bill_12 = new BuildingUnit(_application, _world, bill_position, bill_rotation, bill_scaling);
	bill_position = _world->GetCollisionGrid()->CellCenterPoint(4, 4);
	BuildingUnit* bill_13 = new BuildingUnit(_application, _world, bill_position, bill_rotation, bill_scaling);
	bill_position = _world->GetCollisionGrid()->CellCenterPoint(4, 1);
	BuildingUnit* bill_14 = new BuildingUnit(_application, _world, bill_position, bill_rotation, bill_scaling);
	bill_position = _world->GetCollisionGrid()->CellCenterPoint(4, 2);
	BuildingUnit* bill_15 = new BuildingUnit(_application, _world, bill_position, bill_rotation, bill_scaling);
	bill_position = _world->GetCollisionGrid()->CellCenterPoint(4, 3);
	BuildingUnit* bill_16 = new BuildingUnit(_application, _world, bill_position, bill_rotation, bill_scaling);

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
	unit_list.push_back(bill_16);;

	_world->PushUnit(std::move(unit_list));
}

//=============================================================================
// リソースの作成
void SceneGame::ResourceGeneration()
{
	// メッシュ
	_world->GetMeshResource()->Create(MESH_RESOURE_BOX, _application->GetRendererDevice());
	_world->GetMeshResource()->Create(MESH_RESOURE_SPRITE, _application->GetRendererDevice());
	_world->GetMeshResource()->Create(MESH_RESOURE_MESH_FIELD, _application->GetRendererDevice());
	_world->GetMeshResource()->Create(MESH_RESOURE_WATER_CYLINDER, _application->GetRendererDevice());
	_world->GetMeshResource()->Create(MESH_RESOURE_WATER_CYLINDER_BACK, _application->GetRendererDevice());

	// テクスチャ
	_world->GetTextureResource()->Create(TEXTURE_RESOURE_BILL_TEXTURE, _application->GetRendererDevice());
	_world->GetTextureResource()->Create(TEXTURE_RESOURE_AIM_TEXTURE, _application->GetRendererDevice());
	_world->GetTextureResource()->Create(TEXTURE_RESOURE_DIRT_NORMAL_TEXTURE, _application->GetRendererDevice());
	_world->GetTextureResource()->Create(TEXTURE_RESOURE_WATER_BALL_TEXTURE, _application->GetRendererDevice());
	_world->GetTextureResource()->Create(TEXTURE_RESOURE_WATER_NORMAL_TEXTURE, _application->GetRendererDevice());
	_world->GetTextureResource()->Create(TEXTURE_RESOURE_PLAYER_TEXTURE, _application->GetRendererDevice());
	_world->GetTextureResource()->Create(TEXTURE_RESOURE_BILL_METALNESS_TEXTURE, _application->GetRendererDevice());
	_world->GetTextureResource()->Create(TEXTURE_RESOURE_DIRTY_TEXTURE, _application->GetRendererDevice());

	// キューブマップ
	_world->GetCubeTextureResource()->Create(CUBE_TEXTURE_RESOURE_GRID_ZERO_ZERO_DIFFUSE, _application->GetRendererDevice());
	_world->GetCubeTextureResource()->Create(CUBE_TEXTURE_RESOURE_GRID_ZERO_ZERO_SPECULAR, _application->GetRendererDevice());

	// SMO
	_world->GetStaticMeshResource()->Create(STATIC_MESH_RESOURE_BILL, _application->GetRendererDevice());

	// AMO
	_world->GetAnimationMeshResource()->Create(ANIMATION_MESH_RESOURE_WEAPON_01, _application->GetRendererDevice());
	_world->GetAnimationMeshResource()->Create(ANIMATION_MESH_RESOURE_GRANDPA, _application->GetRendererDevice());
}