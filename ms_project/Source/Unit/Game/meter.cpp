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

//�萔
namespace
{
	static const D3DXVECTOR4 kOverHeatColor(1.f, 0.f, 0.f, 1.f);
	static const D3DXVECTOR4 kNormalColor(1.f,1.f, 1.f, 1.f);
	static const fx32 kRotationAdd(0.1f);
}

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
	for( u32 i = 0; i < 2;++i )
	{
		if( _meter[i]._meter_water->IsOverHeat() )
		{
			_meter[i]._meter_frame->SelectColor(kOverHeatColor);
			_meter[i]._meter_gear->SelectColor(kOverHeatColor);
		}
		else
		{
			_meter[i]._meter_frame->SelectColor(kNormalColor);
			_meter[i]._meter_gear->SelectColor(kNormalColor);
			_meter[i]._meter_gear->AddRotation(kRotationAdd);
		}
		
	}
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
	for( int i = 0; i < 2; i++ )
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
//���[�^�[���ʍX�V
void Meter::UpdateMeterWaterAdd(int player_id, float amount)
{
	_meter[player_id]._meter_water->UpdateMeterWaterAdd(amount);
}

//=============================================================================
//���[�^�[���x���X�V
void Meter::UpdateMeterLevel(int player_id, int level)
{
	_meter[player_id]._meter_level->UpdateWaerLevel(level);
}

//=============================================================================
//���[�^�[���ʍX�V
void Meter::MaxWaterMeter(int player_id, float max_water)
{
	//���ʍX�V
	_meter[player_id]._meter_water->LevelUpMeterWater(max_water);
}

//=============================================================================
//���[�^�[���ʎ擾
float Meter::GetCurrentMeterWater(int player_id)
{
	return _meter[player_id]._meter_water->GetCurrentWater();
}


