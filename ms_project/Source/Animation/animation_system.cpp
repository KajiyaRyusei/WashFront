//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// 
// アニメーションシステム
// 
// Created by Ryusei Kajiya on 20151029
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
	static const fx32 kCoefficientOfPurposeUpper = 0.5f;
	static const fx32 kCoefficientOfPurposeLower = 0.5f;
	static const fx32 kLimitUpperDirection = 0.905207304f;
}

//=============================================================================
// 武器のボーン選択
void AnimationSystem::SelectWeaponBone(
	D3DXMATRIX* matrix_list,
	const u32 matrix_id)
{
	matrix_list[2] = matrix_list[matrix_id];
}

//=============================================================================
// 人型の姿勢計算
void AnimationSystem::ComputeHumanPose(
	D3DXMATRIX* matrix_list,
	const u32 matrix_count,
	const data::ObjectAnimationFile& oaf,
	D3DXVECTOR3& upper_body_rotation,
	const D3DXVECTOR3& lower_body_rotation ,
	const u32 mesh_id)
{
	if( _frame >= oaf.end_frame )
	{
		_frame = 0;
	}

	if( matrix_count < oaf.animation[mesh_id].number_cluster )
	{
		OutputDebugStringA("ボーンの数が格納用行列の数を超えています。\n");
		return;
	}

	if( upper_body_rotation.x > kLimitUpperDirection )
	{
		upper_body_rotation.x = kLimitUpperDirection;
	}
	else if( upper_body_rotation.x < -kLimitUpperDirection )
	{
		upper_body_rotation.x = -kLimitUpperDirection;
	}

	_upper_rotation += (upper_body_rotation - _upper_rotation) * kCoefficientOfPurposeUpper;
	_lower_rotation += (upper_body_rotation - _lower_rotation) * kCoefficientOfPurposeLower;
	UNREFERENCED_PARAMETER(lower_body_rotation);

	D3DXMatrixRotationYawPitchRoll(&_upper_rotation_matrix, _upper_rotation.y, _upper_rotation.x, _upper_rotation.z);
	D3DXMatrixRotationYawPitchRoll(&_lower_rotation_matrix, _lower_rotation.y, _lower_rotation.x, _lower_rotation.z);

	switch( mesh_id )
	{
	case 0:
		ComputeHumanPoseMeshOne(matrix_list, oaf);
		break;
	case 1:
		ComputeHumanPoseMeshTwo(matrix_list, oaf);
		break;
	case 2:
		ComputeHumanPoseMeshThree(matrix_list, oaf);
		break;
	case 3:
		ComputeHumanPoseMeshFour(matrix_list, oaf);
		break;
	case 4:
		ComputeHumanPoseMeshFive(matrix_list, oaf);
		break;
	default:
		break;
	}
}

//=============================================================================
// メッシュごとの行列変換
void AnimationSystem::ComputeHumanPoseMeshOne(D3DXMATRIX* matrix_list, const data::ObjectAnimationFile& oaf)
{
	for( u32 cluster_index = 0; cluster_index < oaf.animation[0].number_cluster; ++cluster_index )
	{
		matrix_list[cluster_index] = oaf.animation[0].frame[_frame].matrix_animation[cluster_index] * _upper_rotation_matrix;
	}
}

void AnimationSystem::ComputeHumanPoseMeshTwo(D3DXMATRIX* matrix_list, const data::ObjectAnimationFile& oaf)
{
	for( u32 cluster_index = 0; cluster_index < oaf.animation[1].number_cluster; ++cluster_index )
	{
		matrix_list[cluster_index] = oaf.animation[1].frame[_frame].matrix_animation[cluster_index] * _upper_rotation_matrix;
	}
}

void AnimationSystem::ComputeHumanPoseMeshThree(D3DXMATRIX* matrix_list, const data::ObjectAnimationFile& oaf)
{
	for( u32 cluster_index = 0; cluster_index < oaf.animation[2].number_cluster; ++cluster_index )
	{
		matrix_list[cluster_index] = oaf.animation[2].frame[_frame].matrix_animation[cluster_index] * _upper_rotation_matrix;
	}
}

void AnimationSystem::ComputeHumanPoseMeshFour(D3DXMATRIX* matrix_list, const data::ObjectAnimationFile& oaf)
{
	for( u32 cluster_index = 0; cluster_index < oaf.animation[3].number_cluster; ++cluster_index )
	{
		matrix_list[cluster_index] = oaf.animation[3].frame[_frame].matrix_animation[cluster_index] * _upper_rotation_matrix;
	}
}

void AnimationSystem::ComputeHumanPoseMeshFive(D3DXMATRIX* matrix_list, const data::ObjectAnimationFile& oaf)
{
	for( u32 cluster_index = 0; cluster_index < oaf.animation[4].number_cluster; ++cluster_index )
	{
		if( cluster_index < 5 )
		{
			matrix_list[cluster_index] = oaf.animation[4].frame[_frame].matrix_animation[cluster_index] * _lower_rotation_matrix;
		}
		else
		{
			matrix_list[cluster_index] = oaf.animation[4].frame[_frame].matrix_animation[cluster_index] * _upper_rotation_matrix;
		}
	}
}