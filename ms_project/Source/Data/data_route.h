//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// ���[�g�̃f�[�^
//
// Created by Ryusei Kajiya on 20151204
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//*****************************************************************************
// ���d�C���N���[�h�h�~
#pragma once

namespace data
{
	//*****************************************************************************
	// �\���̒�`
	struct Route
	{
	public:
		Route() :
			point(0.f, 0.f, 0.f),
			eye_rotation(0.f, 0.f, 0.f),
			player_rotation(0.f, 0.f, 0.f),
			velocity(0.f),
			state(0)
		{
			D3DXQuaternionIdentity(&eye_quaternion);
			D3DXQuaternionIdentity(&player_quaternion);
		}

		D3DXVECTOR3 point;
		D3DXVECTOR3 eye_rotation;
		D3DXVECTOR3 player_rotation;
		D3DXQUATERNION eye_quaternion;
		D3DXQUATERNION player_quaternion;
		fx32 velocity;
		s32 state;

		// ���[�g�̕��
		void LerpRoute(
			const Route& route_one,
			const Route& route_two,
			const fx32 frame)
		{
			float t2;
			if( frame < 0.5f )
				t2 = 2 * frame * 2 * frame * 0.5f;
			else
				t2 = -1 * (2 * frame - 2) * (2 * frame - 2) * 0.5f + 1.0f;


			this->state = route_one.state;
			this->velocity = route_one.velocity;
			//D3DXVec3Lerp(&this->point, &route_one.point, &route_two.point, t2);
			this->point = route_one.point * (1 - frame) + route_two.point * frame;
			D3DXQuaternionSlerp(&this->eye_quaternion, &route_one.eye_quaternion, &route_two.eye_quaternion, t2);
			D3DXVec3Lerp(&this->player_rotation, &route_one.player_rotation, &route_two.player_rotation, t2);
			D3DXQuaternionSlerp(&this->player_quaternion, &route_one.player_quaternion, &route_two.player_quaternion, frame);
		}
	};
};

