//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// シーン：ゲーム
//
// Created by Ryusei Kajiya on 20151130
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
#include "Unit/Game/water_spray_pool.h"
#include "Unit/Game/clouds.h"
#include "Unit/Game/static_building.h"
#include "Unit/ui.h"

// 空間
#include "World/collision_grid.h"

// resource
#include "Resource/animation_mesh_resource.h"
#include "Resource/static_mesh_resource.h"
#include "Resource/cube_texture_resource.h"
#include "Resource/texture_resource.h"
#include "Resource/mesh_resource.h"
#include "Resource/animation_resource.h"

// viewport
#include "Renderer/directx9.h"
#include "Windows/window.h"

// カメラ
#include "Camera/camera_manager.h"
#include "Camera/Camera/camera_game_player.h"

// 汚れ
#include "Data/data_dirt.h"

// ルート
#include "Data/data_route.h"

// sound
#include "Sound/sound.h"

//*****************************************************************************
// 定数
namespace
{
	static const fx32 kWaterMax = 100.f;
}

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
	WaterSprayPool* water_spray_pool = new WaterSprayPool(_application,_world);
	_world->SetWaterSprayPool(water_spray_pool);

	Ui *ui = new Ui(_application, _world);
	_world->SetUi(ui);

	ResourceGeneration();
	MapGeneration();
	_application->GetSound()->Play(BGM_GAME);
}
//=============================================================================
// 終了
void SceneGame::Finalize()
{
	s_scene_data.score_player_1 = _world->GetUi()->GetScore(0);
	s_scene_data.score_player_2 = _world->GetUi()->GetScore(1);

	_application->GetSound()->Stop(BGM_GAME);
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
	D3DVIEWPORT9 viewport,viewport_1p, viewport_2p;
	viewport.Height = _application->GetWindow()->GetSizeWindowHeight();
	viewport.Width = _application->GetWindow()->GetSizeWindowWidth();
	viewport.X = 0;
	viewport.Y = 0;
	viewport.MaxZ = 1.f;
	viewport.MinZ = 0.f;

	viewport_1p = viewport;
	viewport_1p.Height = _application->GetWindow()->GetSizeWindowHeight()/2;

	_application->GetRendererDevice()->GetDevice()->SetViewport(&viewport);

	viewport_2p = viewport_1p;
	viewport_2p.Y = _application->GetWindow()->GetSizeWindowHeight() / 2;

	
	_application->GetCommandBuffer()->Sort();

	// ライトから見た深度
	_application->GetCommandProcessor()->ProccessLightDepth();
	// 影の描画：いる？
	_application->GetCommandProcessor()->ProccessShadow();

	_application->GetCommandBuffer()->Clear();

	//------------------------------------
	// 1p
	D3DXMATRIX projection = _application->GetCameraManager()->GetCamera(CAMERA_TYPE_GAME_PLAYER_1P)->GetMatrixProjection();
	D3DXMATRIX view = _application->GetCameraManager()->GetCamera(CAMERA_TYPE_GAME_PLAYER_1P)->GetMatrixView();
	_application->GetCameraManager()->GetCamera(CAMERA_TYPE_GAME_PLAYER_1P)->GetFrustumCulling().MakeClip(viewport_1p, projection,view);
	_application->GetCameraManager()->SetCurrentCamera(_application->GetCameraManager()->GetCamera(CAMERA_TYPE_GAME_PLAYER_1P));
	_application->GetRendererDevice()->GetDevice()->SetViewport(&viewport_1p);
	_application->GetRendererDevice()->GetDevice()->SetTransform(D3DTS_PROJECTION, &projection);
	_application->GetRendererDevice()->GetDevice()->SetTransform(D3DTS_VIEW, &view);

	_world->Draw();

	_application->GetCommandBuffer()->Sort();
	// 上画面の描画
	_application->GetCommandProcessor()->ProccessDefault();
	_application->GetCommandProcessor()->ProccessField();
	_application->GetCommandProcessor()->ProccessBackGround();
	_application->GetCommandProcessor()->ProccessTranslucent();
	_application->GetCommandProcessor()->ProccessAIM();

	_application->GetCommandBuffer()->Clear();

	// デバッグ描画
	_application->GetDevelopToolManager()->Draw();

	//------------------------------------
	// 2p
	projection = _application->GetCameraManager()->GetCamera(CAMERA_TYPE_GAME_PLAYER_2P)->GetMatrixProjection();
	view = _application->GetCameraManager()->GetCamera(CAMERA_TYPE_GAME_PLAYER_2P)->GetMatrixView();
	_application->GetCameraManager()->GetCamera(CAMERA_TYPE_GAME_PLAYER_2P)->GetFrustumCulling().MakeClip(viewport_2p, projection, view);
	_application->GetCameraManager()->SetCurrentCamera(_application->GetCameraManager()->GetCamera(CAMERA_TYPE_GAME_PLAYER_2P));
	_application->GetRendererDevice()->GetDevice()->SetViewport(&viewport_2p);
	_application->GetRendererDevice()->GetDevice()->SetTransform(D3DTS_PROJECTION, &projection);
	_application->GetRendererDevice()->GetDevice()->SetTransform(D3DTS_VIEW, &view);

	_world->Draw();
	_application->GetCommandBuffer()->Sort();
	// 下画面の描画
	_application->GetCommandProcessor()->ProccessDefault();
	_application->GetCommandProcessor()->ProccessField();
	_application->GetCommandProcessor()->ProccessBackGround();
	_application->GetCommandProcessor()->ProccessTranslucent();
	_application->GetCommandProcessor()->ProccessAIM();

	_application->GetCommandBuffer()->Clear();

	// デバッグ描画
	_application->GetDevelopToolManager()->Draw();

	//------------------------------------
	// 通常 : 2D
	_world->Draw2D();

	_application->GetCommandBuffer()->Sort();

	_application->GetRendererDevice()->GetDevice()->SetViewport(&viewport);

	// 2Dの描画
	_application->GetCommandProcessor()->ProccessDefault();
	_application->GetCommandProcessor()->Proccess2D();

	_application->GetCommandBuffer()->Clear();
}

