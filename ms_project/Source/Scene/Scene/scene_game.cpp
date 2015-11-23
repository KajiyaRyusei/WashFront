//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// シーン：ゲーム
//
// Created by Ryusei Kajiya on 20151029
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
#include "Unit/Game/map.h"


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
<<<<<<< HEAD
	ResourceGeneration();
	MapGeneration();
=======
	std::list<Unit*> unit_list;
	unit_list.push_back(new PlayerUnit(_application, _world));
	unit_list.push_back(new BackGroundUnit(_application, _world));

	// ビル
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


	// ごみ
	/*DirtUnit* dirt_0 = new DirtUnit(_application, _world);
	DirtUnit* dirt_1 = new DirtUnit(_application, _world);
	DirtUnit* dirt_2 = new DirtUnit(_application, _world);
	DirtUnit* dirt_3 = new DirtUnit(_application, _world);
	DirtUnit* dirt_4 = new DirtUnit(_application, _world);
	DirtUnit* dirt_5 = new DirtUnit(_application, _world);
	DirtUnit* dirt_6 = new DirtUnit(_application, _world);
	DirtUnit* dirt_7 = new DirtUnit(_application, _world);
	DirtUnit* dirt_8 = new DirtUnit(_application, _world);
	DirtUnit* dirt_9 = new DirtUnit(_application, _world);

	D3DXVECTOR3 dirt_position = _world->GetCollisionGrid()->CellCenterPoint(0, 1);
	dirt_position += D3DXVECTOR3(5, 5, 15);
	dirt_0->SetPosition(dirt_position);
	dirt_position = _world->GetCollisionGrid()->CellCenterPoint(1, 0);
	dirt_position += D3DXVECTOR3(15, -5, 5);
	dirt_1->SetPosition(dirt_position);
	dirt_position = _world->GetCollisionGrid()->CellCenterPoint(2, 0);
	dirt_position += D3DXVECTOR3(15, 0, 15);
	dirt_2->SetPosition(dirt_position);
	dirt_position = _world->GetCollisionGrid()->CellCenterPoint(4, 2);
	dirt_position += D3DXVECTOR3(5, 7, 15);
	dirt_3->SetPosition(dirt_position);
	dirt_position = _world->GetCollisionGrid()->CellCenterPoint(2, 2);
	dirt_position += D3DXVECTOR3(5, -2, 15);
	dirt_4->SetPosition(dirt_position);
	dirt_position = _world->GetCollisionGrid()->CellCenterPoint(2, 2);
	dirt_position += D3DXVECTOR3(15, 10, 5);
	dirt_5->SetPosition(dirt_position);
	dirt_position = _world->GetCollisionGrid()->CellCenterPoint(0, 2);
	dirt_position += D3DXVECTOR3(5, 2, 15);
	dirt_6->SetPosition(dirt_position);
	dirt_position = _world->GetCollisionGrid()->CellCenterPoint(2, 4);
	dirt_position += D3DXVECTOR3(5, -3, -15);
	dirt_7->SetPosition(dirt_position);
	dirt_position = _world->GetCollisionGrid()->CellCenterPoint(3, 4);
	dirt_position += D3DXVECTOR3(5, 5, -15);
	dirt_8->SetPosition(dirt_position);
	dirt_position = _world->GetCollisionGrid()->CellCenterPoint(0, 3);
	dirt_position += D3DXVECTOR3(15, 8, 5);
	dirt_9->SetPosition(dirt_position);

	unit_list.push_back(dirt_0);
	unit_list.push_back(dirt_1);
	unit_list.push_back(dirt_2);
	unit_list.push_back(dirt_3);
	unit_list.push_back(dirt_4);
	unit_list.push_back(dirt_5);
	unit_list.push_back(dirt_6);
	unit_list.push_back(dirt_7);
	unit_list.push_back(dirt_8);
	unit_list.push_back(dirt_9);
*/
	//マップ
	unit_list.push_back(new Map(_application, _world));


	_world->PushUnit(std::move(unit_list));
