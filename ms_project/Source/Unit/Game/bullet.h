//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// バレット
// 
// Created by Ryusei Kajiya on 20151115
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
// クラス設計
class BulletUnit : public Unit
{
public:

	BulletUnit(Application* application, World* world) : Unit(application, world)
	{
		Initialize();
	}

	virtual ~BulletUnit(){ Finalize(); }

	virtual void Initialize() override;
	virtual void Finalize() override;
	virtual void Update() override;
	virtual void Draw() override;
	virtual void CollisionUpdate() override;
	virtual void CollisionSphere() override;
	virtual void CollisionBox()override;

	// 発射
	void Fire(
		const D3DXVECTOR3& start,
		const D3DXVECTOR3& end,
		const fx32 velocity);

private:

	data::World _world;

	D3DXVECTOR3 _start_point;
	D3DXVECTOR3 _end_point;
	D3DXVECTOR3 _control_point;
	fx32 _frame_velocity;
	fx32 _frame;

	// 移動
	void Move();
};