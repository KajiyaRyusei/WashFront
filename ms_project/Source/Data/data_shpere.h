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
			radius(1.f)
		{

		}

		D3DXVECTOR3 position;
		fx32 radius;

		void DebugDraw()
		{
			DebugSphere& sphere = Reference::GetInstance().GetDevelopToolManager()->GetDebugSphere();
			sphere.RegisteSphere(
				radius,
				position);
		}
	};
};

