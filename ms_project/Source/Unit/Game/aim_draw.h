//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// 描画用AIM
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
class ShaderAim;

//*****************************************************************************
// クラス設計
class AimDrawUnit : public Unit
{
public:
	AimDrawUnit(Application* application, World* world) : Unit(application, world)
	{
		Initialize();
	}
	virtual ~AimDrawUnit(){ Finalize(); }

	virtual void Initialize() override;
	virtual void Finalize() override;
	virtual void Update() override;
	virtual void Draw() override;
	virtual void CollisionUpdate() override{};

	void SetEndPosition(const D3DXVECTOR3& position)
	{
		_world.position = position;
	}

	void SetHit(const bool is_hit)
	{
		_is_hit = is_hit;
	}

private:

	// シェーダー
	ShaderAim* _shader;

	// ワールド
	data::World _world;
	D3DXMATRIX _matrix_world_view_projection;

	bool _is_hit;

	// 自分の位置を算出
	void CalculatePosition();
};