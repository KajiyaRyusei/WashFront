//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// �v���C���[�ւ̃R�}���h
//
// Created by Ryusei Kajiya on 20151204
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//*****************************************************************************
// ���d�C���N���[�h�h�~
#pragma once

//*****************************************************************************
// �O���錾
class PlayerUnit;

//*****************************************************************************
// �N���X�݌v
class Command
{
public:

	enum CONTROLLER_TYPE
	{
		CONTROLLER_TYPE_1P = 0,
		CONTROLLER_TYPE_2P = 8
	};

	Command(){}
	virtual ~Command(){}

	virtual void Execute(PlayerUnit* player) = 0;

	void PressPower(const s32 power){ _power = power; }

protected:

	s32 _power;

};