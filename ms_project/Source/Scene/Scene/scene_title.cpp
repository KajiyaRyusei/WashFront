//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// シーン：タイトル
//
// Created by Ryusei Kajiya on 20151130
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//*****************************************************************************
// インクルード
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
#include "Unit/Game/water_spray_pool_dummy.h"
#include "World/collision_grid.h"

// resource
#include "Resource/animation_mesh_resource.h"
#include "Resource/static_mesh_resource.h"
#include "Resource/cube_texture_resource.h"
#include "Resource/texture_resource.h"
#include "Resource/mesh_resource.h"

// viewport
#include "Renderer/directx9.h"
#include "Windows/window.h"

// カメラ
#include "Camera/camera_manager.h"
#include "Camera/Camera/camera_game_player.h"
#include "Camera/Camera/camera_title.h"

// 汚れ
#include "Data/data_dirt.h"

// ルート
#include "Data/data_route.h"

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
	_world = new World();
	WaterSprayPool* water_spray_pool = new WaterSprayPool(_application, _world);
	_world->SetWaterSprayPool(water_spray_pool);
	ResourceGeneration();
	MapGeneration();

}
//=============================================================================
// 終了
void SceneTitle::Finalize()
{
	SafeDelete(_world);
	Unit::ResetID();
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

	D3DVIEWPORT9 viewport;
	viewport.Height = _application->GetWindow()->GetSizeWindowHeight();
	viewport.Width = _application->GetWindow()->GetSizeWindowWidth();
	viewport.X = 0;
	viewport.Y = 0;
	viewport.MaxZ = 1.f;
	viewport.MinZ = 0.f;

	_application->GetRendererDevice()->GetDevice()->SetViewport(&viewport);
	_application->GetCameraManager()->SetCurrentCamera(_application->GetCameraManager()->GetCamera(CAMERA_TYPE_TITLE));
	// コマンドにたまっているものを描画
	_application->GetCommandBuffer()->Sort();
	_application->GetCommandProcessor()->ProccessLightDepth();
	_application->GetCommandProcessor()->ProccessShadow();
	_application->GetCommandProcessor()->ProccessDefault();
	_application->GetCommandProcessor()->ProccessField();
	_application->GetCommandProcessor()->ProccessBackGround();
	_application->GetCommandProcessor()->ProccessTranslucent();
	_application->GetCommandProcessor()->ProccessAIM();
	_application->GetCommandProcessor()->Proccess2D();
	_application->GetCommandBuffer()->Clear();
}

//=============================================================================
// マップの作成
void SceneTitle::MapGeneration()
{
	std::list<Unit*> unit_list;

	// 2Dオブジェクト
	unit_list.push_back(new TextUnit(_application, _world));
	unit_list.push_back(new Logo_BGUnit(_application, _world));
	unit_list.push_back(new LogoUnit(_application, _world));

	// プレイヤー
	CameraGamePlayer* camera_1p = static_cast<CameraGamePlayer*>(_application->GetCameraManager()->GetCamera(CAMERA_TYPE_GAME_PLAYER_1P));
	PlayerUnit* player_1p = new PlayerUnit(_application, _world, camera_1p);
	unit_list.push_back(player_1p);

	// 背景
	unit_list.push_back(new BackGroundUnit(_application, _world));

	// マップファイル読み込み
	FILE* file;
	file = fopen("Data/Map/test.map", "rt");

	s32 object_number = 0;

	for( ;; )
	{// オブジェクト数取得
		char string[4096] = {};

		if( EOF == fscanf(file, "%s", string) )
		{
			break;
		}

		if( !strcmp(string, "#OBJNUM") )
		{
			fscanf(file, "%d", &object_number);
		}
	}

	fseek(file, 0, SEEK_SET);

	for( ;; )
	{
		char string[4096] = {};

		if( EOF == fscanf(file, "%s", string) )
		{
			break;
		}

		if( !strcmp(string, "#OBJ") )
		{
			for( s32 i = 0; i < object_number; ++i )
			{
				s32 model_id = 0;
				s32 texture_id = 0;
				D3DXVECTOR3 position;
				D3DXVECTOR3 rotation;
				D3DXVECTOR3 scale;

				fscanf(file, "%d %d %f %f %f %f %f %f %f %f %f",
					&model_id, &texture_id,
					&position.x, &position.y, &position.z,
					&rotation.x, &rotation.y, &rotation.z,
					&scale.x, &scale.y, &scale.z);

				BuildingUnit* bill = new BuildingUnit(_application, _world, position, rotation, scale);

				unit_list.push_back(bill);
			}
		}
	}

	fclose(file);

	_world->PushUnit(std::move(unit_list));
}

//=============================================================================
// リソースの作成
void SceneTitle::ResourceGeneration()
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
	_world->GetTextureResource()->Create(TEXTURE_RESOURE_PLAYER_BAG_TEXTURE, _application->GetRendererDevice());
	_world->GetTextureResource()->Create(TEXTURE_RESOURE_PLAYER_BAG_METALNESS_TEXTURE, _application->GetRendererDevice());
	_world->GetTextureResource()->Create(TEXTURE_RESOURE_PLAYER_METALNESS_TEXTURE, _application->GetRendererDevice());

	// キューブマップ
	_world->GetCubeTextureResource()->Create(CUBE_TEXTURE_RESOURE_GRID_ZERO_ZERO_DIFFUSE, _application->GetRendererDevice());
	_world->GetCubeTextureResource()->Create(CUBE_TEXTURE_RESOURE_GRID_ZERO_ZERO_SPECULAR, _application->GetRendererDevice());
	_world->GetCubeTextureResource()->Create(CUBE_TEXTURE_RESOURE_GRID_ZERO_ONE_DIFFUSE, _application->GetRendererDevice());
	_world->GetCubeTextureResource()->Create(CUBE_TEXTURE_RESOURE_GRID_ZERO_ONE_SPECULAR, _application->GetRendererDevice());

	// SMO
	_world->GetStaticMeshResource()->Create(STATIC_MESH_RESOURE_BILL, _application->GetRendererDevice());

	// AMO
	_world->GetAnimationMeshResource()->Create(ANIMATION_MESH_RESOURE_WEAPON_01, _application->GetRendererDevice());
	_world->GetAnimationMeshResource()->Create(ANIMATION_MESH_RESOURE_GRANDPA, _application->GetRendererDevice());
}