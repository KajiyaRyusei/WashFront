//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// 
// �A�j���[�V�����V�X�e��
// 
// Created by Ryusei Kajiya on 20151014
// 
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//*****************************************************************************
// ���d�C���N���[�h�h�~
#pragma once

//*****************************************************************************
// �O���錾
namespace data
{
	struct ObjectAnimationFile;
}


//*****************************************************************************
// ��
enum HUMAN_POSE
{
	HUMAN_POSE_FRONT = 0,
	HUMAN_POSE_RIGHT,
	HUMAN_POSE_LEFT,
	HUMAN_POSE_TOP,
	HUMAN_POSE_BOTTOM,
};

//*****************************************************************************
// �N���X�݌v
class AnimationSystem
{
public:

	AnimationSystem() : 
		_rotation(0.f,0.f,0.f),
		_dest_rotation(0.f, 0.f, 0.f),
		_frame(0)
	{
		D3DXMatrixIdentity(&_rotation_matrix);
	}

	// �t���[����i�߂�
	void AdvanceFrame(const u32 advance_time)
	{
		_frame += advance_time;
	}

	// �l�^�{�[���̎p���v�Z
	void ComputeHumanPose(
		D3DXMATRIX* matrix_list,			// �v�Z���ʂ��l�ߍ��ލs��
		const u32 matrix_count,				// �s��̍ő吔
		const data::ObjectAnimationFile& oaf,// �A�j���[�V�����t�@�C��
		const HUMAN_POSE human_pose);		// �㔼�g�̌���

private:

	D3DXVECTOR3 _rotation;
	D3DXVECTOR3 _dest_rotation;
	D3DXMATRIX _rotation_matrix;
	u32 _frame;
};