>>>>>>> origin/Mochizuki-desk
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
	// BuildingUnit* bill_0 = new BuildingUnit(_application, _world);
	// BuildingUnit* bill_1 = new BuildingUnit(_application, _world);
	// BuildingUnit* bill_2 = new BuildingUnit(_application, _world);
	// BuildingUnit* bill_3 = new BuildingUnit(_application, _world);
	// BuildingUnit* bill_4 = new BuildingUnit(_application, _world);
	// BuildingUnit* bill_5 = new BuildingUnit(_application, _world);
	// BuildingUnit* bill_6 = new BuildingUnit(_application, _world);
	// BuildingUnit* bill_7 = new BuildingUnit(_application, _world);
	// BuildingUnit* bill_8 = new BuildingUnit(_application, _world);
	D3DXVECTOR3 bull_position = _world->GetCollisionGrid()->CellCenterPoint(2, 2);
	bull_position.y -= 10.f;
	D3DXVECTOR3 bull_rotation(0.f,0.f,0.f);
	D3DXVECTOR3 bull_scaling(0.1f, 0.1f, 0.1f);
	BuildingUnit* bill_9 = new BuildingUnit(_application, _world, bull_position, bull_rotation, bull_scaling);
	// BuildingUnit* bill_10 = new BuildingUnit(_application, _world);
	// BuildingUnit* bill_11 = new BuildingUnit(_application, _world);
	// BuildingUnit* bill_12 = new BuildingUnit(_application, _world);
	// BuildingUnit* bill_13 = new BuildingUnit(_application, _world);
	// BuildingUnit* bill_14 = new BuildingUnit(_application, _world);
	// BuildingUnit* bill_15 = new BuildingUnit(_application, _world);
	// BuildingUnit* bill_16 = new BuildingUnit(_application, _world);

	//bill_0->SetPosition(bull_position);
	//bull_position = _world->GetCollisionGrid()->CellCenterPoint(1, 0);
	//bill_1->SetPosition(bull_position);
	//bull_position = _world->GetCollisionGrid()->CellCenterPoint(2, 0);
	//bill_2->SetPosition(bull_position);
	//bull_position = _world->GetCollisionGrid()->CellCenterPoint(3, 0);
	//bill_3->SetPosition(bull_position);
	//bull_position = _world->GetCollisionGrid()->CellCenterPoint(4, 0);
	//bill_4->SetPosition(bull_position);
	//bull_position = _world->GetCollisionGrid()->CellCenterPoint(0, 1);
	//bill_5->SetPosition(bull_position);
	//bull_position = _world->GetCollisionGrid()->CellCenterPoint(0, 2);
	//bill_6->SetPosition(bull_position);
	//bull_position = _world->GetCollisionGrid()->CellCenterPoint(0, 3);
	//bill_7->SetPosition(bull_position);
	//bull_position = _world->GetCollisionGrid()->CellCenterPoint(0, 4);
	//bill_8->SetPosition(bull_position);
	
	//bull_position = D3DXVECTOR3(0.f,0.f,0.f);
	//bull_position = _world->GetCollisionGrid()->CellCenterPoint(1, 4);
	//bill_10->SetPosition(bull_position);
	//bull_position = _world->GetCollisionGrid()->CellCenterPoint(2, 4);
	//bill_11->SetPosition(bull_position);
	//bull_position = _world->GetCollisionGrid()->CellCenterPoint(3, 4);
	//bill_12->SetPosition(bull_position);
	//bull_position = _world->GetCollisionGrid()->CellCenterPoint(4, 4);
	//bill_13->SetPosition(bull_position);
	//bull_position = _world->GetCollisionGrid()->CellCenterPoint(4, 1);
	//bill_14->SetPosition(bull_position);
	//bull_position = _world->GetCollisionGrid()->CellCenterPoint(4, 2);
	//bill_15->SetPosition(bull_position);
	//bull_position = _world->GetCollisionGrid()->CellCenterPoint(4, 3);
	//bill_16->SetPosition(bull_position);

	//unit_list.push_back(bill_0);
	//unit_list.push_back(bill_1);
	//unit_list.push_back(bill_2);
	//unit_list.push_back(bill_3);
	//unit_list.push_back(bill_4);
	//unit_list.push_back(bill_5);
	//unit_list.push_back(bill_6);
	//unit_list.push_back(bill_7);
	//unit_list.push_back(bill_8);
	unit_list.push_back(bill_9);
	//unit_list.push_back(bill_10);
	//unit_list.push_back(bill_11);
	//unit_list.push_back(bill_12);
	//unit_list.push_back(bill_13);
	//unit_list.push_back(bill_14);
	//unit_list.push_back(bill_15);
	//unit_list.push_back(bill_16);

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