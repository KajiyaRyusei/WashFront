//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// 
// アニメーションシステム
// 
// Created by Ryusei Kajiya on 20151029
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
// クラス設計
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

	// フレームを進める
	void AdvanceFrame(const u32 advance_time)
	{
		_frame += advance_time;
	}

	// 人型の姿勢計算
	void ComputeHumanPose(
		D3DXMATRIX* matrix_list,				// 計算結果を詰め込む行列
		const u32 matrix_count,					// 行列の最大数
		const data::ObjectAnimationFile& oaf,	// アニメーションファイル
		D3DXVECTOR3& upper_body_rotation,		// 上半身の向き
		const D3DXVECTOR3& lower_body_rotation, // 下半身の向き
		const u32 mesh_id);

	// 武器のボーン選択
	void SelectWeaponBone(
		D3DXMATRIX* matrix_list,// 計算結果を詰め込む行列
		const u32 matrix_id);	// 行列番号

private:

	void ComputeHumanPoseMeshOne(D3DXMATRIX* matrix_list, const data::ObjectAnimationFile& oaf);
	void ComputeHumanPoseMeshTwo(D3DXMATRIX* matrix_list, const data::ObjectAnimationFile& oaf);
	void ComputeHumanPoseMeshThree(D3DXMATRIX* matrix_list, const data::ObjectAnimationFile& oaf);
	void ComputeHumanPoseMeshFour(D3DXMATRIX* matrix_list, const data::ObjectAnimationFile& oaf);
	void ComputeHumanPoseMeshFive(D3DXMATRIX* matrix_list, const data::ObjectAnimationFile& oaf);

	D3DXVECTOR3 _upper_rotation;
	D3DXMATRIX _upper_rotation_matrix;
	D3DXVECTOR3 _lower_rotation;
	D3DXMATRIX _lower_rotation_matrix;
	
	u32 _frame;
};