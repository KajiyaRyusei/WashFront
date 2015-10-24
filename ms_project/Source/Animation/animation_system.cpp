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
	static const fx32 kCoefficientOfPurpose = 0.5f;
}

void AnimationSystem::ComputeHumanPose(
	D3DXMATRIX* matrix_list,
	const u32 matrix_count,
	const data::ObjectAnimationFile& oaf,
	const D3DXVECTOR3& human_pose)
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

	_rotation += (human_pose - _rotation) * kCoefficientOfPurpose;

	D3DXMatrixRotationYawPitchRoll(&_rotation_matrix, _rotation.y, _rotation.x, _rotation.z);

	for( unsigned int bone_index = 0; bone_index < oaf.max_bone; ++bone_index )
	{
		if( bone_index < 6 )
		{// ここの番号をボーンに合わせて変更するべし
			matrix_list[bone_index] = oaf.key[_frame].matrix_animation[bone_index];
		}
		else
		{
			matrix_list[bone_index] = oaf.key[_frame].matrix_animation[bone_index] * _rotation_matrix;
		}
	}
}
