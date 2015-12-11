//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// 後ろ水
// 
// Created by Ryusei Kajiya on 20151123
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
class ShaderWaterBack;

//*****************************************************************************
// クラス設計
class WaterBackUnit : public Unit
{
public:

	WaterBackUnit(Application* application, World* world) : Unit(application, world)
	{
		Initialize();
	}
	virtual ~WaterBackUnit(){ Finalize(); }

	virtual void Initialize() override;
	virtual void Finalize() override;
	virtual void Update() override;
	virtual void Draw() override;
	virtual void CollisionUpdate() override;

	// 座標の設定
	void SetPosition(const D3DXVECTOR3& position);

private:

	// シェーダー
	ShaderWaterBack* _shader;
	// シェーダパラメーターの設定
	void SettingShaderParameter();
	data::World _world;
	D3DXMATRIX _matrix_world_view_projection;
	D3DXMATRIX _animation_matrix;
	D3DXMATRIX _player_rotation_matrix;
};