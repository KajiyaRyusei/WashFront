//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// ¢ŠE
// 
// Created by Ryusei Kajiya on 20151029
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//*****************************************************************************
// include
#include "World/world.h"
#include "World/collision_grid.h"
#include "Unit/unit.h"

#include "DevelopTool/develop_tool_manager.h"

//=============================================================================
// ‰Šú‰»
void World::Initialize()
{
	_collision_grid = new CollisionGrid();
}

//=============================================================================
// I—¹
void World::Finalize()
{
	for( auto it : _unit_list )
	{
		SafeDelete(it);
	}
	SafeDelete(_collision_grid);
}

//=============================================================================
// XV
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
}

//=============================================================================
// •`‰æ
void World::Draw()
{
	for( auto it : _unit_list )
	{
		it->Draw();
	}
	_collision_grid->DebugDraw();
}