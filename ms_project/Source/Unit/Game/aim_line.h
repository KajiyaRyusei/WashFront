//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// AIM�̐�
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
// �N���X�݌v
class AimLineUnit : public Unit
{
public:
	AimLineUnit(Application* application, World* world) : Unit(application, world)
	{
		Initialize();
	}
	virtual ~AimLineUnit(){ Finalize(); }

	virtual void Initialize() override;
	virtual void Finalize() override;
	virtual void Update() override;
	virtual void Draw() override;
	virtual void CollisionUpdate() override;
	virtual void CollisionLine(const D3DXVECTOR3& impact_point) override;

	// ���C���̎n�_�ݒ�
	void SetStartPosition(const D3DXVECTOR3& position)
	{
		_position.current = position;
		_line->start_point = position;
	}
	// ���C���̏I�_�ݒ�
	void SetEndPosition(const D3DXVECTOR3& position)
	{
		_line->end_point = position;
	}

	// ���C���̎n�_���擾
	D3DXVECTOR3& GetStartPosition()
	{
		return _line->start_point;
	}

	// ���C���̏I�_���擾
	D3DXVECTOR3& GetEndPosition()
	{
		return _line->end_point;
	}

	
};
