//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// �`��pAIM
// 
// Created by Ryusei Kajiya on 20151102
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
class ShaderAim;

//*****************************************************************************
// �N���X�݌v
class AimDrawUnit : public Unit
{
public:
	AimDrawUnit(Application* application, World* world) : Unit(application, world)
	{
		Initialize();
	}
	virtual ~AimDrawUnit(){ Finalize(); }

	virtual void Initialize() override;
	virtual void Finalize() override;
	virtual void Update() override;
	virtual void Draw() override;
	virtual void CollisionUpdate() override{};

	void SetEndPosition(const D3DXVECTOR3& position)
	{
		_world.position = position;
	}

	void SetHit(const bool is_hit)
	{
		_is_hit = is_hit;
	}

private:

	// �V�F�[�_�[
	ShaderAim* _shader;

	// ���[���h
	data::World _world;
	D3DXMATRIX _matrix_world_view_projection;

	bool _is_hit;

	// �����̈ʒu���Z�o
	void CalculatePosition();
};