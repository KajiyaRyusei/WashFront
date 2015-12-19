//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// ���e
// 
// Created by Ryusei Kajiya on 20151111
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
class ShaderWater;
class PlayerUnit;

//*****************************************************************************
// �N���X�݌v
class WaterBulletUnit : public Unit
{
public:

	WaterBulletUnit(Application* application, World* world) : Unit(application, world)
	{
		Initialize();
	}
	virtual ~WaterBulletUnit(){ Finalize(); }

	virtual void Initialize() override;
	virtual void Finalize() override;
	virtual void Update() override;
	virtual void Draw() override;
	virtual void CollisionUpdate() override;


	// ����
	void Fire(const D3DXVECTOR3& end);

	// �Z�b�g�v���C���[
	void SetPlayer(PlayerUnit* player){ _player = player; }

	// �A���r�G���g�J���[�ύX
	void ReNewAmbientColor(const D3DXVECTOR4& ambient){ _ambient = ambient; }

private:

	// �V�F�[�_�[
	ShaderWater* _shader;
	// �V�F�[�_�p�����[�^�[�̐ݒ�
	void SettingShaderParameter();
	data::World _world;
	D3DXMATRIX _matrix_world_view_projection;
	D3DXMATRIX _matrix_water[3];

	// �e�̃p�����[�^
	D3DXVECTOR3 _start_point;
	D3DXVECTOR3 _end_point;
	D3DXVECTOR3 _control_point;
	fx32 _rotation_y;
	fx32 _destination_release_of;
	fx32 _release_of;
	D3DXVECTOR4 _ambient;

	// �v���C���[
	PlayerUnit* _player;
};