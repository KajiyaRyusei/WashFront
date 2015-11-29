//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// 
// �A�j���[�V�����V�X�e��
// 
// Created by Ryusei Kajiya on 20151029
// 
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//*****************************************************************************
// �C���N���[�h
#include "animation_system.h"
#include "Data/data_oaf.h"

//*****************************************************************************
// �萔
namespace
{
	static const fx32 kCoefficientOfPurposeUpper = 0.5f;
	static const fx32 kCoefficientOfPurposeLower = 0.1f;
}

void AnimationSystem::ComputeHumanPose(
	D3DXMATRIX* matrix_list,
	const u32 matrix_count,
	const data::ObjectAnimationFile& oaf,
	const D3DXVECTOR3& upper_body_rotation,
	const D3DXVECTOR3& lower_body_rotation )
{
	if( matrix_count < oaf.max_bone )
	{
		OutputDebugStringA("�{�[���̐����i�[�p�s��̐��𒴂��Ă��܂��B\n");
		return;
	}

	if( _frame >= oaf .end_frame)
	{
		_frame = 0;
	}

	_upper_rotation += (upper_body_rotation - _upper_rotation) * kCoefficientOfPurposeUpper;

	_lower_rotation += (lower_body_rotation - _lower_rotation) * kCoefficientOfPurposeLower;


	D3DXMatrixRotationYawPitchRoll(&_upper_rotation_matrix, _upper_rotation.y, _upper_rotation.x, _upper_rotation.z);
	D3DXMatrixRotationYawPitchRoll(&_lower_rotation_matrix, _lower_rotation.y, _lower_rotation.x, _lower_rotation.z);

	for( unsigned int bone_index = 0; bone_index < oaf.max_bone; ++bone_index )
	{
		if( bone_index < 6 )
		{// �����̔ԍ����{�[���ɍ��킹�ĕύX����ׂ�
			matrix_list[bone_index] = oaf.key[_frame].matrix_animation[bone_index] * _lower_rotation_matrix;
		}
		else
		{
			matrix_list[bone_index] = oaf.key[_frame].matrix_animation[bone_index] * _upper_rotation_matrix;
		}
	}
}
