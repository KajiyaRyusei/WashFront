//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// 背景用ビル
// 
// Created by Ryusei Kajiya on 201511214
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//*****************************************************************************
// 多重インクルード防止
#pragma once

//*****************************************************************************
// include
#include "Unit/unit.h"
#include "Data/data_world.h"
#include "Resource/static_mesh_resource.h"
//*****************************************************************************
// 前方宣言
class ShaderStaticToonBuilding;
class MeshBuffer;

//*****************************************************************************
// クラス設計
class StaticBuildingUnit : public Unit
{
public:

	StaticBuildingUnit(
		Application* application,
		World* world,
		const D3DXVECTOR3& position,
		const D3DXVECTOR3& rotaiton,
		const D3DXVECTOR3& scale,
		STATIC_MESH_RESOURE_ID id) : Unit(application, world)
	{
		Initialize(position, rotaiton, scale, id);
	}
	virtual ~StaticBuildingUnit(){ Finalize(); }

	virtual void Initialize() override{};
	void Initialize(
		const D3DXVECTOR3& position,
		const D3DXVECTOR3& rotaiton,
		const D3DXVECTOR3& scale,
		STATIC_MESH_RESOURE_ID id);
	virtual void Finalize() override;
	virtual void Update() override;
	virtual void Draw() override;
	virtual void CollisionUpdate() override{}
	virtual void CollisionMeshPoint(u32 point_index)override{ UNREFERENCED_PARAMETER(point_index); }

private:

	// シェーダー
	ShaderStaticToonBuilding* _shader;
	u32 _shader_size;
	// シェーダパラメーターの設定
	void SettingShaderParameter();
	data::World _world;
	D3DXMATRIX _matrix_world_view_projection;
	// メッシュ
	std::vector<MeshBuffer*> _mesh_list;
};