//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// AIM
// 
// Created by Ryusei Kajiya on 20151029
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//*****************************************************************************
// include
#include "Unit/Game/aim.h"
#include "Unit/Game/aim_draw.h"
#include "Unit/Game/aim_line.h"

// カメラ
#include "Camera/camera_manager.h"
#include "Camera/Camera/camera_game_player.h"

// プレイヤー
#include "Unit/Game/player.h"

#include "Data/data_route.h"

//*****************************************************************************
// 定数
namespace
{
	static const fx32 kRotationCoefficient = 0.001f;
	static const D3DXVECTOR3 kTargetLength(0.f,0.f,30.f);
	static const fx32 kRotationLimitX = 0.6f;
	static const fx32 kRotationLimitY = 1.2f;
}

//=============================================================================
// 初期化
void AimUnit::Initialize()
{
	// 描画用AIMの作成
	_aim_draw = new AimDrawUnit(_application,_game_world);
	_aim_line = new AimLineUnit(_application, _game_world);

	_current_rotation = D3DXVECTOR3(0.f,0.f,0.f);
}

//=============================================================================
// 終了
void AimUnit::Finalize()
{
	SafeDelete(_aim_line);
	SafeDelete(_aim_draw);
}

//=============================================================================
// 更新
void AimUnit::Update()
{
	CalculatePosition();
	_aim_line->Update();
	_aim_draw->Update();
}

//=============================================================================
// 更新
void AimUnit::CollisionUpdate()
{
	_aim_line->CollisionUpdate();
	_aim_draw->SetEndPosition(_aim_line->GetEndPosition());
	_aim_draw->SetHit(_aim_line->IsHit());
}

//=============================================================================
// 描画
void AimUnit::Draw()
{
	_aim_line->Draw();
	_aim_draw->Draw();
}

//=============================================================================
// 位置の計算
void AimUnit::CalculatePosition()
{
	_current_rotation += (_destination_rotation - _current_rotation) * kRotationCoefficient;
	data::Route route = _player->GetPlayerCamera()->GetCurrentRoute();
	D3DXMATRIX quaternion_matrix,rotation_matrix;
	D3DXMatrixRotationQuaternion(&quaternion_matrix, &route.eye_quaternion);

	if( _current_rotation.x < -kRotationLimitX )
	{
		_current_rotation.x = -kRotationLimitX;
	}
	else if( _current_rotation.x > kRotationLimitX )
	{
		_current_rotation.x = kRotationLimitX;
	}

	if( _current_rotation.y < -kRotationLimitY )
	{
		_current_rotation.y = -kRotationLimitY;
	}
	else if( _current_rotation.y > kRotationLimitY )
	{
		_current_rotation.y = kRotationLimitY;
	}

	D3DXMatrixRotationYawPitchRoll(&rotation_matrix, _current_rotation.y, _current_rotation.x, _current_rotation.z);
	rotation_matrix *= quaternion_matrix;
	D3DXVec3TransformCoord(&_position.current, &kTargetLength, &rotation_matrix);
	_position.current += _player->GetPlayerCamera()->GetVectorEye();
	_aim_line->SetStartPosition(_player->GetPosition());
	_aim_line->SetEndPosition(_position.current);
	
}

//=============================================================================
// 狙っている位置の取得
const D3DXVECTOR3& AimUnit::GetTargetPosition()
{
	return _aim_line->GetEndPosition();
}

//=============================================================================
// 衝突しているか
const bool AimUnit::IsHit() const
{
	return _aim_line->IsHit();
}