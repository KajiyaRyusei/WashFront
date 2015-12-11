//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// プレイヤー
// 
// Created by Ryusei Kajiya on 20151207
//
//<やること>
// カメラのルートに合わせる
// アニメーションに水を合わせる：CPUで計算
// シェーダのスペキュラ削除
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//*****************************************************************************
// 多重インクルード防止
#pragma once

//*****************************************************************************
// include
#include "Unit/unit.h"
#include "Data/data_oaf.h"
#include "Data/data_world.h"
#include "Data/data_velocity.h"

#include "Command/command_handler.h"

//*****************************************************************************
// 前方宣言
class ShaderToonPlayer;
class AnimationSystem;
class AimUnit;
class CommandHandler;
class WeaponUnit;
class WaterBackUnit;
class CameraGamePlayer;

//*****************************************************************************
// クラス設計
class PlayerUnit : public Unit
{
	friend class CommandMoveFront;
	friend class CommandMoveBack;
	friend class CommandMoveRight;
	friend class CommandMoveLeft;
	friend class CommandMoveUp;
	friend class CommandMoveDown;
	friend class CommandFire;
	friend class CommandMove;

public:

	PlayerUnit(Application* application, World* world, CameraGamePlayer* camera) : Unit(application, world),
		_player_camera(camera)
	{
		Initialize();
	}
	virtual ~PlayerUnit(){ Finalize(); }

	virtual void Initialize() override;
	virtual void Finalize() override;
	virtual void Update() override;
	virtual void Draw() override;
	virtual void CollisionUpdate() override;

	// プレイヤーの座標を取得：いろいろと計算がいるバージョン
	// ちょい手前
	const D3DXVECTOR3 GetPosition();

	void SetControllerType(Command::CONTROLLER_TYPE type){ _controller_type = type; }

	CameraGamePlayer* GetPlayerCamera()const{ return _player_camera; }

private:

	// シェーダー
	ShaderToonPlayer* _shader;
	// シェーダ数:メッシュ数に合わせる
	u32 _shader_size;
	// アニメーション
	data::ObjectAnimationFile _animation;
	// アニメーションシステム
	AnimationSystem* _animation_system;
	// シェーダパラメーターの設定
	void SettingShaderParameter();
	data::World _world;
	D3DXMATRIX _matrix_world_view_projection;
	// aim
	AimUnit* _aim;
	void AimUpdate();
	// コマンド
	CommandHandler* _command_handler;
	// 武器
	WeaponUnit* _weapon;
	// 後ろ水
	WaterBackUnit* _back_water;
	// プレイヤー用カメラ
	CameraGamePlayer* _player_camera;
	// コントローラータイプ
	Command::CONTROLLER_TYPE _controller_type;

	// 水とアニメーションを合わせる
	void CompositionWater2Animation(const D3DXMATRIX* matrices);
	// 座標と向き設定
	void PassRootDecision();

};