//=============================================================================
// マップの作成
void SceneGame::MapGeneration()
{
	// 汚れ読み込み
	std::vector<data::Dirt> dirty_list = DirtyRead();

	std::list<Unit*> unit_list;

	std::list<Unit*> unit_list_2d;


	// プレイヤー１
	CameraGamePlayer* camera_1p = static_cast<CameraGamePlayer*>(_application->GetCameraManager()->GetCamera(CAMERA_TYPE_GAME_PLAYER_1P));
	camera_1p->InitializeFrame();
	PlayerUnit* player_1p = new PlayerUnit(_application, _world, camera_1p);
	player_1p->SetControllerType(Command::CONTROLLER_TYPE_1P);
	player_1p->SelectAlbedoTexture(true);

	// プレイヤー２
	CameraGamePlayer* camera_2p = static_cast<CameraGamePlayer*>(_application->GetCameraManager()->GetCamera(CAMERA_TYPE_GAME_PLAYER_2P));
	camera_2p->InitializeFrame();
	PlayerUnit* player_2p = new PlayerUnit(_application, _world, camera_2p);
	player_2p->SetControllerType(Command::CONTROLLER_TYPE_2P);
	player_2p->SelectAlbedoTexture(false);

	_world->GetUi()->SetList(&unit_list_2d);
	_world->GetUi()->MaxWaterMeter(0, kWaterMax);
	_world->GetUi()->MaxWaterMeter(0, kWaterMax);
	
	
	RouteRead();

	unit_list.push_back(player_1p);
	unit_list.push_back(player_2p);

	// 背景
	unit_list.push_back(new BackGroundUnit(_application, _world));

	// 雲
	unit_list.push_back(new CloudsUnit(_application, _world));

	// マップファイル読み込み
	FILE* file;
	file = fopen("Data/Map/pre001.map", "rt");

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
				s32 static_id = 0;
				D3DXVECTOR3 position;
				D3DXVECTOR3 rotation;
				D3DXVECTOR3 scale;

				fscanf(file, "%d %d %f %f %f %f %f %f %f %f %f %d",
					&model_id, &texture_id,
					&position.x, &position.y, &position.z,
					&rotation.x, &rotation.y, &rotation.z,
					&scale.x, &scale.y, &scale.z, &static_id);

				std::string file_name;
				STATIC_MESH_RESOURE_ID id = STATIC_MESH_RESOURE_BILL_000;
				switch( model_id )
				{
				case STATIC_MESH_RESOURE_BILL_000:
					file_name = "Data/StaticModel/new_biru_1.smo";
					id = STATIC_MESH_RESOURE_BILL_000;
					break;
				case STATIC_MESH_RESOURE_BILL_001:
					file_name = "Data/StaticModel/new_biru_2.smo";
					id = STATIC_MESH_RESOURE_BILL_001_LOW;
					break;
				case STATIC_MESH_RESOURE_BILL_002:
					file_name = "Data/StaticModel/new_biru_3.smo";
					id = STATIC_MESH_RESOURE_BILL_002_LOW;
					break;
				case STATIC_MESH_RESOURE_BILL_003:
					file_name = "Data/StaticModel/new_biru_4.smo";
					id = STATIC_MESH_RESOURE_BILL_003;
					break;
				case STATIC_MESH_RESOURE_BILL_HAIKEI:
					file_name = "Data/StaticModel/new_biru_haikei.smo";
					id = STATIC_MESH_RESOURE_BILL_HAIKEI;
					break;
				case 5:
					id = STATIC_MESH_RESOURE_ROAD;
				default:
					break;
				}
				if( static_id)
				{
					BuildingUnit* bill = new BuildingUnit(_application, _world, position, rotation, scale, file_name);
					bill->SettingDirty(dirty_list);
					unit_list.push_back(bill);
				}
				else
				{
					StaticBuildingUnit* bill = new StaticBuildingUnit(_application, _world, position, rotation, scale,id);
					unit_list.push_back(bill);
				}
			}
		}
	}

	fclose(file);

	_world->PushUnit(std::move(unit_list));
	_world->PushUnit2D(std::move(unit_list_2d));
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
	_world->GetTextureResource()->Create(TEXTURE_RESOURE_PLAYER_BAG_TEXTURE, _application->GetRendererDevice());
	_world->GetTextureResource()->Create(TEXTURE_RESOURE_PLAYER_BAG_METALNESS_TEXTURE, _application->GetRendererDevice());
	_world->GetTextureResource()->Create(TEXTURE_RESOURE_PLAYER_METALNESS_TEXTURE, _application->GetRendererDevice());
	_world->GetTextureResource()->Create(TEXTURE_RESOURE_TOON_TEXTURE, _application->GetRendererDevice());
	_world->GetTextureResource()->Create(TEXTURE_RESOURE_BILL_NORMAL_TEXTURE, _application->GetRendererDevice());
	_world->GetTextureResource()->Create(TEXTURE_RESOURE_PLAYER_FACE, _application->GetRendererDevice());

	_world->GetTextureResource()->Create(TEXTURE_RESOURE_PLAYER_2_BAG, _application->GetRendererDevice());
	_world->GetTextureResource()->Create(TEXTURE_RESOURE_PLAYER_2_FACE, _application->GetRendererDevice());
	_world->GetTextureResource()->Create(TEXTURE_RESOURE_PLAYER_2_TEXTURE, _application->GetRendererDevice());

	_world->GetTextureResource()->Create(TEXTURE_RESOURE_BILL_TEXTURE_001, _application->GetRendererDevice());
	_world->GetTextureResource()->Create(TEXTURE_RESOURE_BILL_TEXTURE_002, _application->GetRendererDevice());
	_world->GetTextureResource()->Create(TEXTURE_RESOURE_BILL_TEXTURE_003, _application->GetRendererDevice());
	_world->GetTextureResource()->Create(TEXTURE_RESOURE_BILL_TEXTURE_004, _application->GetRendererDevice());

	_world->GetTextureResource()->Create(TEXTURE_RESOURE_PLAYER_BAG_GREEN, _application->GetRendererDevice());
	_world->GetTextureResource()->Create(TEXTURE_RESOURE_PLAYER_BAG_ORANGE, _application->GetRendererDevice());

	// キューブマップ
	_world->GetCubeTextureResource()->Create(CUBE_TEXTURE_RESOURE_GRID_ZERO_ZERO_DIFFUSE, _application->GetRendererDevice());
	_world->GetCubeTextureResource()->Create(CUBE_TEXTURE_RESOURE_GRID_ZERO_ZERO_SPECULAR, _application->GetRendererDevice());
	_world->GetCubeTextureResource()->Create(CUBE_TEXTURE_RESOURE_GRID_ZERO_ONE_DIFFUSE, _application->GetRendererDevice());
	_world->GetCubeTextureResource()->Create(CUBE_TEXTURE_RESOURE_GRID_ZERO_ONE_SPECULAR, _application->GetRendererDevice());

	// SMO
	_world->GetStaticMeshResource()->Create(STATIC_MESH_RESOURE_BILL_000, _application->GetRendererDevice());
	_world->GetStaticMeshResource()->Create(STATIC_MESH_RESOURE_BILL_001, _application->GetRendererDevice());
	_world->GetStaticMeshResource()->Create(STATIC_MESH_RESOURE_BILL_002, _application->GetRendererDevice());
	_world->GetStaticMeshResource()->Create(STATIC_MESH_RESOURE_BILL_003, _application->GetRendererDevice());
	_world->GetStaticMeshResource()->Create(STATIC_MESH_RESOURE_BILL_HAIKEI, _application->GetRendererDevice());
	_world->GetStaticMeshResource()->Create(STATIC_MESH_RESOURE_BILL_001_LOW, _application->GetRendererDevice());
	_world->GetStaticMeshResource()->Create(STATIC_MESH_RESOURE_BILL_002_LOW, _application->GetRendererDevice());
	_world->GetStaticMeshResource()->Create(STATIC_MESH_RESOURE_ROAD, _application->GetRendererDevice());

	// AMO
	_world->GetAnimationMeshResource()->Create(ANIMATION_MESH_RESOURE_WEAPON_01, _application->GetRendererDevice());
	_world->GetAnimationMeshResource()->Create(ANIMATION_MESH_RESOURE_GRANDPA, _application->GetRendererDevice());

	// アニメーション
	auto mesh_list = _world->GetAnimationMeshResource()->Get(ANIMATION_MESH_RESOURE_GRANDPA);
	_world->GetAnimationResource()->Create(ANIMATION_RESOURE_STANCE, mesh_list.size());
	_world->GetAnimationResource()->Create(ANIMATION_RESOURE_SHOT, mesh_list.size());
}

