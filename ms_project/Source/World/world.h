//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// ���E
// 
// Created by Ryusei Kajiya on 20151009
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//*****************************************************************************
// ���d�C���N���[�h�h�~
#pragma once

//*****************************************************************************
// �O���錾
class Unit;
class SpaceGrid;

//*****************************************************************************
// �N���X�݌v
class World
{
public:

	World(std::list<Unit*>&& unit_list, SpaceGrid* grid) :
		_unit_list(unit_list),
		_grid(grid)
	{
		Initialize();
	}

	~World(){ Finalize(); }


	void Initialize();
	void Finalize();
	void Update();
	void Draw();

private:

	std::list<Unit*> _unit_list;
	SpaceGrid* _grid;
};
