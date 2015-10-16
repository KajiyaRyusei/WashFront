//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// ���j�b�g
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
// �R���X�g���N�^
Unit::Unit(Application* application, SpaceGrid* grid) :
	_application(application),
	_world_position(100.f,100.f,0.f),
	_next(nullptr),
	_previous(nullptr),
	_id(++s_unit_id)
{
	grid->AddUnit(this);
}
