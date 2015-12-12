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
class ShaderToonWeapon;

//*****************************************************************************
// クラス設計
class TitleWeaponUnit : public Unit
{
public:

	TitleWeaponUnit(Application* application, World* world) : Unit(application, world)
	{
		Initialize();
	}
	virtual ~TitleWeaponUnit(){ Finalize(); }

	virtual void Initialize() override;
	virtual void Finalize() override;
	virtual void Update() override;
	virtual void Draw() override;
	virtual void CollisionUpdate() override;

	// 座標の設定
	void SetPosition(
		const D3DXMATRIX& world,
		const D3DXMATRIX& animation);



private:

	ShaderToonWeapon* _shader;
	u32 _shader_size;
	data::World _world;
	D3DXMATRIX _matrix_world_view_projection;
	D3DXMATRIX _animation_matrix;
	// シェーダパラメーターの設定
	void SettingShaderParameter();

};