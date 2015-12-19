//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// 世界
// 
// Created by Ryusei Kajiya on 20151030
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//*****************************************************************************
// 多重インクルード防止
#pragma once

//*****************************************************************************
// 前方宣言
class Unit;
class CollisionGrid;
class RendererDevice;

class TextureResource;
class CubeTextureResource;
class MeshResource;
class StaticMeshResource;
class AnimationMeshResource;
class AnimationResource;

class WaterSprayPool;
class Ui;

//*****************************************************************************
// クラス設計
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
	void Draw2D();
	void PushUnit(std::list<Unit*>&& unit_list)
	{
		_unit_list = unit_list;
	}
	void PushUnit2D(std::list<Unit*>&& unit_list)
	{
		_2d_unit_list = unit_list;
	}

	CollisionGrid* GetCollisionGrid(){ return _collision_grid; }
	TextureResource* GetTextureResource(){ return _texture_resource; }
	CubeTextureResource* GetCubeTextureResource(){ return _cube_texture_resource; }
	MeshResource* GetMeshResource(){ return _mesh_resource; }
	StaticMeshResource* GetStaticMeshResource(){ return _static_mesh_resource; }
	AnimationMeshResource* GetAnimationMeshResource(){ return _animation_mesh_resource; }
	AnimationResource* GetAnimationResource(){ return _animation_resource; }

	void SetWaterSprayPool(WaterSprayPool* water_spray_pool){ _water_spray_pool = water_spray_pool; }
	WaterSprayPool* GetWaterSprayPool(){ return _water_spray_pool; }

	void SetUi(Ui *ui){ _ui = ui; }
	Ui *GetUi(void){ return _ui; }

private:

	std::list<Unit*> _unit_list;
	std::list<Unit*> _2d_unit_list;
	CollisionGrid* _collision_grid;
	TextureResource* _texture_resource;
	CubeTextureResource* _cube_texture_resource;
	MeshResource* _mesh_resource;
	StaticMeshResource* _static_mesh_resource;
	AnimationMeshResource* _animation_mesh_resource;
	AnimationResource* _animation_resource;
	WaterSprayPool* _water_spray_pool;
	Ui* _ui;
};