//=============================================================================
// ルートの読み込み
void SceneGame::RouteRead()
{
	FILE* inputFile;
	inputFile = fopen("Data/Map/pre001.rt", "rt");

	int num = 0;
	fx32 length = 0.f;
	

	fseek(inputFile, 0, SEEK_SET);

	for( int i = 0; i < 4; i++ )
	{// 1は1p,2は2p、3は3p、4は4p
		
		for( ;; )
		{// 生成したオブジェクト数取得
			char str[4096] = {};
			if( EOF == fscanf(inputFile, "%s", str) )
			{
				break;
			}

			if( !strcmp(str, "#NUM") )
			{
				fscanf(inputFile, "%d", &num);
				break;
			}
		}

		std::vector<data::Route> route;
		route.reserve(num);

		for( ;; )
		{// 生成したオブジェクト数取得
			char str[4096] = {};
			if( EOF == fscanf(inputFile, "%s", str) )
			{
				break;
			}

			if( !strcmp(str, "#LEN") )
			{
				fscanf(inputFile, "%f", &length);
				
				break;
			}
		}

		
		for( ;; )
		{// インポートファイルパス読み込み
			char str[4096] = {};
			if( EOF == fscanf(inputFile, "%s", str) )
			{
				break;
			}

			if( !strcmp(str, "#POINT") )
			{
				for( int j = 0; j < num; j++ )
				{
					data::Route temp_route;
					u32 ID;

					
					fscanf(inputFile, "%d %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %d",
						&ID,
						&temp_route.point.x, &temp_route.point.y, &temp_route.point.z,
						&temp_route.eye_rotation.x, &temp_route.eye_rotation.y, &temp_route.eye_rotation.z,
						&temp_route.eye_quaternion.x, &temp_route.eye_quaternion.y, &temp_route.eye_quaternion.z, &temp_route.eye_quaternion.w,
						&temp_route.player_rotation.x, &temp_route.player_rotation.y, &temp_route.player_rotation.z,
						&temp_route.player_quaternion.x, &temp_route.player_quaternion.y, &temp_route.player_quaternion.z, &temp_route.player_quaternion.w,
						&temp_route.velocity, &temp_route.state);

					char str[4096] = {};
					sprintf(str, "%d", j + 1);

					route.push_back(temp_route);
				}
				break;
			}
		}

		if( i == 0)
		{
			D3DXVECTOR3 point = route[0].point;
			_world->GetUi()->SetMap(length, point);
			static_cast<CameraGamePlayer*>(_application->GetCameraManager()->GetCamera(CAMERA_TYPE_GAME_PLAYER_1P))->SetRoute(std::move(route));
		}
		else if( i == 1 )
		{
			static_cast<CameraGamePlayer*>(_application->GetCameraManager()->GetCamera(CAMERA_TYPE_GAME_PLAYER_2P))->SetRoute(std::move(route));
		}
	}

	fclose(inputFile);
}

