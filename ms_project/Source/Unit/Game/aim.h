//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// AIM
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
// 前方宣言
class AimDrawUnit;
class AimLineUnit;

//*****************************************************************************
// クラス設計
class AimUnit : public Unit
{
public:

	AimUnit(Application* application, World* world) : Unit(application, world)
	{
		Initialize();
	}
	virtual ~AimUnit(){ Finalize(); }

	virtual void Initialize() override;
	virtual void Finalize() override;
	virtual void Update() override;
	virtual void Draw() override;
	virtual void CollisionUpdate() override;

	// ラインの始点設定
	void SetStartPosition(const D3DXVECTOR3& position);

	// ラインの終点設定
	void SetEndPosition(const D3DXVECTOR3& position);

	// ラインの始点を取得
	D3DXVECTOR3& GetStartPosition();

	// ラインの終点を取得
	D3DXVECTOR3& GetEndPosition();

private:

	// 描画用AIM
	AimDrawUnit* _aim_draw;
	AimLineUnit* _aim_line;
};