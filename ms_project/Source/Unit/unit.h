//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// ���j�b�g
// 
// Created by Ryusei Kajiya on 20151009
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//*****************************************************************************
// ���d�C���N���[�h�h�~
#pragma once

//*****************************************************************************
// include
#include "DrawCommand/command_buffer_holder.h"

//*****************************************************************************
// �O���錾
class Application;
class SpaceGrid;

//*****************************************************************************
// �N���X�݌v
class Unit : public CommandBufferHolder
{
	friend class SpaceGrid;

public:

	Unit(Application* application, SpaceGrid* grid);
	virtual ~Unit(){}

	virtual void Initialize() = 0;
	virtual void Finalize() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;

	// �V�[���̐؂�ւ����ɌĂяo���Ă��������B
	static void ResetID(){ s_unit_id = 0; }

	// �����̃I�u�W�F�N�gID : Unit�P�ɂ��P��
	u32 GetID() const { return _id; }

protected:
	Application* _application;
	D3DXVECTOR3 _world_position;

private:

	Unit* _next;
	Unit* _previous;
	static u32 s_unit_id;
	u32 _id;
};