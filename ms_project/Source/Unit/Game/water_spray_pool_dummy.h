//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// �����Ԃ��̃I�u�W�F�N�g�v�[���̃_�~�[
// 
// Created by Ryusei Kajiya on 20151128
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//*****************************************************************************
// ���d�C���N���[�h�h�~
#pragma once

//*****************************************************************************
// include
#include "Unit/unit.h"
#include "water_spray_pool.h"

//*****************************************************************************
// �N���X�݌v
class WaterSprayPoolDummy : public WaterSprayPool
{
public:
	WaterSprayPoolDummy(Application* application, World* world) : WaterSprayPool(application, world)
	{
		UNREFERENCED_PARAMETER(application);
		UNREFERENCED_PARAMETER(world);
	}

	virtual ~WaterSprayPoolDummy(){}

	// �쐬
	virtual void Create(
		const D3DXVECTOR3& position,
		const fx32 rotation) override
	{
		UNREFERENCED_PARAMETER(position);
		UNREFERENCED_PARAMETER(rotation);
	}

	// �A�j���[�V����:�`������˂Ă�B
	virtual void Animate()override{}

	virtual void Initialize() override{}
	virtual void Finalize() override{}
	virtual void Update() override{}
	virtual void Draw() override{}
	virtual void CollisionUpdate() override{}
};
