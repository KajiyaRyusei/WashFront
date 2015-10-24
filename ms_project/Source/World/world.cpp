//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// ¢ŠE
// 
// Created by Ryusei Kajiya on 20151009
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//*****************************************************************************
// include
#include "world.h"
#include "World/space_grid.h"
#include "Unit/unit.h"

#include "DevelopTool/develop_tool_manager.h"

//=============================================================================
// ‰Šú‰»
void World::Initialize()
{

}

//=============================================================================
// I—¹
void World::Finalize()
{
	for( auto it : _unit_list )
	{
		SafeDelete(it);
	}
	SafeDelete(_grid);
}

//=============================================================================
// XV
void World::Update()
{
	for( auto it : _unit_list)
	{
		it->Update();
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

#ifndef RELEASE

	DebugLineBox& box = Reference::GetInstance().GetDevelopToolManager()->GetDebugLineBox();
	fx32 cell_size = static_cast<fx32>(_grid->S_GetSizeCell());
	s32 cell_max = _grid->S_GetMaxCell();

	for( s32 x = 0; x < cell_max; ++x )
	{
		for( s32 y = 0; y < cell_max; ++y )
		{
			for( s32 z = 0; z < cell_max; ++z )
			{
				box.RegisteBox(
					D3DXVECTOR3(cell_size / 2.f, cell_size / 2.f, cell_size / 2.f),
					D3DXVECTOR3(cell_size*x, cell_size*y, cell_size*z),
					D3DXVECTOR3(0.f,0.f,0.f));
			}
		}
	}

#endif
}