//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// �^�C�g���v���C���[
// 
// Created by Ryusei Kajiya on 20151212
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//*****************************************************************************
// ���d�C���N���[�h�h�~
#pragma once

//*****************************************************************************
// include
#include "Unit/unit.h"
#include "Data/data_oaf.h"
#include "Data/data_world.h"

//*****************************************************************************
// �O���錾
class ShaderToonPlayer;
class AnimationSystem;
class WaterBackUnit;
class TitleWeaponUnit;

//*****************************************************************************
// �N���X�݌v
class TitlePlayerUnit : public Unit
{
public:

	TitlePlayerUnit(Application* application, World* world) : Unit(application, world)
	{
		Initialize();
	}
	virtual ~TitlePlayerUnit(){ Finalize(); }

	virtual void Initialize() override;
	virtual void Finalize() override;
	virtual void Update() override;
	virtual void Draw() override;
	virtual void CollisionUpdate() override{};

private:

	// �V�F�[�_�[
	ShaderToonPlayer* _shader;
	// �V�F�[�_��:���b�V�����ɍ��킹��
	u32 _shader_size;
	// �A�j���[�V����
	data::ObjectAnimationFile* _statnce_animation;
	// �A�j���[�V�����V�X�e��
	AnimationSystem* _statnce_animation_system;

	// �V�F�[�_�p�����[�^�[�̐ݒ�
	void SettingShaderParameter();
	data::World _world;
	D3DXMATRIX _matrix_world_view_projection;
	// ��됅
	WaterBackUnit* _back_water;
	// ����
	TitleWeaponUnit* _weapon;

	// ���ƃA�j���[�V���������킹��
	void CompositionWater2Animation(const D3DXMATRIX* matrices);
};