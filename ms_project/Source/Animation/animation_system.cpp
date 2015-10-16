//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// 
// アニメーションシステム
// 
// Created by Ryusei Kajiya on 20151014
// 
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//*****************************************************************************
// インクルード
#include "animation_system.h"
#include "Data/data_oaf.h"

//*****************************************************************************
// 定数
namespace
{
	static const fx32 kCoefficientOfPurpose = 0.1f;
}

void AnimationSystem::ComputeHumanPose(
	D3DXMATRIX* matrix_list,
	const u32 matrix_count,
	const data::ObjectAnimationFile& oaf,
	const HUMAN_POSE human_pose)
{
	if( matrix_count < oaf.max_bone )
	{
		OutputDebugStringA("ボーンの数が格納用行列の数を超えています。\n");
		return;
	}

	if( _frame >= oaf .end_frame)
	{
		_frame = 0;
	}

	switch( human_pose )
	{
	case HUMAN_POSE_FRONT:
		_dest_rotation.x = 0.f;
		_dest_rotation.y = 0.f;
		break;
	case HUMAN_POSE_RIGHT:
		_dest_rotation.x = 0.f;
		_dest_rotation.y = 1.07079f;
		break;
	case HUMAN_POSE_LEFT:
		_dest_rotation.x = 0.f;
		_dest_rotation.y = -1.07079f;
		break;
	case HUMAN_POSE_TOP:
		_dest_rotation.x = -0.57079f;
		_dest_rotation.y = 0.f;
		break;
	case HUMAN_POSE_BOTTOM:
		_dest_rotation.x = 0.57079f;
		_dest_rotation.y = 0.f;
		break;
	}

	_rotation += (_dest_rotation - _rotation) * kCoefficientOfPurpose;

	D3DXMatrixRotationYawPitchRoll(&_rotation_matrix, _rotation.y, _rotation.x, _rotation.z);

	for( unsigned int bone_index = 0; bone_index < oaf.max_bone; ++bone_index )
	{
		if( bone_index < 11 )
		{// ここの番号をボーンに合わせて変更するべし
			matrix_list[bone_index] = oaf.key[_frame].matrix_animation[bone_index];
		}
		else
		{
			matrix_list[bone_index] = oaf.key[_frame].matrix_animation[bone_index] * _rotation_matrix;
		}
	}
}