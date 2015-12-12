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

//*****************************************************************************
// �N���X�݌v
class TitleWeaponUnit : public Unit
{
public:

	TitleWeaponUnit(Application* application, World* world) : Unit(application, world)
	{
		Initialize();
	}
	virtual ~TitleWeaponUnit(){ Finalize(); }

	virtual void Initialize() override;
	virtual void Finalize() override;
	virtual void Update() override;
	virtual void Draw() override;
	virtual void CollisionUpdate() override;

	// ���W�̐ݒ�
	void SetPosition(
		const D3DXMATRIX& world,
		const D3DXMATRIX& animation);



private:

	ShaderToonWeapon* _shader;
	u32 _shader_size;
	data::World _world;
	D3DXMATRIX _matrix_world_view_projection;
	D3DXMATRIX _animation_matrix;
	// �V�F�[�_�p�����[�^�[�̐ݒ�
	void SettingShaderParameter();

};