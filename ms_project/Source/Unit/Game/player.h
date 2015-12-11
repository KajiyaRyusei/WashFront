//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// �v���C���[
// 
// Created by Ryusei Kajiya on 20151207
//
//<��邱��>
// �J�����̃��[�g�ɍ��킹��
// �A�j���[�V�����ɐ������킹��FCPU�Ōv�Z
// �V�F�[�_�̃X�y�L�����폜
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//*****************************************************************************
// ���d�C���N���[�h�h�~
#pragma once

//*****************************************************************************
// include
#include "Unit/unit.h"
#include "Data/data_oaf.h"
#include "Data/data_world.h"
#include "Data/data_velocity.h"

#include "Command/command_handler.h"

//*****************************************************************************
// �O���錾
class ShaderToonPlayer;
class AnimationSystem;
class AimUnit;
class CommandHandler;
class WeaponUnit;
class WaterBackUnit;
class CameraGamePlayer;

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
	friend class CommandMove;

public:

	PlayerUnit(Application* application, World* world, CameraGamePlayer* camera) : Unit(application, world),
		_player_camera(camera)
	{
		Initialize();
	}
	virtual ~PlayerUnit(){ Finalize(); }

	virtual void Initialize() override;
	virtual void Finalize() override;
	virtual void Update() override;
	virtual void Draw() override;
	virtual void CollisionUpdate() override;

	// �v���C���[�̍��W���擾�F���낢��ƌv�Z������o�[�W����
	// ���傢��O
	const D3DXVECTOR3 GetPosition();

	void SetControllerType(Command::CONTROLLER_TYPE type){ _controller_type = type; }

	CameraGamePlayer* GetPlayerCamera()const{ return _player_camera; }

private:

	// �V�F�[�_�[
	ShaderToonPlayer* _shader;
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
	// �v���C���[�p�J����
	CameraGamePlayer* _player_camera;
	// �R���g���[���[�^�C�v
	Command::CONTROLLER_TYPE _controller_type;

	// ���ƃA�j���[�V���������킹��
	void CompositionWater2Animation(const D3DXMATRIX* matrices);
	// ���W�ƌ����ݒ�
	void PassRootDecision();

};