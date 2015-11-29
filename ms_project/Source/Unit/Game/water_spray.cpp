//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// 水しぶきエフェクト
// 
// Created by Ryusei Kajiya on 20151125
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//*****************************************************************************
// include
#include "Unit/Game/water_spray.h"

//*****************************************************************************
// 定数
namespace
{
	static const fx32 kAnimationVelocity = 0.1f;
	static const fx32 kAnimationEnd = 1.f;
}

//=============================================================================
// コンストラクタ
WaterSpray::WaterSpray() : _frame(kAnimationEnd)
{

}
//=============================================================================
// 初期化
void WaterSpray::Initialize(
	const D3DXVECTOR3& position,
	const fx32 rotation)
{
	_state._position = position;
	_state._rotation = rotation;
	_state._scale = D3DXVECTOR3(0.f,0.f,0.f);
	_frame = 0.f;
}

//=============================================================================
// アニメーション
bool WaterSpray::Animate(D3DXMATRIX& matrix)
{
	if( IsUse() == false)
	{
		D3DXMatrixScaling(&matrix, 0.f, 0.f, 0.f);
		return false;
	}

	_frame += kAnimationVelocity;

	_state._scale = D3DXVECTOR3(_frame, _frame, _frame);
	D3DXMATRIX scaling_matrix, rotaiton_matrix, translation_matrix;
	D3DXMatrixScaling(&scaling_matrix, _state._scale.x, _state._scale.y, 1.f);
	D3DXMatrixRotationYawPitchRoll(&rotaiton_matrix,_state._rotation,0.f,0.f);
	D3DXMatrixTranslation(&translation_matrix, _state._position.x, _state._position.y, _state._position.z);
	matrix = scaling_matrix *rotaiton_matrix *  translation_matrix;

	if( _frame >= kAnimationEnd )
	{
		return true;
	}

	return false;
}

//=============================================================================
// 使用しているか
bool WaterSpray::IsUse()const
{
	return _frame < kAnimationEnd;
}
