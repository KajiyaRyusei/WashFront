//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// SHPERE
//
// Created by Ryusei Kajiya on 20151028
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//*****************************************************************************
// ���d�C���N���[�h�h�~
#pragma once

//*****************************************************************************
// include
#include "DevelopTool/develop_tool_manager.h"

namespace data
{
	//*****************************************************************************
	// �\���̒�`
	struct Shpere
	{
	public:
		Shpere() :
			position(0.f, 0.f, 0.f),
			radius(1.f),
			level(0),
			is_player_one(false)
		{

		}

		D3DXVECTOR3 position;
		fx32 radius;
		u8 level;
		bool is_player_one;

		void DebugDraw()
		{
			DebugSphere& sphere = Reference::GetInstance().GetDevelopToolManager()->GetDebugSphere();
			sphere.RegisteSphere(
				radius,
				position);
		}
	};
};

