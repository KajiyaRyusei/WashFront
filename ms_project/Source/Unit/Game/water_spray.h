////+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
////
//// 水しぶき
//// 
//// Created by Ryusei Kajiya on 20151125
////
////+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
////*****************************************************************************
//// 多重インクルード防止
//#pragma once
//
////*****************************************************************************
//// クラス設計
//class WaterSpray
//{
//public:
//	WaterSpray* GetNext() const { return _state._next; }
//	void SetNext(WaterSpray* next){ _state._next = next; }
//	// 初期化
//	void Initialize(
//		const D3DXVECTOR3& position,
//		const D3DXQUATERNION& quaternion);
//	// アニメーション
//	bool Animate();
//	// 使用しているか
//	bool IsUse()const { return _frame_left > 0; }
//
//private:
//	u32 _frame_left;
//
//	union
//	{
//		struct
//		{
//			D3DXVECTOR3 _position;
//			D3DXQUATERNION _quaternion;
//			D3DXVECTOR3 _scale;
//		};
//
//		WaterSpray* _next;
//	}_state;
//};