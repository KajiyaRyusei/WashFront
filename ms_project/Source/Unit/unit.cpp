//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// ユニット
// 
// Created by Ryusei Kajiya on 20151029
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//*****************************************************************************
// include
#include "unit.h"

u32 Unit::s_unit_id = 0;

//=============================================================================
// コンストラクタ
Unit::Unit(Application* application, World* world) :
	_application(application),
	_game_world(world),
	_next(nullptr),
	_previous(nullptr),
	_id(++s_unit_id),
	_shpere(nullptr),
	_box(nullptr),
	_line(nullptr),
	_volume_mesh_point(nullptr)
{

}

//=============================================================================
// デストラクタ
Unit::~Unit()
{
	SafeDelete(_shpere);
	SafeDelete(_box);
	SafeDelete(_line);
	SafeDelete(_volume_mesh_point);
}