//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// 
// 衝突判定関数群
// 
// Created by Ryusei Kajiya on 20151123
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//*****************************************************************************
// 多重インクルード防止
#pragma once

//*****************************************************************************
// 衝突判定関数群
namespace collision
{
	// 矩形と矩形の衝突判定
	bool Rect2Rect(
		const D3DXVECTOR2 &p1,	// 矩形�@左上の座標
		const D3DXVECTOR2 &s1,	// 矩形�@大きさ
		const D3DXVECTOR2 &p2,	// 矩形�A左上の座標
		const D3DXVECTOR2 &s2);	// 矩形�A大きさ


	// 点と三角形の衝突判定
	bool Point2Trigangle(
		const D3DXVECTOR3& point,		// 点
		const D3DXVECTOR3& point_one,	// 三角形の座標1
		const D3DXVECTOR3& point_two,	// 三角形の座標2
		const D3DXVECTOR3& point_three);// 三角形の座標3

	// 線と三角形の衝突判定
	bool Line2Trigangle(
		D3DXVECTOR3* impact_point,		// 衝突してる場所
		const D3DXVECTOR3& start_point,	// 線分の始点
		const D3DXVECTOR3& end_point,	// 線分の終点
		const D3DXVECTOR3& point_one,	// 三角形の座標1
		const D3DXVECTOR3& point_two,	// 三角形の座標2
		const D3DXVECTOR3& point_three);// 三角形の座標3

	// 線と四角形の衝突
	bool Line2Square(
		D3DXVECTOR3* impact_point,		// 衝突してる場所
		const D3DXVECTOR3& start_point,	// 線分の始点
		const D3DXVECTOR3& end_point,	// 線分の終点
		const D3DXVECTOR3& point_one,	// 四角形の座標1
		const D3DXVECTOR3& point_two,	// 四角形の座標2
		const D3DXVECTOR3& point_three,	// 四角形の座標3
		const D3DXVECTOR3& point_four);	// 四角形の座標3

	// 線と立方体の衝突
	bool Line2Box(
		D3DXVECTOR3* impact_point,		// 衝突してる場所
		const D3DXVECTOR3& start_point,	// 線分の始点
		const D3DXVECTOR3& end_point,	// 線分の終点
		const D3DXVECTOR3& ltf,			// ←↑前
		const D3DXVECTOR3& rtf,			// →↑前
		const D3DXVECTOR3& lbf,			// ←↓前
		const D3DXVECTOR3& rbf,			// →↓前
		const D3DXVECTOR3& ltb,			// ←↑後
		const D3DXVECTOR3& rtb,			// →↑後
		const D3DXVECTOR3& lbb,			// ←↓後
		const D3DXVECTOR3& rbb);		// →↓後

	// 球と球の衝突判定
	bool Sphrere2Sphrere(
		const D3DXVECTOR3& point_one,	// 球の中心�@
		const D3DXVECTOR3& point_two,	// 球の中心�A
		const fx32 radius_one,			// 球の半径�@
		const fx32 radius_two);			// 球の半径�A

	// 立方体と立方体の衝突判定
	bool Box2Box(
		const D3DXVECTOR3& p1,	// 立方体�@の中心
		const D3DXVECTOR3& s1,	// 立方体�@の１辺の半分の大きさ
		const D3DXVECTOR3& p2,	// 立方体�Aの中心
		const D3DXVECTOR3& s2);	// 立方体�Aの１辺の半分の大きさ

	// 球と点
	bool Sphrere2Point(
		const D3DXVECTOR3& sphrere_center,	// 球の中心
		const D3DXVECTOR3& point,			// 点
		const fx32 radius);					// 球の半径

};