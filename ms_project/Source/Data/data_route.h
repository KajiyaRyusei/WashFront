//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// ルートのデータ
//
// Created by Ryusei Kajiya on 20151204
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//*****************************************************************************
// 多重インクルード防止
#pragma once

namespace data
{
	//*****************************************************************************
	// 構造体定義
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

		// ルートの補間
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

