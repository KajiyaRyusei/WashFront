//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// SHPERE
//
// Created by Ryusei Kajiya on 20151028
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//*****************************************************************************
// 多重インクルード防止
#pragma once

//*****************************************************************************
// include
#include "DevelopTool/develop_tool_manager.h"

namespace data
{
	//*****************************************************************************
	// 構造体定義
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

