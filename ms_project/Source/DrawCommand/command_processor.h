//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// �R�}���h�v���Z�b�T
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
class CommandProcessor
{
public:

	explicit CommandProcessor(const CommandBuffer& command_buffer) :
		_command_buffer(command_buffer){}

	~CommandProcessor(){}

	// �`�揈�����s���B
	void ProccessLightDepth(void) const;
	void ProccessDefault(void) const;
	void ProccessShadow(void) const;
	void ProccessField(void) const;
	void ProccessBackGround(void) const;
	void ProccessTranslucent(void) const;
	void ProccessAIM(void) const;
	void Proccess2D(void) const;

private:

	// �R�s�[�֎~
	CommandProcessor& operator=(const CommandProcessor& rhs);

	// ��L�̃v���Z�X�����̖{��
	void Proccess(u32 render_state_paramater) const;

	const CommandBuffer& _command_buffer;
};