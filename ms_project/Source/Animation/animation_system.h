//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// 
// �A�j���[�V�����V�X�e��
// 
// Created by Ryusei Kajiya on 20151029
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
// �N���X�݌v
class AnimationSystem
{
public:

	AnimationSystem() : 
		_upper_rotation(0.f, 0.f, 0.f),
		_lower_rotation(0.f, 0.f, 0.f),
		_frame(0)
	{
		D3DXMatrixIdentity(&_upper_rotation_matrix);
		D3DXMatrixIdentity(&_lower_rotation_matrix);
	}

	// �t���[����i�߂�
	void AdvanceFrame(const u32 advance_time)
	{
		_frame += advance_time;
	}

	// �l�^�{�[���̎p���v�Z
	void ComputeHumanPose(
		D3DXMATRIX* matrix_list,				// �v�Z���ʂ��l�ߍ��ލs��
		const u32 matrix_count,					// �s��̍ő吔
		const data::ObjectAnimationFile& oaf,	// �A�j���[�V�����t�@�C��
		const D3DXVECTOR3& upper_body_rotation,	// �㔼�g�̌���
		const D3DXVECTOR3& lower_body_rotation);// �����g�̌���

private:

	D3DXVECTOR3 _upper_rotation;
	D3DXMATRIX _upper_rotation_matrix;
	D3DXVECTOR3 _lower_rotation;
	D3DXMATRIX _lower_rotation_matrix;
	u32 _frame;
};