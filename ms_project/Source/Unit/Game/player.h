//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// �v���C���[
// 
// Created by Ryusei Kajiya on 20151029
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
class ShaderPBLAnimation;
class AnimationSystem;
class AimUnit;
class CommandHandler;
class WeaponUnit;
class WaterBackUnit;

//*****************************************************************************
// �N���X�݌v
class PlayerUnit : public Unit
{
	friend class CommandMoveFront;
	friend class CommandMoveBack;
	friend class CommandMoveRight;
	friend class CommandMoveLeft;
	friend class CommandMoveUp;
	friend class CommandMoveDown;
	friend class CommandFire;

public:

	PlayerUnit(Application* application, World* world) : Unit(application, world)
	{
		Initialize();
	}
	virtual ~PlayerUnit(){ Finalize(); }

	virtual void Initialize() override;
	virtual void Finalize() override;
	virtual void Update() override;
	virtual void Draw() override;
	virtual void CollisionUpdate() override;

	// �f�o�b�O�p�ړ�
	void DebugMove(const float velocity);

private:

	// �V�F�[�_�[
	ShaderPBLAnimation* _shader;
	// �V�F�[�_��:���b�V�����ɍ��킹��
	u32 _shader_size;
	// �A�j���[�V����
	data::ObjectAnimationFile _animation;
	// �A�j���[�V�����V�X�e��
	AnimationSystem* _animation_system;
	// �V�F�[�_�p�����[�^�[�̐ݒ�
	void SettingShaderParameter();
	data::World _world;
	D3DXMATRIX _matrix_world_view_projection;

	// aim
	AimUnit* _aim;
	void AimUpdate();

	// �R�}���h
	CommandHandler* _command_handler;

	// ����
	WeaponUnit* _weapon;

	// ��됅
	WaterBackUnit* _back_water;

	// �ړ��p�X
	static const s32 kMaxPass = 4;
	D3DXVECTOR3 _pass_point_list[kMaxPass];
	fx32 _pass_frame;
	fx32 _lower_body_rotation;
	// �p�X�v�Z
	void PassRootDecision();

	// �����g�̕����𐧌�
	D3DXVECTOR3 _front_vector;
	void LowerBodyControl();

	
};