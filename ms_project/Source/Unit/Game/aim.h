//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// AIM
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

//*****************************************************************************
// �O���錾
class AimDrawUnit;
class AimLineUnit;
class PlayerUnit;

//*****************************************************************************
// �N���X�݌v
class AimUnit : public Unit
{
public:

	AimUnit(Application* application, World* world) : Unit(application, world),
		_aim_draw(nullptr),
		_aim_line(nullptr),
		_current_rotation(0.f, 0.f, 0.f),
		_destination_rotation(_current_rotation),
		_player(nullptr)
	{
		Initialize();
	}
	virtual ~AimUnit(){ Finalize(); }

	virtual void Initialize() override;
	virtual void Finalize() override;
	virtual void Update() override;
	virtual void Draw() override;
	virtual void CollisionUpdate() override;

	// �v���C���[��ݒ�
	void SetPlayer(PlayerUnit* player){ _player = player; }

	// ��]�̃Z�b�g
	void SetRotation(const D3DXVECTOR3& rotation){ _destination_rotation = rotation; }

	// �_���Ă���ʒu�̎擾
	const D3DXVECTOR3& GetTargetPosition();

	// �Փ˂��Ă��邩
	const bool IsHit() const;

private:

	// �`��pAIM
	AimDrawUnit* _aim_draw;
	AimLineUnit* _aim_line;

	// ���݂̉�]�
	D3DXVECTOR3 _current_rotation;
	D3DXVECTOR3 _destination_rotation;

	// �v���C���[
	PlayerUnit* _player;

	// �ʒu�̌v�Z
	void CalculatePosition();

};