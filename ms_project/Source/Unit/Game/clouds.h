//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// 雲
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
#include "Data/data_velocity.h"

//*****************************************************************************
// 前方宣言
class ShaderStaticToonCloud;
class MeshBuffer;

//*****************************************************************************
// クラス設計
class CloudsUnit : public Unit
{
public:

	CloudsUnit(
		Application* application,
		World* world) : Unit(application, world)
	{
		Initialize();
	}
	virtual ~CloudsUnit(){ Finalize(); }

	virtual void Initialize() override;
	virtual void Finalize() override;
	virtual void Update() override;
	virtual void Draw() override;
	virtual void CollisionUpdate() override{}

	// 雲のポジション設定
	void CloudSettingPosition();

private:

	static const u32 kCloudMax = 15;

	// シェーダー
	ShaderStaticToonCloud* _shader;
	u32 _shader_size;
	// シェーダパラメーターの設定
	void SettingShaderParameter();
	data::World _world[kCloudMax];
	D3DXMATRIX _work_world_matrix[kCloudMax];
	data::Velocity _velocity;
	D3DXMATRIX _matrix_view_projection;
	// メッシュ
	std::vector<MeshBuffer*> _mesh_list;

	// 雲選択
	void CloudSelect();

	// 座標の移動
	void MovePosition();
	// 座標の限界
	void LimitedPosition();
};