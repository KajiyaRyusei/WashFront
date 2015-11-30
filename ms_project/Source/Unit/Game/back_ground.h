//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// �w�i�p�V��
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
#include "Data/data_projection.h"

//*****************************************************************************
// �O���錾
class ShaderBackGround;

//*****************************************************************************
// �N���X�݌v
class BackGroundUnit : public Unit
{
public:

	BackGroundUnit(Application* application, World* world) : Unit(application, world)
	{
		Initialize();
	}
	virtual ~BackGroundUnit(){ Finalize(); }

	virtual void Initialize() override;
	virtual void Finalize() override;
	virtual void Update() override;
	virtual void Draw() override;
	virtual void CollisionUpdate() override{};
private:

	// �V�F�[�_�[
	ShaderBackGround* _shader;

};