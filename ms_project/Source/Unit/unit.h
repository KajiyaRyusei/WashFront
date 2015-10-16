//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// ユニット
// 
// Created by Ryusei Kajiya on 20151009
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//*****************************************************************************
// 多重インクルード防止
#pragma once

//*****************************************************************************
// include
#include "DrawCommand/command_buffer_holder.h"

//*****************************************************************************
// 前方宣言
class Application;
class SpaceGrid;

//*****************************************************************************
// クラス設計
class Unit : public CommandBufferHolder
{
	friend class SpaceGrid;

public:

	Unit(Application* application, SpaceGrid* grid);
	virtual ~Unit(){}

	virtual void Initialize() = 0;
	virtual void Finalize() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;

	// シーンの切り替え時に呼び出してください。
	static void ResetID(){ s_unit_id = 0; }

	// 自分のオブジェクトID : Unit１つにつき１つ
	u32 GetID() const { return _id; }

protected:
	Application* _application;
	D3DXVECTOR3 _world_position;

private:

	Unit* _next;
	Unit* _previous;
	static u32 s_unit_id;
	u32 _id;
};