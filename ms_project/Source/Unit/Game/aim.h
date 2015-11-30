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

//*****************************************************************************
// �N���X�݌v
class AimUnit : public Unit
{
public:

	AimUnit(Application* application, World* world) : Unit(application, world)
	{
		Initialize();
	}
	virtual ~AimUnit(){ Finalize(); }

	virtual void Initialize() override;
	virtual void Finalize() override;
	virtual void Update() override;
	virtual void Draw() override;
	virtual void CollisionUpdate() override;

	// ���C���̎n�_�ݒ�
	void SetStartPosition(const D3DXVECTOR3& position);

	// ���C���̏I�_�ݒ�
	void SetEndPosition(const D3DXVECTOR3& position);

	// ���C���̎n�_���擾
	D3DXVECTOR3& GetStartPosition();

	// ���C���̏I�_���擾
	D3DXVECTOR3& GetEndPosition();

private:

	// �`��pAIM
	AimDrawUnit* _aim_draw;
	AimLineUnit* _aim_line;
};