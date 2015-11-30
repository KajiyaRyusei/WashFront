//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// AIMの線
// 
// Created by Ryusei Kajiya on 20151029
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//*****************************************************************************
// 多重インクルード防止
#pragma once

//*****************************************************************************
// include
#include "Unit/unit.h"

//*****************************************************************************
// クラス設計
class AimLineUnit : public Unit
{
public:
	AimLineUnit(Application* application, World* world) : Unit(application, world)
	{
		Initialize();
	}
	virtual ~AimLineUnit(){ Finalize(); }

	virtual void Initialize() override;
	virtual void Finalize() override;
	virtual void Update() override;
	virtual void Draw() override;
	virtual void CollisionUpdate() override;
	virtual void CollisionLine(const D3DXVECTOR3& impact_point) override;

	// ラインの始点設定
	void SetStartPosition(const D3DXVECTOR3& position)
	{
		_position.current = position;
		_line->start_point = position;
	}
	// ラインの終点設定
	void SetEndPosition(const D3DXVECTOR3& position)
	{
		_line->end_point = position;
	}

	// ラインの始点を取得
	D3DXVECTOR3& GetStartPosition()
	{
		return _line->start_point;
	}

	// ラインの終点を取得
	D3DXVECTOR3& GetEndPosition()
	{
		return _line->end_point;
	}

	
};
