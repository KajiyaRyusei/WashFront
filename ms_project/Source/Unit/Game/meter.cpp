//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// ���[�^�[
// 
// Created by Chiharu Kamiyama on 20151111
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//*****************************************************************************
// include
#include "meter.h"
#include "Unit/Game/meter_frame.h"
#include "Unit/Game/meter_water.h"
#include "Unit/Game/meter_level.h"
#include "Unit/Game/meter_gear.h"
#include "Windows/window.h"


//=============================================================================
// ������
void Meter::Initialize()
{
}


//=============================================================================
// �I��
void Meter::Finalize()
{

}

//=============================================================================
// �X�V
void Meter::Update()
{
/*	
	//���ʍX�V
	UpdateMeterWater(0, 3);

	float water = GetCurrentMeterWater(0);

	//���[�^�[���x���A�b�v
	if (water <= 0.0f)
	{
		UpdateMeterLevel(0, 2, 700);
	}
	*/
}

//=============================================================================
// �`��
void Meter::Draw()
{
}

//=============================================================================
// �����蔻��
void Meter::CollisionUpdate()
{
}


//=============================================================================
//���X�g�Z�b�g
void Meter::SetMeterCharacterList(std::list<Unit*> *list)
{
	float window_height = (float)_application->GetWindow()->GetSizeWindowHeight();

	//���[�^�[�������X�g�ɓo�^
	for (int i = 0; i < 2; i++)
	{
		//���[�^�[���Ԃ����X�g�ɓo�^
		_meter[i]._meter_gear = new MeterGear(_application, _game_world);
		list->push_back(_meter[i]._meter_gear);

		//���[�^�[�������X�g�ɓo�^
		_meter[i]._meter_water = new MeterWater(_application, _game_world);
		list->push_back(_meter[i]._meter_water);

		//���[�^�[�g�����X�g�ɓo�^
		_meter[i]._meter_frame = new MeterFrame(_application, _game_world);
		list->push_back(_meter[i]._meter_frame);

		//���[�^�[���x�������X�g�ɓo�^
		_meter[i]._meter_level = new MeterLevel(_application, _game_world);
		list->push_back(_meter[i]._meter_level);

	}

	float meter_height = window_height - 210.0f / 2;

	_meter[0]._meter_frame->SetPosition(D3DXVECTOR3(85.0f, meter_height + 20.0f, 0.0f));
	_meter[0]._meter_gear->SetPosition(D3DXVECTOR3(85.0f, meter_height + 20.0f, 0.0f));
	_meter[0]._meter_level->SetPosition(D3DXVECTOR3(85.0f, meter_height - 50 + 20.0f, 0.0f));
	_meter[0]._meter_water->SetPosition(D3DXVECTOR3(85.0f, meter_height + 20.0f, 0.0f));
	_meter[0]._meter_water->SetInitPosition(D3DXVECTOR3(85.0f, meter_height + 20.0f, 0.0f));

	float meter_height_center_distance = meter_height - window_height / 2;

	_meter[1]._meter_frame->SetPosition(D3DXVECTOR3(85.0f, meter_height_center_distance, 0.0f));
	_meter[1]._meter_gear->SetPosition(D3DXVECTOR3(85.0f, meter_height_center_distance, 0.0f));
	_meter[1]._meter_level->SetPosition(D3DXVECTOR3(85.0f, meter_height_center_distance - 50, 0.0f));
	_meter[1]._meter_water->SetPosition(D3DXVECTOR3(85.0f, meter_height_center_distance, 0.0f));
	_meter[1]._meter_water->SetInitPosition(D3DXVECTOR3(85.0f, meter_height_center_distance, 0.0f));
}

//=============================================================================
//���[�^�[���ʍX�V
void Meter::UpdateMeterWater(int player_id, float amount)
{
	_meter[player_id]._meter_water->UpdateMeterWater(amount);
}

//=============================================================================
//���[�^�[���ʃ��x���X�V
void Meter::UpdateMeterLevel(int player_id, int level, float water_max)
{
	//���ʍX�V
	_meter[player_id]._meter_water->LevelUpMeterWater(water_max);
	_meter[player_id]._meter_level->UpdateWaerLevel(level);
}

//=============================================================================
//���[�^�[���ʎ擾
float Meter::GetCurrentMeterWater(int player_id)
{
	float water = _meter[player_id]._meter_water->GetCurrentWater();

	return water;
}


