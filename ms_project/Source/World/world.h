//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// ���E
// 
// Created by Ryusei Kajiya on 20151030
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//*****************************************************************************
// ���d�C���N���[�h�h�~
#pragma once

//*****************************************************************************
// �O���錾
class Unit;
class CollisionGrid;
class RendererDevice;

class TextureResource;
class CubeTextureResource;
class MeshResource;
class StaticMeshResource;
class AnimationMeshResource;


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
	TextureResource* GetTextureResource(){ return _texture_resource; }
	CubeTextureResource* GetCubeTextureResource(){ return _cube_texture_resource; }
	MeshResource* GetMeshResource(){ return _mesh_resource; }
	StaticMeshResource* GetStaticMeshResource(){ return _static_mesh_resource; }
	AnimationMeshResource* GetAnimationMeshResource(){ return _animation_mesh_resource; }


private:

	std::list<Unit*> _unit_list;
	CollisionGrid* _collision_grid;
	TextureResource* _texture_resource;
	CubeTextureResource* _cube_texture_resource;
	MeshResource* _mesh_resource;
	StaticMeshResource* _static_mesh_resource;
	AnimationMeshResource* _animation_mesh_resource;
};
