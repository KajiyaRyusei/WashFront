//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// ���x
//
// Created by Ryusei Kajiya on 20151028
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//*****************************************************************************
// ���d�C���N���[�h�h�~
#pragma once

//*****************************************************************************
// include

namespace data
{
	//*****************************************************************************
	// �\���̒�`
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

