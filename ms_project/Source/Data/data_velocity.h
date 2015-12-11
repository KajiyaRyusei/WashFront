//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// 速度
//
// Created by Ryusei Kajiya on 20151028
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//*****************************************************************************
// 多重インクルード防止
#pragma once

//*****************************************************************************
// include

namespace data
{
	//*****************************************************************************
	// 構造体定義
	struct Velocity
	{
	public:
		Velocity() :
			current(0.f, 0.f, 0.f),
			destnation(current)
		{

		}

		D3DXVECTOR3 current;
		D3DXVECTOR3 destnation;

		void ComputeDestinationVelocity(fx32 coefficient)
		{
			current += (destnation - current) * coefficient;
		}
	};
};

