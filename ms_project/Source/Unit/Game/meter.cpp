//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// メーター
// 
// Created by Chiharu Kamiyama on 20151111
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//*****************************************************************************
// include
#include "meter.h"
#include "Unit/Game/meter_frame.h"
#include "Unit/Game/meter_water.h"


//=============================================================================
// 初期化
void Meter::Initialize()
{
}


//=============================================================================
// 終了
void Meter::Finalize()
{

}

//=============================================================================
// 更新
void Meter::Update()
{	

}

//=============================================================================
// 描画
void Meter::Draw()
{
}

//=============================================================================
// 当たり判定
void Meter::CollisionUpdate()
{
}


//=============================================================================
//リストセット
void Meter::SetMeterCharacterList(std::list<Unit*> *list)
{
	//メーター水をリストに登録
	_meter_water = new MeterWater(_application, _game_world);
	list->push_back(_meter_water);

	//メーター枠をリストに登録
	_meter_frame = new MeterFrame(_application, _game_world);
	list->push_back(_meter_frame);


}