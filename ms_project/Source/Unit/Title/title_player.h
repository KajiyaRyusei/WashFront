//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// タイトルプレイヤー
// 
// Created by Ryusei Kajiya on 20151212
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//*****************************************************************************
// 多重インクルード防止
#pragma once

//*****************************************************************************
// include
#include "Unit/unit.h"
#include "Data/data_oaf.h"
#include "Data/data_world.h"

//*****************************************************************************
// 前方宣言
class ShaderToonPlayer;
class AnimationSystem;
class WaterBackUnit;
class TitleWeaponUnit;

//*****************************************************************************
// クラス設計
class TitlePlayerUnit : public Unit
{
public:

	TitlePlayerUnit(Application* application, World* world) : Unit(application, world)
	{
		Initialize();
	}
	virtual ~TitlePlayerUnit(){ Finalize(); }

	virtual void Initialize() override;
	virtual void Finalize() override;
	virtual void Update() override;
	virtual void Draw() override;
	virtual void CollisionUpdate() override{};

private:

	// シェーダー
	ShaderToonPlayer* _shader;
	// シェーダ数:メッシュ数に合わせる
	u32 _shader_size;
	// アニメーション
	data::ObjectAnimationFile* _statnce_animation;
	// アニメーションシステム
	AnimationSystem* _statnce_animation_system;

	// シェーダパラメーターの設定
	void SettingShaderParameter();
	data::World _world;
	D3DXMATRIX _matrix_world_view_projection;
	// 後ろ水
	WaterBackUnit* _back_water;
	// 武器
	TitleWeaponUnit* _weapon;

	// 水とアニメーションを合わせる
	void CompositionWater2Animation(const D3DXMATRIX* matrices);
};