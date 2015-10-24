//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// 
// 個人的によく使う関数群
// 
// Created by Ryusei Kajiya on 20151022
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//*****************************************************************************
// 多重インクルード防止
#pragma once

//*****************************************************************************
// 前方宣言
class Camera;

//*****************************************************************************
// よく使う関数群
namespace algo
{
	//====================================
	// ワールドビュープロジェクションの作成
	D3DXMATRIX& CreateWVP(
		D3DXMATRIX& world_view_projection,
		const D3DXMATRIX& world,
		const Camera* camera);

	//====================================
	// ワールド行列の作成
	D3DXMATRIX& CreateWorld(
		D3DXMATRIX& world,
		const D3DXVECTOR3& position,
		const D3DXVECTOR3& rotation,
		const D3DXVECTOR3& scale);

	//====================================
	// ワールドの方向をローカルに合わせる
	D3DXVECTOR4& CreateLocalDirection(
		D3DXVECTOR4& inverse_vector,
		const D3DXVECTOR4& vector,
		const D3DXMATRIX& world);

}

