//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// ����
// 
// Created by Ryusei Kajiya on 20151118
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
class ShaderPBLAnimation;
class BulletUnit;
class WaterBulletUnit;

//*****************************************************************************
// �N���X�݌v
class WeaponUnit : public Unit
{
public:

	WeaponUnit(Application* application, World* world) : Unit(application, world)
	{
		Initialize();
	}
	virtual ~WeaponUnit(){ Finalize(); }

	virtual void Initialize() override;
	virtual void Finalize() override;
	virtual void Update() override;
	virtual void Draw() override;
	virtual void CollisionUpdate() override;

	// ���W�̐ݒ�
	void SetPosition(
		const D3DXVECTOR3& position,
		const D3DXMATRIX& animation);

	// ����
	void Fire(
		const D3DXVECTOR3& start,
		const D3DXVECTOR3& end);

private:

	ShaderPBLAnimation* _shader;
	u32 _sahder_size;
	data::World _world;
	D3DXMATRIX _matrix_world_view_projection;
	D3DXMATRIX _animation_matrix;
	// �V�F�[�_�p�����[�^�[�̐ݒ�
	void SettingShaderParameter();

	// �e
	BulletUnit* _bullet;
	WaterBulletUnit* _water_bullet;

};