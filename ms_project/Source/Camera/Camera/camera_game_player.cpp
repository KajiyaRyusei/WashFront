//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// プレイヤー用カメラ
// 
// Created by Ryusei Kajiya on 20151130
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
#include "Windows/window.h"
#include "DevelopTool/develop_tool_manager.h"

//*****************************************************************************
// 定数
namespace
{
	static const fx32 kCenterPointHeight = 5.f;
	static const fx32 kVelocityCoefficient = 0.8f;
	static const fx32 kLengthCenterAndLookAt = 30.f;
	static const fx32 kLengthCenterAndEye = -20.f;
	static const fx32 kCameraRotationVelocityX = 0.01f;
	static const fx32 kCameraRotationVelocityY = 0.03f;
	static const fx32 kCameraRotationVelocityStickX = 0.0000005f;
	static const fx32 kCameraRotationVelocityStickY = 0.0000005f;
	static const fx32 kCameraRotationLimitX = 1.15f;// 3.14のパーセンテージ
	static const fx32 kCameraRotationLimitY = 1.5f;	// 3.14のパーセンテージ
	static const fx32 kPassFrameVelocity = 0.1f;

	static const D3DXVECTOR3 kLookAtVector(0.f,0.f,10.f);
}
//=============================================================================
// 初期化
void CameraGamePlayer::Initialize()
{
	//_projection.fov = D3DXToRadian(45);
	_projection.fov = D3DXToRadian(60);
	_projection.aspect = static_cast<fx32>(16.f / 9.f);
	_projection.camera_near = 1.f;
	_projection.camera_far = 1000.f;
	_view.eye = D3DXVECTOR3(0.f, -1.f, -10.f);
	_view.look_at = D3DXVECTOR3(0.f, 0.f, 0.f);
	_view.up = D3DXVECTOR3(0.f, 1.f, 0.f);
	_rotation = D3DXVECTOR3(D3DX_PI/16, 0.f, 0.f);
	_rotation_velocity = D3DXVECTOR3(0.f, 0.f, 0.f);
	_destnation_rotation_velocity = D3DXVECTOR3(0.f, 0.f, 0.f);
	_pass_frame = 0.f;
}

//=============================================================================
// ビュープロジェクションの作成
void CameraGamePlayer::CreateMatrix()
{
	//Input();
	PassRootDecision();
	//Chase();

	D3DXMatrixPerspectiveFovLH(&_projection.matrix, _projection.fov, _projection.aspect, _projection.camera_near, _projection.camera_far);
	D3DXMatrixLookAtLH(&_view.matrix, &_view.eye, &_view.look_at, &_view.up);

	_application->GetRendererDevice()->GetDevice()->SetTransform(D3DTS_VIEW, &_view.matrix);
	_application->GetRendererDevice()->GetDevice()->SetTransform(D3DTS_PROJECTION, &_projection.matrix);
}

//=============================================================================
// ルートに沿って
void CameraGamePlayer::PassRootDecision()
{
	// ルート補間
	fx32 floating_index = 0;
	fx32 frame = modf(_pass_frame, &floating_index);
	s32 index = static_cast<s32>(floating_index);
	s32 index2 = (index + 1) % _route.size();
	_current_route.LerpRoute(_route[index], _route[index2], frame);
	_view.eye = _current_route.point;
	D3DXVECTOR3 length_vector(_route[index].point - _route[index2].point);
	fx32 length_frame = 1 / D3DXVec3Length(&length_vector);
	// フレーム加算
	_pass_frame += length_frame * 0.1f;

	// ルートの最大数超えていたらまた１から
	if( _pass_frame >= static_cast<fx32>(_route.size()) )
	{
		_pass_frame = 0;
	}

	// 視点を中心に注視点を回転
	D3DXMATRIX look_at_rotation_matrix;
	D3DXMatrixRotationQuaternion(&look_at_rotation_matrix, &_current_route.eye_quaternion);
	D3DXVec3TransformCoord(&_view.look_at, &kLookAtVector, &look_at_rotation_matrix);
	_view.look_at += _view.eye;
}