//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// バレット
// 
// Created by Ryusei Kajiya on 20151029
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//*****************************************************************************
// include
#include "Unit/Game/bullet.h"
#include "Camera/camera_manager.h"
#include "Camera/Camera/camera_game_player.h"
#include "Algorithm/often_use.h"
#include "World/collision_grid.h"
// sound
#include "Sound/sound.h"
//=============================================================================
// 定数
namespace
{
	static const fx32 kBulletSize = 3.5f;
}

//=============================================================================
// 初期化
void BulletUnit::Initialize()
{
	// 座標の設定
	_position.current = D3DXVECTOR3(0.f, 0.f, 0.f);
	_position.previous = _position.current;
	_world.position = _position.current;
	_world.scale = D3DXVECTOR3(kBulletSize, kBulletSize, kBulletSize);
	_world.rotation = D3DXVECTOR3(0.f, 0.f, 0.f);

	// 弾の設定
	_start_point = _position.current;
	_end_point = _position.current;
	_control_point = _position.current;
	_frame_velocity = 0.f;
	_frame = 1.f;

	// ボリュームの作成
	CreateVolumeShpre(_world.position, _world.scale.x);

	// 空間に突っ込む
	_game_world->GetCollisionGrid()->AddUnit(this, _position);
}

//=============================================================================
// 終了
void BulletUnit::Finalize()
{
	if( _shpere->is_player_one == true )
	{
		_application->GetSound()->Stop(SE_WATER_BULLET);
	}
	else
	{
		_application->GetSound()->Stop(SE_WATER_BULLET_2);
	}
}

//=============================================================================
// 更新
void BulletUnit::Update()
{
	// シェーダパラメーターの更新
	if( _frame >= 1.f)
	{
		if( _shpere->is_player_one == true )
		{
			_application->GetSound()->Stop(SE_WATER_BULLET);
		}
		else
		{
			_application->GetSound()->Stop(SE_WATER_BULLET_2);
		}
		_shpere->position = D3DXVECTOR3(100000.f, 100000.f, 100000.f);
	}
	else
	{
		Move();
		_game_world->GetCollisionGrid()->MoveUnit(this, _position);
		_shpere->position = _position.current;
	}
}
//=============================================================================
// 衝突判定用更新
void BulletUnit::CollisionUpdate()
{

}
//=============================================================================
// 衝突判定時処理 : 球
void BulletUnit::CollisionSphere()
{
	if( _shpere->is_player_one == true )
	{
		_application->GetSound()->Stop(SE_WATER_BULLET);
	}
	else
	{
		_application->GetSound()->Stop(SE_WATER_BULLET_2);
	}
	_frame = 1.f;
}
//=============================================================================
// 衝突判定時処理 : ボックス
void BulletUnit::CollisionBox()
{
	if( _shpere->is_player_one == true )
	{
		_application->GetSound()->Stop(SE_WATER_BULLET);
	}
	else
	{
		_application->GetSound()->Stop(SE_WATER_BULLET_2);
	}
	_frame = 1.f;
}
//=============================================================================
// 描画
void BulletUnit::Draw()
{
//	_shpere->DebugDraw();
}

//=============================================================================
// 発射
void BulletUnit::Fire(
	const D3DXVECTOR3& start,
	const D3DXVECTOR3& end,
	const fx32 velocity,
	const Command::CONTROLLER_TYPE controller_type)
{
	if( _frame < 1.f )
	{
		return;
	}
	_start_point = start;
	_end_point = end;
	_control_point = (start + end) / 2;
	_control_point.y += 5.f;
	_frame_velocity = velocity;
	_frame = 0.f;
	_position.current = start;
	if( controller_type == Command::CONTROLLER_TYPE_1P)
	{
		_shpere->is_player_one = true;
		_application->GetSound()->Play(SE_WATER_BULLET);
	}
	else
	{
		_shpere->is_player_one = false;
		_application->GetSound()->Play(SE_WATER_BULLET_2);
	}
	
	
}

//=============================================================================
// 移動
void BulletUnit::Move()
{
	algo::BezierCurve2D(_position.current,_start_point,_end_point,_control_point,_frame);
	_frame += _frame_velocity;
}

//=============================================================================
// バレットサイズ更新
void BulletUnit::ReNewBulletSize(const u8 level)
{
	_shpere->level = level;
}