//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// �V�X�e���̗���
//
// Created by Ryusei Kajiya on 20151006
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//*****************************************************************************
// ���d�C���N���[�h�h�~
#pragma once

//*****************************************************************************
// �O���錾
class Window;
class Application;
class RendererDevice;

//*****************************************************************************
// �N���X�݌v
class SystemFlow
{
public:

	SystemFlow() :
		_main_window{ nullptr },
		_applicaion{ nullptr },
		_renderer_device{ nullptr }
	{}

	virtual ~SystemFlow(){ Finalize(); }

	// ������
	void Initialize(const HINSTANCE handle_instance);

	// �I��
	void Finalize();

	// ���b�Z�[�W���[�v
	void MessageLoop();

private:

	Window *_main_window;
	Application *_applicaion;
	RendererDevice *_renderer_device;
};