//=============================================================================
// 汚れの読み込み
std::vector<data::Dirt> SceneGame::DirtyRead()
{
	int num = 0;

	FILE* inputFile;
	inputFile = fopen("Data/Map/pre001.drt", "rt");

	fseek(inputFile, 0, SEEK_SET);

	std::vector<data::Dirt> dirty_list;

	// 生成したオブジェクト数取得
	for( ;; )
	{
		char str[4096] = {};
		if( EOF == fscanf(inputFile, "%s", str) )
		{
			break;
		}

		if( !strcmp(str, "#NUM") )
		{
			fscanf(inputFile, "%d", &num);
		}
	}

	dirty_list.reserve(num);

	fseek(inputFile, 0, SEEK_SET);

	// インポートファイルパス読み込み
	for( ;; )
	{
		char str[4096] = {};

		if( EOF == fscanf(inputFile, "%s", str) )
		{
			break;
		}

		if( !strcmp(str, "#DIRT") )
		{
			for( int i = 0; i < num; i++ )
			{
				data::Dirt dirt;
				int ID;

				fscanf(inputFile, "%d %f %f %f %f %d", &ID, &dirt.point.x, &dirt.point.y, &dirt.point.z, &dirt.radius, &dirt.level);

				dirty_list.push_back(dirt);

				char str[4096] = {};
				sprintf(str, "%d", i + 1);
			}
		}
	}

	fclose(inputFile);

	return dirty_list;
}

