//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// プロジェクション
//
// Created by Ryusei Kajiya on 20151009
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//*****************************************************************************
// 多重インクルード防止
#pragma once

namespace data
{
	//*****************************************************************************
	// 構造体定義
	struct Projection
	{
	public:
		Projection() :
			matrix(
			1.f, 0.f, 0.f, 0.f,
			0.f, 1.f, 0.f, 0.f,
			0.f, 0.f, 1.f, 0.f,
			0.f, 0.f, 0.f, 1.f),
			fov(D3DXToRadian(45)),
			aspect(16/9),
			camera_near(1.f),
			camera_far(10000.f),
			volume_width(200.f),
			volume_height(200.f),
			volume_near(-200.f),
			volume_far(200.f){}

		D3DXMATRIX matrix;
		fx32 fov;
		fx32 aspect;
		fx32 camera_near;
		fx32 camera_far;
		fx32 volume_width;
		fx32 volume_height;
		fx32 volume_near;
		fx32 volume_far;
	};
};

