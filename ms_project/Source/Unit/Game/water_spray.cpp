////+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
////
//// 水しぶきエフェクト
//// 
//// Created by Ryusei Kajiya on 20151125
////
////+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
////*****************************************************************************
//// include
//#include "Unit/Game/water_spray.h"
//
////=============================================================================
//// 初期化
//void WaterSpray::Initialize(
//	const D3DXVECTOR3& position,
//	const D3DXQUATERNION& quaternion)
//{
//	UNREFERENCED_PARAMETER(position);
//	UNREFERENCED_PARAMETER(quaternion);
//}
//
////=============================================================================
//// アニメーション
//bool WaterSpray::Animate()
//{
//	if( IsUse() == false)
//	{
//		return false;
//	}
//
//	_frame_left--;
//
//	return _frame_left == 0;
//}