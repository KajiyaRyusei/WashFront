//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// �V�[���F�Q�[��
//
// Created by Ryusei Kajiya on 20151123
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//*****************************************************************************
// �C���N���[�h
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


// ���
#include "World/collision_grid.h"

// resource
#include "Resource/animation_mesh_resource.h"
#include "Resource/static_mesh_resource.h"
#include "Resource/cube_texture_resource.h"
#include "Resource/texture_resource.h"
#include "Resource/mesh_resource.h"

//=============================================================================
// �R���X�g���N�^
SceneGame::SceneGame(Application *application) :
	Scene{ application }
{
	Initialize();
}
//=============================================================================
// ������
void SceneGame::Initialize()
{
	_world = new World();
	ResourceGeneration();
	MapGeneration();
}
//=============================================================================
// �I��
void SceneGame::Finalize()
{
	SafeDelete(_world);
	Unit::ResetID();
}
//=============================================================================
// �X�V
void SceneGame::Update()
{
	Reference::GetInstance().GetDevelopToolManager()->GetDebugPrint().Print("�Q�[���V�[���ł���\n");

	if( _application->GetInputManager()->CheckTrigger(INPUT_EVENT_RETURN) )
	{
		_application->GetSceneManager()->SetNextScene(new SpawnerForScene<SceneResult>);
	}

	_world->Update();
}
//=============================================================================
// �`��
void SceneGame::Draw()
{
	_world->Draw();
}


//=============================================================================
// �}�b�v�̍쐬
void SceneGame::MapGeneration()
{
	std::list<Unit*> unit_list;
	unit_list.push_back(new PlayerUnit(_application, _world));
	unit_list.push_back(new BackGroundUnit(_application, _world));

	FILE *input_file = nullptr;
	input_file = fopen("Data/Map/beta.map", "rt");
	ASSERT(input_file != nullptr,"�}�b�v�t�@�C���̓ǂݍ��݂Ɏ��s");

	u32 number = 0;
	fseek(input_file,0,SEEK_SET);

	while(true)
	{// ���������I�u�W�F�N�g���擾
		char string[4096] = {};
		if( EOF == fscanf(input_file, "%s",string) )
		{
			break;
		}

		if( !strcmp(string, "#OBJNUM"))
		{
			fscanf(input_file,"%d",&number);
		}
	}

	fseek(input_file, 0, SEEK_SET);

	while( true )
	{// �C���|�[�g�t�@�C���p�X�ǂݍ���
		char str[4096] = {};
		if( EOF == fscanf(input_file, "%s", str) )
			break;

		if( !strcmp(str, "#OBJ") )
		{
			for( u32 i = 0; i < number; i++ )
			{
				u32 id;
				D3DXVECTOR3 position;
				D3DXVECTOR3 rotation;
				D3DXVECTOR3 scale;

				fscanf(
					input_file,
					"%d %f %f %f %f %f %f %f %f %f",
					&id,
					&position.x, &position.y, &position.z,
					&rotation.x, &rotation.y, &rotation.z,
					&scale.x, &scale.y, &scale.z);

				//BuildingUnit* bill = new BuildingUnit(_application, _world, position, rotation, scale);
				//unit_list.push_back(bill);
			}
		}
	}

	fclose(input_file);

	_world->PushUnit(std::move(unit_list));
}

//=============================================================================
// ���\�[�X�̍쐬
void SceneGame::ResourceGeneration()
{
	// ���b�V��
	_world->GetMeshResource()->Create(MESH_RESOURE_BOX, _application->GetRendererDevice());
	_world->GetMeshResource()->Create(MESH_RESOURE_SPRITE, _application->GetRendererDevice());
	_world->GetMeshResource()->Create(MESH_RESOURE_MESH_FIELD, _application->GetRendererDevice());
	_world->GetMeshResource()->Create(MESH_RESOURE_WATER_CYLINDER, _application->GetRendererDevice());
	_world->GetMeshResource()->Create(MESH_RESOURE_WATER_CYLINDER_BACK, _application->GetRendererDevice());

	// �e�N�X�`��
	_world->GetTextureResource()->Create(TEXTURE_RESOURE_BILL_TEXTURE, _application->GetRendererDevice());
	_world->GetTextureResource()->Create(TEXTURE_RESOURE_AIM_TEXTURE, _application->GetRendererDevice());
	_world->GetTextureResource()->Create(TEXTURE_RESOURE_DIRT_NORMAL_TEXTURE, _application->GetRendererDevice());
	_world->GetTextureResource()->Create(TEXTURE_RESOURE_WATER_BALL_TEXTURE, _application->GetRendererDevice());
	_world->GetTextureResource()->Create(TEXTURE_RESOURE_WATER_NORMAL_TEXTURE, _application->GetRendererDevice());
	_world->GetTextureResource()->Create(TEXTURE_RESOURE_PLAYER_TEXTURE, _application->GetRendererDevice());
	_world->GetTextureResource()->Create(TEXTURE_RESOURE_BILL_METALNESS_TEXTURE, _application->GetRendererDevice());
	_world->GetTextureResource()->Create(TEXTURE_RESOURE_DIRTY_TEXTURE, _application->GetRendererDevice());

	// �L���[�u�}�b�v
	_world->GetCubeTextureResource()->Create(CUBE_TEXTURE_RESOURE_GRID_ZERO_ZERO_DIFFUSE, _application->GetRendererDevice());
	_world->GetCubeTextureResource()->Create(CUBE_TEXTURE_RESOURE_GRID_ZERO_ZERO_SPECULAR, _application->GetRendererDevice());

	// SMO
	_world->GetStaticMeshResource()->Create(STATIC_MESH_RESOURE_BILL, _application->GetRendererDevice());

	// AMO
	_world->GetAnimationMeshResource()->Create(ANIMATION_MESH_RESOURE_WEAPON_01, _application->GetRendererDevice());
	_world->GetAnimationMeshResource()->Create(ANIMATION_MESH_RESOURE_GRANDPA, _application->GetRendererDevice());
}