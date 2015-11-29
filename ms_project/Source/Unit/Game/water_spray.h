//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// 水しぶき
// 
// Created by Ryusei Kajiya on 20151125
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//*****************************************************************************
// 多重インクルード防止
#pragma once

//*****************************************************************************
// クラス設計
class WaterSpray
{
public:
	WaterSpray();

	WaterSpray* GetNext() const { return _state._next; }
	void SetNext(WaterSpray* next){ _state._next = next; }
	// 初期化
	void Initialize(
		const D3DXVECTOR3& position,
		const fx32 rotation);
	// アニメーション
	bool Animate(D3DXMATRIX& matrix);
	// 使用しているか
	bool IsUse()const;

private:

	fx32 _frame;

	union
	{
		struct
		{
			D3DXVECTOR3 _position;
			fx32 _rotation;
			D3DXVECTOR3 _scale;
		};
		WaterSpray* _next;
	}_state;

};