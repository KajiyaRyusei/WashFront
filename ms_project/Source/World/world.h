//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// 世界
// 
// Created by Ryusei Kajiya on 20151009
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//*****************************************************************************
// 多重インクルード防止
#pragma once

//*****************************************************************************
// 前方宣言
class Unit;
class SpaceGrid;

//*****************************************************************************
// クラス設計
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
