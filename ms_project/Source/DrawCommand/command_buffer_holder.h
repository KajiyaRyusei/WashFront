//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// �R�}���h�o�b�t�@�z���_�[
// 
// Created by Ryusei Kajiya on 20151009
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//*****************************************************************************
// ���d�C���N���[�h�h�~
#pragma once

//*****************************************************************************
// �O���錾
class CommandBuffer;

//*****************************************************************************
// �N���X�݌v
class CommandBufferHolder
{
public:
	virtual ~CommandBufferHolder() {}

	// �~���[�e�[�^
	static void S_SetCommandBuffer(CommandBuffer* command_buffer)
	{
		s_command_buffer = command_buffer;
	}

protected:
	
	// �A�N�Z�T
	static CommandBuffer* S_GetCommandBuffer(void)
	{
		return s_command_buffer;
	}

private:
	static CommandBuffer* s_command_buffer;
};