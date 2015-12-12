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
class ShaderToonWeapon;
class BulletUnit;
class WaterBulletUnit;
class PlayerUnit;

//*****************************************************************************
// ���탌�x��
enum WEAPON_LEVEL
{
	WEAPON_LEVEL_ONE =0,
	WEAPON_LEVEL_TWO,
	WEAPON_LEVEL_THREE,
};

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
		const D3DXMATRIX& world,
		const D3DXMATRIX& animation);

	// ����
	void Fire(
		const D3DXVECTOR3& start,
		const D3DXVECTOR3& end);

	// �Z�b�g�v���C���[
	void SetPlayer(PlayerUnit* player);

	// ���탌�x���A�b�v
	void WeaponLevel(WEAPON_LEVEL level);

private:

	ShaderToonWeapon* _shader;
	u32 _shader_size;
	data::World _world;
	D3DXMATRIX _matrix_world_view_projection;
	D3DXMATRIX _animation_matrix;
	// �V�F�[�_�p�����[�^�[�̐ݒ�
	void SettingShaderParameter();

	// �e
	BulletUnit* _bullet;
	WaterBulletUnit* _water_bullet;
	WEAPON_LEVEL _level;

};