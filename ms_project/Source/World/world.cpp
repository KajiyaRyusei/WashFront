//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// ¢ŠE
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

// ƒŠƒ\[ƒX
#include "Resource/texture_resource.h"
#include "Resource/cube_texture_resource.h"
#include "Resource/mesh_resource.h"
#include "Resource/static_mesh_resource.h"
#include "Resource/animation_mesh_resource.h"
#include "Resource/animation_resource.h"

//=============================================================================
// ‰Šú‰»
void World::Initialize()
{
	_collision_grid = new CollisionGrid();
	_texture_resource = new TextureResource;
	_cube_texture_resource = new CubeTextureResource;
	_mesh_resource = new MeshResource;
	_static_mesh_resource = new StaticMeshResource;
	_animation_mesh_resource = new AnimationMeshResource;
	_animation_resource = new AnimationResource;
	_ui = nullptr;
}

//=============================================================================
// I—¹
void World::Finalize()
{
	SafeDelete(_ui);
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
	for( auto it : _2d_unit_list )
	{
		SafeDelete(it);
	}
	SafeDelete(_collision_grid);
	SafeDelete(_water_spray_pool);
}

//=============================================================================
// XV
void World::Update()
{
	for( auto it : _unit_list)
	{
		it->Update();
	}

	for( auto it : _2d_unit_list )
	{
		it->Update();
	}

	for( auto it : _unit_list )
	{
		it->CollisionUpdate();
	}

	if( _ui != NULL )
	{
		_ui->Update();
	}
}

//=============================================================================
// •`‰æ
void World::Draw()
{
	for( auto it : _unit_list )
	{
		it->Draw();
	}
	_water_spray_pool->Animate();
	_collision_grid->DebugDraw();
}

//=============================================================================
// 2D•`‰æ
void World::Draw2D()
{
	for( auto it : _2d_unit_list )
	{
		it->Draw();
	}
}
