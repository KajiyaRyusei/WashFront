//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// 
// 2Dカメラ
// 
// Created by Ryusei Kajiya on 20151022
// 
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//*****************************************************************************
// インクルード
#include "camera_2d.h"

//=============================================================================
// 初期化
void Camera2D::Initialize()
{
	_projection.volume_near = -100.f;
	_projection.volume_far = 100.f;
	_projection.volume_height = 100.f;
	_projection.volume_width = 100.f;

	_view.eye = D3DXVECTOR3(0.f, 0.f, -50.f);
	_view.look_at = D3DXVECTOR3(0.f, 0.f, 0.f);
	_view.up = D3DXVECTOR3(0.f, 1.f, 0.f);
}

//=============================================================================
// ビュープロジェクションの作成
void Camera2D::CreateMatrix()
{
	D3DXMatrixOrthoLH(&_projection.matrix, _projection.volume_width, _projection.volume_height, _projection.volume_near, _projection.volume_far);
	D3DXMatrixLookAtLH(&_view.matrix, &_view.eye, &_view.look_at, &_view.up);
}