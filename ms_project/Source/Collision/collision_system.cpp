//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// 
// �Փ˔���֐��Q
// 
// Author : ryusei kajiya
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//*****************************************************************************
// �C���N���[�h
#include "collision_system.h"


namespace cs
{
	//=============================================================================
	// ��`�̏Փ˔���
	bool Rect2Rect(
		const D3DXVECTOR2 &p1,
		const D3DXVECTOR2 &s1,
		const D3DXVECTOR2 &p2,
		const D3DXVECTOR2 &s2)
	{
		if (p1.x < p2.x + s2.x)
		{
			if (p2.x < p1.x + s1.x)
			{
				if (p1.y < p2.y + s2.y)
				{
					if (p2.y < p1.y + s1.y)
					{
						return true;
					}
				}
			}
		}

		return  false;
	}
};