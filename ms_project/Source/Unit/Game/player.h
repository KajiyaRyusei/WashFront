//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// プレイヤー
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
#include "Data/data_oaf.h"
#include "Data/data_world.h"

//*****************************************************************************
// 前方宣言
class ShaderPBLAnimation;
class MeshBuffer;
class AnimationSystem;
class AimUnit;
class CommandHandler;
class BulletUnit;



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

public:

	PlayerUnit(Application* application, World* world) : Unit(application, world)
	{
		Initialize();
	}
	virtual ~PlayerUnit(){ Finalize(); }

	virtual void Initialize() override;
	virtual void Finalize() override;
	virtual void Update() override;
	virtual void Draw() override;
	virtual void CollisionUpdate() override;

	// デバッグ用移動
	void DebugMove(const float velocity);



private:

	// シェーダー
	ShaderPBLAnimation* _shader;
	// メッシュ
	std::vector<MeshBuffer*> _mesh_list;
	// アニメーション
	data::ObjectAnimationFile _animation;
	// アニメーションシステム
	AnimationSystem* _animation_system;
	// シェーダパラメーターの設定
	void SettingShaderParameter();
	data::World _world;
	D3DXMATRIX _matrix_world_view_projection;
	LPDIRECT3DCUBETEXTURE9 _diffuse_cube_map;
	LPDIRECT3DCUBETEXTURE9 _specular_cube_map;
	LPDIRECT3DTEXTURE9 _albedo_map;

	// aim
	AimUnit* _aim;
	void AimUpdate();


	// コマンド
	CommandHandler* _command_handler;

	// 弾
	BulletUnit* _bullet;

	// 移動パス
	static const s32 kMaxPass = 4;
	D3DXVECTOR3 _pass_point_list[kMaxPass];
	fx32 _pass_frame;
	fx32 _lower_body_rotation;
	// パス計算
	void PassRootDecision();

	// 下半身の方向を制御
	D3DXVECTOR3 _front_vector;
	void LowerBodyControl();

	
};