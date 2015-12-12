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
class PlayerUnit;

//*****************************************************************************
// クラス設計
class AimUnit : public Unit
{
public:

	AimUnit(Application* application, World* world) : Unit(application, world),
		_aim_draw(nullptr),
		_aim_line(nullptr),
		_current_rotation(0.f, 0.f, 0.f),
		_destination_rotation(_current_rotation),
		_player(nullptr)
	{
		Initialize();
	}
	virtual ~AimUnit(){ Finalize(); }

	virtual void Initialize() override;
	virtual void Finalize() override;
	virtual void Update() override;
	virtual void Draw() override;
	virtual void CollisionUpdate() override;

	// プレイヤーを設定
	void SetPlayer(PlayerUnit* player){ _player = player; }

	// 回転のセット
	void SetRotation(const D3DXVECTOR3& rotation){ _destination_rotation = rotation; }

	// 狙っている位置の取得
	const D3DXVECTOR3& GetTargetPosition();

	// 衝突しているか
	const bool IsHit() const;

private:

	// 描画用AIM
	AimDrawUnit* _aim_draw;
	AimLineUnit* _aim_line;

	// 現在の回転具合
	D3DXVECTOR3 _current_rotation;
	D3DXVECTOR3 _destination_rotation;

	// プレイヤー
	PlayerUnit* _player;

	// 位置の計算
	void CalculatePosition();

};