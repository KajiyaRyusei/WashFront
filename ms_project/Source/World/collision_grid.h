//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// �Փ˔���p�i�q : XZ
// 
// Created by Ryusei Kajiya on 20151028
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//*****************************************************************************
// ���d�C���N���[�h�h�~
#pragma once

//*****************************************************************************
// include
#include "World/grid_2D.h"

//*****************************************************************************
// �O���錾
class Unit;

//*****************************************************************************
// �N���X�݌v
class CollisionGrid : public Grid2D
{
public:

	CollisionGrid(){}

	virtual ~CollisionGrid(){}

	// ���j�b�g�̑���
	virtual void HandleUnit(Unit* unit, Unit* other_unit) override;

	// �f�o�b�O�p�`��
	void DebugDraw();

private:

	// ���Ƌ�
	void Sphrere2Sphere(Unit* unit, Unit* other_unit);

	// ���ƃ{�b�N�X
	// ���m�ɂ�XZ�̉~�Ɖ~
	void Sphrere2Box(Unit* unit, Unit* other_unit);

	// ����box
	void Line2Box(Unit* unit, Unit* other_unit);

	// ���b�V���|�C���g�Ƌ�
	void MeshPoint2Sphrere(Unit* unit, Unit* other_unit);
};
