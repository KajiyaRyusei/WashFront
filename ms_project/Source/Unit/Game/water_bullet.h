//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// 水弾
// 
// Created by Ryusei Kajiya on 20151111
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
class ShaderWater;
class PlayerUnit;

//*****************************************************************************
// クラス設計
class WaterBulletUnit : public Unit
{
public:

	WaterBulletUnit(Application* application, World* world) : Unit(application, world)
	{
		Initialize();
	}
	virtual ~WaterBulletUnit(){ Finalize(); }

	virtual void Initialize() override;
	virtual void Finalize() override;
	virtual void Update() override;
	virtual void Draw() override;
	virtual void CollisionUpdate() override;


	// 発射
	void Fire(const D3DXVECTOR3& end);

	// セットプレイヤー
	void SetPlayer(PlayerUnit* player){ _player = player; }

	// アンビエントカラー変更
	void ReNewAmbientColor(const D3DXVECTOR4& ambient){ _ambient = ambient; }

private:

	// シェーダー
	ShaderWater* _shader;
	// シェーダパラメーターの設定
	void SettingShaderParameter();
	data::World _world;
	D3DXMATRIX _matrix_world_view_projection;
	D3DXMATRIX _matrix_water[3];

	// 弾のパラメータ
	D3DXVECTOR3 _start_point;
	D3DXVECTOR3 _end_point;
	D3DXVECTOR3 _control_point;
	fx32 _rotation_y;
	fx32 _destination_release_of;
	fx32 _release_of;
	D3DXVECTOR4 _ambient;

	// プレイヤー
	PlayerUnit* _player;
};