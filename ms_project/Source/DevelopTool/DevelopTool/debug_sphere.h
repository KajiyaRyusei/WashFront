//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// デバッグ用球
//
// Created by Ryusei Kajiya on 20151028
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//*****************************************************************************
// 多重インクルード防止
#pragma once

//*****************************************************************************
// クラス設計
class DebugSphere
{
public:

	DebugSphere(){}
	virtual ~DebugSphere(){}

	void Initialize();
	void Finalize();
	void Draw();

	// これで登録してください
	void RegisteSphere(
		const float scale,
		const D3DXVECTOR3& position);

private:

#ifndef _RELEASE

	static const u32 kVertexMax = 30;

	struct Sphere
	{
		D3DXVECTOR3 position;
		float scale;
	};


	static const u32 kMaxShpere = 1000;
	Sphere _sphere[kMaxShpere];
	LPD3DXMESH _mesh;

	u32 _current_sphere_index;

#endif

};