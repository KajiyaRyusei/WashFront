//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// ユニット
// 
// Created by Ryusei Kajiya on 20151009
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//*****************************************************************************
// include
#include "unit.h"
#include "World/space_grid.h"

u32 Unit::s_unit_id = 0;

//=============================================================================
// コンストラクタ
Unit::Unit(Application* application, SpaceGrid* grid) :
	_application(application),
	_space_grid(grid),
	_world_position(100.f,100.f,0.f),
	_previous_world_position(_world_position),
	_next(nullptr),
	_previous(nullptr),
	_id(++s_unit_id)
{
	//_space_grid->AddUnit(this, _world_position);
}
