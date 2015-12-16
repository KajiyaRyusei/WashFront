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
#include "Unit/Title/title_player.h"
#include "Unit/Game/back_ground.h"
#include "Unit/Game/building.h"
#include "World/collision_grid.h"
#include "Unit/Game/water_spray_pool.h"
#include "Unit/Game/clouds.h"
#include "Unit/Game/static_building.h"

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
#include "Camera/Camera/camera_title.h"

// 汚れ
#include "Data/data_dirt.h"


// ルート
#include "Data/data_route.h"

//=============================================================================
// const
const int windowSizeID = 0;

const D3DXVECTOR3 WindowPos[2][3] =
{
	// 960 : 540
	{
		// logo_bg
		D3DXVECTOR3(480.0f, 150.0f, 0.0),

		// logo
		D3DXVECTOR3(480.0f, 150.0f, 0.0),

		// text
		D3DXVECTOR3(480.0f, 500.0f, 0.0)
	},

	// 1280 : 720
	{
		// logo_bg
		D3DXVECTOR3(640.0f, 200.0f, 0.0),

		// logo
		D3DXVECTOR3(640.0f, 200.0f, 0.0),

		// text
		D3DXVECTOR3(640.0f, 650.0f, 0.0)
	}
};

const D3DXVECTOR3 WindowScl[2][3] =
{
	// 960 : 540
	{
		// logo_bg
		D3DXVECTOR3(500.0f, 250.0f, 0.0f),

		// logo
		D3DXVECTOR3(400.0f, 200.0f, 0.0f),

		// text
		D3DXVECTOR3(500.0f, 50.0f, 0.0f)
	},

	// 1280 : 720
	{
		// logo_bg
		D3DXVECTOR3(600.0f, 350.0f, 0.0f),

		// logo
		D3DXVECTOR3(500.0f, 300.0f, 0.0f),

		// text
		D3DXVECTOR3(600.0f, 70.0f, 0.0f)
	}
};

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
	TextUnit*		pText = new TextUnit(_application, _world);
	Logo_BGUnit*	pLogoBg = new Logo_BGUnit(_application, _world);
	LogoUnit*		pLogo = new LogoUnit(_application, _world);

	pLogoBg->SetPosition(WindowPos[windowSizeID][0]);
	pLogoBg->SetScaling(WindowScl[windowSizeID][0]);
	pLogo->SetPosition(WindowPos[windowSizeID][1]);
	pLogo->SetScaling(WindowScl[windowSizeID][1]);
	pText->SetPosition(WindowPos[windowSizeID][2]);
	pText->SetScaling(WindowScl[windowSizeID][2]);

	unit_list.push_back(pText);
	unit_list.push_back(pLogoBg);
	unit_list.push_back(pLogo);

	// プレイヤー
	TitlePlayerUnit* player = new TitlePlayerUnit(_application, _world);
	unit_list.push_back(player);

	// 背景
	unit_list.push_back(new BackGroundUnit(_application, _world));

	// 雲
	unit_list.push_back(new CloudsUnit(_application, _world));

	// マップファイル読み込み
	FILE* file;
	file = fopen("Data/Map/pre.map", "rt");

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
					id = STATIC_MESH_RESOURE_BILL_001;
					break;
				case STATIC_MESH_RESOURE_BILL_002:
					file_name = "Data/StaticModel/new_biru_3.smo";
					id = STATIC_MESH_RESOURE_BILL_002;
					break;
				case STATIC_MESH_RESOURE_BILL_003:
					file_name = "Data/StaticModel/new_biru_4.smo";
					id = STATIC_MESH_RESOURE_BILL_003;
					break;
				case STATIC_MESH_RESOURE_BILL_HAIKEI:
					file_name = "Data/StaticModel/new_biru_haikei.smo";
					id = STATIC_MESH_RESOURE_BILL_HAIKEI;
					break;
				default:
					break;
				}

				StaticBuildingUnit* bill = new StaticBuildingUnit(_application, _world, position, rotation, scale, id);
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
	_world->GetTextureResource()->Create(TEXTURE_RESOURE_TOON_TEXTURE, _application->GetRendererDevice());
	_world->GetTextureResource()->Create(TEXTURE_RESOURE_BILL_NORMAL_TEXTURE, _application->GetRendererDevice());
	_world->GetTextureResource()->Create(TEXTURE_RESOURE_PLAYER_FACE, _application->GetRendererDevice());

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

	// AMO
	_world->GetAnimationMeshResource()->Create(ANIMATION_MESH_RESOURE_WEAPON_01, _application->GetRendererDevice());
	_world->GetAnimationMeshResource()->Create(ANIMATION_MESH_RESOURE_GRANDPA, _application->GetRendererDevice());

	// アニメーション
	auto mesh_list = _world->GetAnimationMeshResource()->Get(ANIMATION_MESH_RESOURE_GRANDPA);
	_world->GetAnimationResource()->Create(ANIMATION_RESOURE_STANCE, mesh_list.size());
}