//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// 武器
// 
// Created by Ryusei Kajiya on 20151118
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
class ShaderPBLAnimation;
class BulletUnit;
class WaterBulletUnit;

//*****************************************************************************
// クラス設計
class WeaponUnit : public Unit
{
public:

	WeaponUnit(Application* application, World* world) : Unit(application, world)
	{
		Initialize();
	}
	virtual ~WeaponUnit(){ Finalize(); }

	virtual void Initialize() override;
	virtual void Finalize() override;
	virtual void Update() override;
	virtual void Draw() override;
	virtual void CollisionUpdate() override;

	// 座標の設定
	void SetPosition(
		const D3DXVECTOR3& position,
		const D3DXMATRIX& animation);

	// 発射
	void Fire(
		const D3DXVECTOR3& start,
		const D3DXVECTOR3& end);

private:

	ShaderPBLAnimation* _shader;
	u32 _sahder_size;
	data::World _world;
	D3DXMATRIX _matrix_world_view_projection;
	D3DXMATRIX _animation_matrix;
	// シェーダパラメーターの設定
	void SettingShaderParameter();

	// 弾
	BulletUnit* _bullet;
	WaterBulletUnit* _water_bullet;

};