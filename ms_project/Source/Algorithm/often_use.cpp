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

}