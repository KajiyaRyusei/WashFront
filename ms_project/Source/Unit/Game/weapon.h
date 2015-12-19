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
#include "Command/command.h"

//*****************************************************************************
// 前方宣言
class ShaderToonWeapon;
class BulletUnit;
class WaterBulletUnit;
class PlayerUnit;

//*****************************************************************************
// 武器レベル
enum WEAPON_LEVEL
{
	WEAPON_LEVEL_ONE =0,
	WEAPON_LEVEL_TWO,
	WEAPON_LEVEL_THREE,
};

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
		const D3DXMATRIX& world,
		const D3DXMATRIX& animation);

	// 発射
	void Fire(
		const D3DXVECTOR3& start,
		const D3DXVECTOR3& end,
		const Command::CONTROLLER_TYPE controller_type);

	// セットプレイヤー
	void SetPlayer(PlayerUnit* player);

	// 武器レベルアップ
	void WeaponLevel(WEAPON_LEVEL level);

	// 武器レベルの取得
	WEAPON_LEVEL GetWeaponLevel(){ return _level; }

	// テクスチャの選択
	void SelectAlbedoTexture(bool _is_player_one);

	// 装備のカラー変更
	void SelectWeaponTexture(LPDIRECT3DTEXTURE9 albedo_map);

private:

	ShaderToonWeapon* _shader;
	u32 _shader_size;
	data::World _world;
	D3DXMATRIX _matrix_world_view_projection;
	D3DXMATRIX _animation_matrix;
	// シェーダパラメーターの設定
	void SettingShaderParameter();
	// デバッグ用武器レベル選択
#ifdef _DEBUG
	void DebugWeaponLevelSelect();
#endif

	// 弾
	BulletUnit* _bullet;
	WaterBulletUnit* _water_bullet;
	WEAPON_LEVEL _level;

};