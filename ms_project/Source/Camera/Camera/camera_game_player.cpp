//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// プレイヤー用カメラ
// 
// Created by Ryusei Kajiya on 20151029
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//*****************************************************************************
// インクルード
#include "camera_game_player.h"

// 入力
#include "System/application.h"
#include "Input/input_manager.h"

// アプリケーション
#include "System/application.h"
#include "Renderer/directx9.h"

//*****************************************************************************
// 定数
namespace
{
	static const fx32 kCenterPointHeight = 5.f;
	static const fx32 kVelocityCoefficient = 0.8f;
	static const fx32 kLengthCenterAndLookAt = 30.f;
	static const fx32 kLengthCenterAndEye = -15.f;
	//static const fx32 kLengthCenterAndEye = -550.f;
	static const fx32 kCameraRotationVelocityX = 0.01f;
	static const fx32 kCameraRotationVelocityY = 0.03f;
	static const fx32 kCameraRotationLimitX = 1.15f;// 3.14のパーセンテージ
	static const fx32 kCameraRotationLimitY = 1.5f;	// 3.14のパーセンテージ
}
//=============================================================================
// 初期化
void CameraGamePlayer::Initialize()
{
	_projection.fov = D3DXToRadian(45);
	_projection.aspect = static_cast<fx32>(16.f / 9.f);
	_projection.camera_near = 1.f;
	_projection.camera_far = 1000.f;
	_view.eye = D3DXVECTOR3(0.f, 5.f, 10.f);
	_view.look_at = D3DXVECTOR3(0.f, 0.f, 0.f);
	_view.up = D3DXVECTOR3(0.f, 1.f, 0.f);
	_rotation = D3DXVECTOR3(D3DX_PI/16, 0.f, 0.f);
	_rotation_velocity = D3DXVECTOR3(0.f, 0.f, 0.f);
	_destnation_rotation_velocity = D3DXVECTOR3(0.f, 0.f, 0.f);
}

//=============================================================================
// ビュープロジェクションの作成
void CameraGamePlayer::CreateMatrix()
{
	Input();
	Chase();

	D3DXMatrixPerspectiveFovLH(&_projection.matrix, _projection.fov, _projection.aspect, _projection.camera_near, _projection.camera_far);
	D3DXMatrixLookAtLH(&_view.matrix, &_view.eye, &_view.look_at, &_view.up);
	_application->GetRendererDevice()->GetDevice()->SetTransform(D3DTS_VIEW, &_view.matrix);
	_application->GetRendererDevice()->GetDevice()->SetTransform(D3DTS_PROJECTION, &_projection.matrix);
}

//=============================================================================
// プレイヤーを追走
void CameraGamePlayer::Chase()
{
	// 中心点の作成
	D3DXVECTOR3 center_point = D3DXVECTOR3(0.f, 0.f, 0.f);

	// 中心点から注視点を作成
	D3DXMATRIX world_matrix, rotation_matrix, translation_matrix, position_matrix;
	D3DXMatrixRotationYawPitchRoll(&rotation_matrix, _rotation.y, _rotation.x, _rotation.z);
	D3DXMatrixTranslation(&translation_matrix, 0.f, 0.f, kLengthCenterAndLookAt);
	D3DXMatrixTranslation(&position_matrix, _player_position.x, _player_position.y + kCenterPointHeight, _player_position.z);
	world_matrix = translation_matrix * rotation_matrix * position_matrix;
	D3DXVec3TransformCoord(&_view.look_at, &center_point, &world_matrix);

	// 中心点から視点を作成
	D3DXMatrixRotationYawPitchRoll(&rotation_matrix, _rotation.y, _rotation.x, _rotation.z);
	D3DXMatrixTranslation(&translation_matrix, 0.f, 0.f, kLengthCenterAndEye);
	D3DXMatrixTranslation(&position_matrix, _player_position.x, _player_position.y + kCenterPointHeight, _player_position.z);
	world_matrix = translation_matrix * rotation_matrix * position_matrix;
	D3DXVec3TransformCoord(&_view.eye, &center_point, &world_matrix);
}

//=============================================================================
// 操作
void CameraGamePlayer::Input()
{
	static const float kRotationVelocityLimitX = 0.15f;
	static const float kRotationVelocityLimitY = 0.5f;

	if( _application->GetInputManager()->CheckPress(INPUT_EVENT_DOWN) )
	{
		_destnation_rotation_velocity.x = kCameraRotationVelocityX;
	}
	else if( _application->GetInputManager()->CheckPress(INPUT_EVENT_UP) )
	{
		_destnation_rotation_velocity.x = -kCameraRotationVelocityX;
	}
	else if( _application->GetInputManager()->CheckPress(INPUT_EVENT_RIGHT) )
	{
		_destnation_rotation_velocity.y = kCameraRotationVelocityY;
		
	}
	else if( _application->GetInputManager()->CheckPress(INPUT_EVENT_LEFT) )
	{
		_destnation_rotation_velocity.y = -kCameraRotationVelocityY;
	}

	_rotation_velocity += (_destnation_rotation_velocity - _rotation_velocity) * kVelocityCoefficient;
	_destnation_rotation_velocity *= kVelocityCoefficient;

	//if( _rotation.x >= D3DX_PI * kCameraRotationLimitX )
	//{
	//	_rotation.x = D3DX_PI * kCameraRotationLimitX;
	//}
	//else if( _rotation.x <= -D3DX_PI * kCameraRotationLimitX )
	//{
	//	_rotation.x = -D3DX_PI * kCameraRotationLimitX;
	//}
	//
	//if( _rotation.y >= D3DX_PI * kCameraRotationLimitY )
	//{
	//	_rotation.y = D3DX_PI * kCameraRotationLimitY;
	//}
	//else if( _rotation.y <= -D3DX_PI * kCameraRotationLimitY )
	//{
	//	_rotation.y = -D3DX_PI * kCameraRotationLimitY;
	//}

	_rotation += _rotation_velocity;
}