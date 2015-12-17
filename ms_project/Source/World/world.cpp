//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// 世界
// 
// Created by Ryusei Kajiya on 20151030
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//*****************************************************************************
// include
#include "World/world.h"
#include "World/collision_grid.h"
#include "Unit/unit.h"
#include "Renderer/directx9.h"

#include "Unit/Game/water_spray_pool.h"
#include "Unit/ui.h"

// リソース
#include "Resource/texture_resource.h"
#include "Resource/cube_texture_resource.h"
#include "Resource/mesh_resource.h"
#include "Resource/static_mesh_resource.h"
#include "Resource/animation_mesh_resource.h"
#include "Resource/animation_resource.h"

//=============================================================================
// 初期化
void World::Initialize()
{
	_collision_grid = new CollisionGrid();
	_texture_resource = new TextureResource;
	_cube_texture_resource = new CubeTextureResource;
	_mesh_resource = new MeshResource;
	_static_mesh_resource = new StaticMeshResource;
	_animation_mesh_resource = new AnimationMeshResource;
	_animation_resource = new AnimationResource;
	_ui = NULL;
}

//=============================================================================
// 終了
void World::Finalize()
{
	SafeDelete(_animation_resource);
	SafeDelete(_animation_mesh_resource);
	SafeDelete(_static_mesh_resource);
	SafeDelete(_mesh_resource);
	SafeDelete(_cube_texture_resource);
	SafeDelete(_texture_resource);

	for( auto it : _unit_list )
	{
		SafeDelete(it);
	}
	SafeDelete(_collision_grid);
	SafeDelete(_water_spray_pool);
	SafeDelete(_ui);
}

//=============================================================================
// 更新
void World::Update()
{
	for( auto it : _unit_list)
	{
		it->Update();
	}

	for( auto it : _unit_list )
	{
		it->CollisionUpdate();
	}

	if (_ui != NULL)
	{
		_ui->Update();
	}
}

//=============================================================================
// 描画
void World::Draw()
{
	for( auto it : _unit_list )
	{
		it->Draw();
	}
	_water_spray_pool->Animate();
	_collision_grid->DebugDraw();

	if (_ui != NULL)
	{
		_ui->Draw();
	}
}
