//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// 
// アニメーションシステム
// 
// Created by Ryusei Kajiya on 20151014
// 
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//*****************************************************************************
// 多重インクルード防止
#pragma once

//*****************************************************************************
// 前方宣言
namespace data
{
	struct ObjectAnimationFile;
}


//*****************************************************************************
// 列挙
enum HUMAN_POSE
{
	HUMAN_POSE_FRONT = 0,
	HUMAN_POSE_RIGHT,
	HUMAN_POSE_LEFT,
	HUMAN_POSE_TOP,
	HUMAN_POSE_BOTTOM,
};

//*****************************************************************************
// クラス設計
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

	// フレームを進める
	void AdvanceFrame(const u32 advance_time)
	{
		_frame += advance_time;
	}

	// 人型ボーンの姿勢計算
	void ComputeHumanPose(
		D3DXMATRIX* matrix_list,			// 計算結果を詰め込む行列
		const u32 matrix_count,				// 行列の最大数
		const data::ObjectAnimationFile& oaf,// アニメーションファイル
		const HUMAN_POSE human_pose);		// 上半身の向き

private:

	D3DXVECTOR3 _rotation;
	D3DXVECTOR3 _dest_rotation;
	D3DXMATRIX _rotation_matrix;
	u32 _frame;
};