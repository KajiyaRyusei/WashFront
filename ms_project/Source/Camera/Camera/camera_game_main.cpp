//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// ゲームメインカメラ
// 
// Created by Ryusei Kajiya on 20151006
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//*****************************************************************************
// インクルード
#include "camera_game_main.h"

//=============================================================================
// 初期化
void CameraGameMain::Initialize()
{
	_projection.fov = D3DXToRadian(45);
	_projection.aspect = static_cast<fx32>(16.f / 9.f);
	_projection.camera_near = 1.f;
	_projection.camera_far = 1000.f;

	_view.eye = D3DXVECTOR3(0.f, 5.f, 10.f);
	_view.look_at = D3DXVECTOR3(0.f, 0.f, 0.f);
	_view.up = D3DXVECTOR3(0.f, 1.f, 0.f);
}

//=============================================================================
// ビュープロジェクションの作成
void CameraGameMain::CreateMatrix()
{
	D3DXMatrixPerspectiveFovLH(&_projection.matrix, _projection.fov, _projection.aspect, _projection.camera_near, _projection.camera_far);
	D3DXMatrixLookAtLH(&_view.matrix, &_view.eye, &_view.look_at, &_view.up);
	D3DXMatrixPerspectiveFovLH(&_projection.matrix, _projection.fov, _projection.aspect, _projection.camera_near, _projection.camera_far);

}