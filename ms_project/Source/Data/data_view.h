//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// ビュー
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
	struct View
	{
	public:
		View() :
			matrix(
			1.f, 0.f, 0.f, 0.f,
			0.f, 1.f, 0.f, 0.f,
			0.f, 0.f, 1.f, 0.f,
			0.f, 0.f, 0.f, 1.f),
			eye(0.f, 0.f, 0.f),
			look_at(0.f, 0.f, 0.f),
			up(0.f, 0.f, 0.f){}

		D3DXMATRIX matrix;
		D3DXVECTOR3 eye;
		D3DXVECTOR3 look_at;
		D3DXVECTOR3 up;
	};
};

