//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// ��됅
// 
// Created by Ryusei Kajiya on 20151123
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//*****************************************************************************
// ���d�C���N���[�h�h�~
#pragma once

//*****************************************************************************
// include
#include "Unit/unit.h"
#include "Data/data_world.h"

//*****************************************************************************
// �O���錾
class ShaderWaterBack;

//*****************************************************************************
// �N���X�݌v
class WaterBackUnit : public Unit
{
public:

	WaterBackUnit(Application* application, World* world) : Unit(application, world)
	{
		Initialize();
	}
	virtual ~WaterBackUnit(){ Finalize(); }

	virtual void Initialize() override;
	virtual void Finalize() override;
	virtual void Update() override;
	virtual void Draw() override;
	virtual void CollisionUpdate() override;

	// ���W�̐ݒ�
	void SetPosition(const D3DXVECTOR3& position);

private:

	// �V�F�[�_�[
	ShaderWaterBack* _shader;
	// �V�F�[�_�p�����[�^�[�̐ݒ�
	void SettingShaderParameter();
	data::World _world;
	D3DXMATRIX _matrix_world_view_projection;
	D3DXMATRIX _animation_matrix;
	D3DXMATRIX _player_rotation_matrix;
};