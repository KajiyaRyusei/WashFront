//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// タイトルカメラ
// 
// Created by Ryusei Kajiya on 20151201
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//*****************************************************************************
// インクルード
#include "camera_title.h"

//=============================================================================
// 初期化
void CameraTitle::Initialize()
{
	_projection.fov = D3DXToRadian(60);
	_projection.aspect = static_cast<fx32>(16.f / 9.f);
	_projection.camera_near = 1.f;
	_projection.camera_far = 1000.f;

	_view.eye = D3DXVECTOR3(100.f, 100.f, 100.f);
	_view.look_at = D3DXVECTOR3(200.f, 60.f, 200.f);
	_view.up = D3DXVECTOR3(0.f, 1.f, 0.f);
}

//=============================================================================
// ビュープロジェクションの作成
void CameraTitle::CreateMatrix()
{
	D3DXMatrixPerspectiveFovLH(&_projection.matrix, _projection.fov, _projection.aspect, _projection.camera_near, _projection.camera_far);
	D3DXMatrixLookAtLH(&_view.matrix, &_view.eye, &_view.look_at, &_view.up);
}