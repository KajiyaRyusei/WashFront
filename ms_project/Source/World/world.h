//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// ���E
// 
// Created by Ryusei Kajiya on 20151029
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//*****************************************************************************
// ���d�C���N���[�h�h�~
#pragma once

//*****************************************************************************
// �O���錾
class Unit;
class CollisionGrid;
template<class T>class ResourceBox;

//*****************************************************************************
// �N���X�݌v
class World
{
public:

	World()
	{
		Initialize();
	}

	~World(){ Finalize(); }


	void Initialize();
	void Finalize();
	void Update();
	void Draw();
	void PushUnit(std::list<Unit*>&& unit_list)
	{
		_unit_list = unit_list;
	}

	CollisionGrid* GetCollisionGrid(){ return _collision_grid; }
	ResourceBox<LPDIRECT3DTEXTURE9>* GetTextureResourceBox(){ return _texture_resource_box; }
	ResourceBox<LPDIRECT3DCUBETEXTURE9>* GetCubeTextureResourceBox(){ return _texture_cube_resource_box; }


private:

	std::list<Unit*> _unit_list;
	CollisionGrid* _collision_grid;
	ResourceBox<LPDIRECT3DTEXTURE9>* _texture_resource_box;
	ResourceBox<LPDIRECT3DCUBETEXTURE9>* _texture_cube_resource_box;
};
