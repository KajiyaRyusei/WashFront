//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// 
// �Փ˔���֐��Q
// 
// Created by Ryusei Kajiya on 20151102
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//*****************************************************************************
// �C���N���[�h
#include "collision_system.h"


namespace collision
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

	//=============================================================================
	// �_�ƎO�p�`�̏Փ˔���
	bool Point2Trigangle(
		const D3DXVECTOR3& point,		// �_
		const D3DXVECTOR3& point_one,	// �O�p�`�̍��W1
		const D3DXVECTOR3& point_two,	// �O�p�`�̍��W2
		const D3DXVECTOR3& point_three)	// �O�p�`�̍��W3
	{
		D3DXVECTOR3 one2point = point_one - point;
		D3DXVECTOR3 two2point = point_two - point;
		D3DXVECTOR3 three2point = point_three - point;

		D3DXVECTOR3 one2two = point_two - point_one;
		D3DXVECTOR3 two2three = point_three - point_two;
		D3DXVECTOR3 three2one = point_one - point_three;

		D3DXVECTOR3 cross1;
		D3DXVECTOR3 cross2;
		D3DXVECTOR3 cross3;

		D3DXVec3Cross(&cross1, &one2two, &two2point);
		D3DXVec3Cross(&cross2, &two2three, &three2point);
		D3DXVec3Cross(&cross3, &three2one, &one2point);

		fx32 dot12 = D3DXVec3Dot(&cross1, &cross2);
		fx32 dot13 = D3DXVec3Dot(&cross1, &cross3);

		if( dot12 > 0.0f && dot13 > 0.0f )
		{
			return true;
		}

		return false;
	}

	//=============================================================================
	// ���ƎO�p�`�̏Փ˔���
	bool Line2Trigangle(
		D3DXVECTOR3* impact_point,		// �Փ˂��Ă�ꏊ
		const D3DXVECTOR3& start_point,	// �����̎n�_
		const D3DXVECTOR3& end_point,	// �����̏I�_
		const D3DXVECTOR3& point_one,	// �O�p�`�̍��W1
		const D3DXVECTOR3& point_two,	// �O�p�`�̍��W2
		const D3DXVECTOR3& point_three)// �O�p�`�̍��W3
	{
		D3DXVECTOR3 line = end_point - start_point;
		D3DXVECTOR3 one2two = point_two - point_one;
		D3DXVECTOR3 one2three = point_three - point_one;
		D3DXVECTOR3 normal;

		D3DXVec3Cross(&normal, &one2two, &one2three);
		D3DXVec3Normalize(&normal, &normal);

		D3DXVECTOR3 one2start = start_point - point_one;
		D3DXVECTOR3 one2end = end_point - point_one;
		fx32 dot1 = D3DXVec3Dot(&one2start, &normal);
		fx32 dot2 = D3DXVec3Dot(&one2end, &normal);

		if( dot1 >= 0.0f && dot2 <= 0.0f )
		{
			dot2 = abs(dot2);
		}
		else if( dot1 <= 0.0f && dot2 >= 0.0f )
		{
			dot1 = abs(dot1);
		}
		else
		{
			return false;
		}

		// ��_�܂ł̃x�N�g�������߂�
		D3DXVECTOR3 intersection;

		if( (dot1 + dot2) == 0.0f ) {
			intersection = line * 0.0f;
		}
		else {
			intersection = line * (dot1 / (dot1 + dot2));
		}

		// ��_
		D3DXVECTOR3 cross_point = start_point + intersection;

		// ��_���O�p�`���ʏ�ɑ��݂���
		if( Point2Trigangle(cross_point, point_one, point_two, point_three) )
		{
			if( impact_point != nullptr )
			{
				*impact_point = cross_point;

				// �Փ˂��Ă���ʂ̖@���Z�o
			}
			return true;
		}

		return false;
	}

	//=============================================================================
	// ���Ǝl�p�`�̏Փ�
	bool Line2Square(
		D3DXVECTOR3* impact_point,		// �Փ˂��Ă�ꏊ
		const D3DXVECTOR3& start_point,	// �����̎n�_
		const D3DXVECTOR3& end_point,	// �����̏I�_
		const D3DXVECTOR3& point_one,	// �l�p�`�̍��W1
		const D3DXVECTOR3& point_two,	// �l�p�`�̍��W2
		const D3DXVECTOR3& point_three,	// �l�p�`�̍��W3
		const D3DXVECTOR3& point_four)	// �l�p�`�̍��W3
	{
		if( Line2Trigangle(impact_point, start_point, end_point, point_one, point_two, point_three) )
		{
			return true;
		}

		if( Line2Trigangle(impact_point, start_point, end_point, point_two, point_three, point_four) )
		{
			return true;
		}

		return false;
	}

	//=============================================================================
	// ���Ɨ����̂̏Փ�
	bool Line2Box(
		D3DXVECTOR3* impact_point,		// �Փ˂��Ă�ꏊ
		const D3DXVECTOR3& start_point,	// �����̎n�_
		const D3DXVECTOR3& end_point,	// �����̏I�_
		const D3DXVECTOR3& ltf,			// �����O
		const D3DXVECTOR3& rtf,			// �����O
		const D3DXVECTOR3& lbf,			// �����O
		const D3DXVECTOR3& rbf,			// �����O
		const D3DXVECTOR3& ltb,			// ������
		const D3DXVECTOR3& rtb,			// ������
		const D3DXVECTOR3& lbb,			// ������
		const D3DXVECTOR3& rbb)			// ������
	{
		D3DXVECTOR3 front[] = { ltf, rtf, lbf, rbf };
		D3DXVECTOR3 back[] = { ltb, rtb, lbb, rbb };
		D3DXVECTOR3 right[] = { rtb,rtf, rbb,rbf};
		D3DXVECTOR3 left[] = { ltf, ltb, lbf,lbb };
		D3DXVECTOR3 top[] = { ltf, rtf, ltb, rtb };
		D3DXVECTOR3 bottom[] = { lbf, rbf, lbb, rbb };

		static const D3DXVECTOR3 false_point(10000.f,10000.f,10000.f);

		D3DXVECTOR3 impact_point_position[6] = {false_point, false_point, false_point, false_point, false_point, false_point };


		Line2Square(&impact_point_position[0], start_point, end_point, front[0], front[1], front[2], front[3]);
		Line2Square(&impact_point_position[1], start_point, end_point, back[0], back[1], back[2], back[3]);
		Line2Square(&impact_point_position[2], start_point, end_point, right[0], right[1], right[2], right[3]);
		Line2Square(&impact_point_position[3], start_point, end_point, left[0], left[1], left[2], left[3]);
		Line2Square(&impact_point_position[4], start_point, end_point, top[0], top[1], top[2], top[3]);
		Line2Square(&impact_point_position[5], start_point, end_point, bottom[0], bottom[1], bottom[2], bottom[3]);


		D3DXVECTOR3 temp;

		for( int i = 0; i < 6; ++i )
		{
			for( int j = 0; j < 6; ++j )
			{
				if( i == j)
				{
					continue;
				}
				D3DXVECTOR3 i_length_vector(impact_point_position[i] - start_point);
				D3DXVECTOR3 j_length_vector(impact_point_position[j] - start_point);
				fx32 i_length = D3DXVec3Length(&i_length_vector);
				fx32 j_length = D3DXVec3Length(&j_length_vector);
				if( i_length < j_length )
				{// [2] > [1]
					// [1]X = [1]
					temp = impact_point_position[j];
					// [1] << [2]
					impact_point_position[j] = impact_point_position[i];
					// [2] << [1]X
					impact_point_position[i] = temp;
				}
			}
		}


		if( impact_point_position[0] == false_point )
		{// �����l�̂܂܂Ȃ�Փ˂��Ă��Ȃ�
			impact_point = nullptr;
			return false;
		}

		// �Փ˓_����
		*impact_point = impact_point_position[0];

		return true;
	}

	//=============================================================================
	// ���Ƌ��̏Փ˔���
	bool Sphrere2Sphrere(
		const D3DXVECTOR3& point_one,	// ���̒��S�@
		const D3DXVECTOR3& point_two,	// ���̒��S�A
		const fx32 radius_one,			// ���̔��a�@
		const fx32 radius_two)			// ���̔��a�A
	{
		return powf(point_two.x - point_one.x, 2) + powf(point_two.y - point_one.y, 2) + powf(point_two.z - point_one.z, 2) <= powf(radius_one + radius_two, 2);
	}

	//=============================================================================
	// �����̂Ɨ����̂̏Փ˔���
	bool Box2Box(
		const D3DXVECTOR3& p1,	// �����̇@�̒��S
		const D3DXVECTOR3& s1,	// �����̇@�̂P�ӂ̔����̑傫��
		const D3DXVECTOR3& p2,	// �����̇A�̒��S
		const D3DXVECTOR3& s2)	// �����̇A�̂P�ӂ̔����̑傫��
	{
		D3DXVECTOR3 temp_p1 = p1 + s1;
		D3DXVECTOR3 temp_s1 = s1 * 2.0f;
		D3DXVECTOR3 temp_p2 = p2 + s2;
		D3DXVECTOR3 temp_s2 = s2 * 2.0f;

		return temp_p1.x <= temp_p2.x + temp_s2.x && temp_p2.x <= temp_p1.x + temp_s1.x && temp_p1.y <= temp_p2.y + temp_s2.y && temp_p2.y <= temp_p1.y + temp_s1.y && temp_p1.z <= temp_p2.z + temp_s2.z && temp_p2.z <= temp_p1.z + temp_s1.z;
	}

	//=============================================================================
	// ���Ɠ_
	bool Sphrere2Point(
		const D3DXVECTOR3& sphrere_center,	// ���̒��S
		const D3DXVECTOR3& point,			// �_
		const fx32 radius)					// ���̔��a
	{
		D3DXVECTOR3 temp = sphrere_center - point;
		fx32 sphrere_point_length = D3DXVec3Length(&temp);
		if( sphrere_point_length  < radius )
		{
			return true;
		}
		return false;
	}
	
};