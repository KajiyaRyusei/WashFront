//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// ビル
// 
// Created by Ryusei Kajiya on 20151102
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//*****************************************************************************
// 多重インクルード防止
#pragma once

//*****************************************************************************
// include
#include "Unit/unit.h"
#include "Data/data_world.h"

//*****************************************************************************
// 前方宣言
class ShaderPBLStatic;
class MeshBuffer;

//*****************************************************************************
// クラス設計
class BuildingUnit : public Unit
{
public:

	BuildingUnit(
		Application* application,
		World* world,
		const D3DXVECTOR3& position,
		const D3DXVECTOR3& rotaiton,
		const D3DXVECTOR3& scale) : Unit(application, world)
	{
		Initialize(position,rotaiton,scale);
	}
	virtual ~BuildingUnit(){ Finalize(); }

	virtual void Initialize() override{};
	void Initialize(
		const D3DXVECTOR3& position,
		const D3DXVECTOR3& rotaiton,
		const D3DXVECTOR3& scale);
	virtual void Finalize() override;
	virtual void Update() override;
	virtual void Draw() override;
	virtual void CollisionUpdate() override;
	virtual void CollisionMeshPoint(u32 point_index)override;

private:

	// シェーダー
	ShaderPBLStatic* _shader;
	u32 _shader_size;
	// シェーダパラメーターの設定
	void SettingShaderParameter();
	data::World _world;
	D3DXMATRIX _matrix_world_view_projection;
	// メッシュ
	std::vector<MeshBuffer*> _mesh_list;
	// 衝突してる点かどうか
	std::list<u32> _clean_index_list;
	void CleanUp();
};