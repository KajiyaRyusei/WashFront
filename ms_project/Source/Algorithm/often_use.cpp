//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// よく使う関数群
//
// Created by Ryusei Kajiya on 20151022
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//*****************************************************************************
// include
#include "often_use.h"
#include "Camera/camera_manager.h"
#include "Camera/Camera/camera.h"


//*****************************************************************************
// よく使う関数群
namespace algo
{
	//====================================
	// ワールドビュープロジェクションの作成
	D3DXMATRIX& CreateWVP(D3DXMATRIX& world_view_projection,const D3DXMATRIX& world,const Camera* camera)
	{
		world_view_projection = world * camera->GetMatrixView() * camera->GetMatrixProjection();
		return world_view_projection;
	}

	//====================================
	// ワールド行列の作成
	D3DXMATRIX& CreateWorld(
		D3DXMATRIX& world,
		const D3DXVECTOR3& position,
		const D3DXVECTOR3& rotation,
		const D3DXVECTOR3& scale)
	{
		D3DXMATRIX rotation_matrix, scale_matrix, translation_matrix;
		D3DXMatrixRotationYawPitchRoll(&rotation_matrix, rotation.y, rotation.x, rotation.z);
		D3DXMatrixScaling(&scale_matrix, scale.x, scale.y, scale.z);
		D3DXMatrixTranslation(&translation_matrix, position.x, position.y, position.z);

		world = rotation_matrix * scale_matrix * translation_matrix;
		return world;
	}

	//====================================
	// 視線ベクトルの向きをモデルに合わせる
	D3DXVECTOR4& CreateLocalDirection(
		D3DXVECTOR4& inverse_vector,
		const D3DXVECTOR4& vector,
		const D3DXMATRIX& world)
	{
		D3DXMATRIX world_inverse;
		D3DXMatrixInverse(&world_inverse, nullptr, &world);
		D3DXVec4Transform(&inverse_vector, &vector, &world);
		D3DXVec4Normalize(&inverse_vector, &inverse_vector);
		return inverse_vector;
	}

	//====================================
	// ベジェ曲線
	D3DXVECTOR3& BezierCurve2D(
		D3DXVECTOR3& out_point,
		const D3DXVECTOR3& start_point,
		const D3DXVECTOR3& end_point,
		const D3DXVECTOR3& control_point,
		const fx32 frame)
	{
		out_point.x = (1 - frame) * (1 - frame) * start_point.x + 2 * (1 - frame) *frame * control_point.x + frame * frame * end_point.x;
		out_point.y = (1 - frame) * (1 - frame) * start_point.y + 2 * (1 - frame) *frame * control_point.y + frame * frame * end_point.y;
		out_point.z = (1 - frame) * (1 - frame) * start_point.z + 2 * (1 - frame) *frame * control_point.z + frame * frame * end_point.z;

		return out_point;
	}

	//====================================
	// 頂点座標とUVから接ベクトルと従法線を求める
	void ComputeTangentAndBinormal(
		const D3DXVECTOR3 &position_one,
		const D3DXVECTOR3 &position_two,
		const D3DXVECTOR3 &position_three,
		const D3DXVECTOR2 &texcoord_one,
		const D3DXVECTOR2 &texcoord_two,
		const D3DXVECTOR2 &texcoord_three,
		D3DXVECTOR3* tangent,
		D3DXVECTOR3* binormal)
	{
		// 5次元を3次元に
		D3DXVECTOR3 p1t1[3] = 
		{
			D3DXVECTOR3(position_one.x, texcoord_one.x, texcoord_one.y),
			D3DXVECTOR3(position_one.y, texcoord_one.x, texcoord_one.y),
			D3DXVECTOR3(position_one.z, texcoord_one.x, texcoord_one.y)
		};

		D3DXVECTOR3 p2t2[3] =
		{
			D3DXVECTOR3(position_two.x, texcoord_two.x, texcoord_two.y),
			D3DXVECTOR3(position_two.y, texcoord_two.x, texcoord_two.y),
			D3DXVECTOR3(position_two.z, texcoord_two.x, texcoord_two.y)
		};

		D3DXVECTOR3 p3t3[3] =
		{
			D3DXVECTOR3(position_three.x, texcoord_three.x, texcoord_three.y),
			D3DXVECTOR3(position_three.y, texcoord_three.x, texcoord_three.y),
			D3DXVECTOR3(position_three.z, texcoord_three.x, texcoord_three.y)
		};

		// 平面パラメータからUV軸座標算出
		fx32 u[3], v[3];

		for( u32 i = 0; i < 3; ++i )
		{
			D3DXVECTOR3 v1 = p2t2[i] - p1t1[i];
			D3DXVECTOR3 v2 = p3t3[i] - p2t2[i];
			D3DXVECTOR3 abc;
			D3DXVec3Cross(&abc,&v1,&v2);

			if( abc .x == 0.f)
			{// 縮退
				*tangent = D3DXVECTOR3(0.f, 0.f, 0.f);
				*binormal = D3DXVECTOR3(0.f, 0.f, 0.f);
				return;
			}
			u[i] = -abc.y / abc.x;
			v[i] = -abc.z / abc.x;
		}

		*tangent = D3DXVECTOR3(u[0], u[1], u[2]);
		*binormal = D3DXVECTOR3(v[0], v[1], v[2]);

		// 正規化
		D3DXVec3Normalize(tangent,tangent);
		D3DXVec3Normalize(binormal, binormal);
	}

}