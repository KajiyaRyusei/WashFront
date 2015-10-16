//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// �V�X�e���̗���
//
// Created by Ryusei Kajiya on 20151006
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//*****************************************************************************
// �C���N���[�h
#include "system_flow.h"
#include "application.h"
#include "Windows/window.h"
#include "Renderer/directx9.h"

//*****************************************************************************
// �萔
namespace
{
	static const fx32 kFrameRate = 1000.0f / 60.0f;
}

//=============================================================================
// ������
void SystemFlow::Initialize(const HINSTANCE handle_instance)
{
	// �E�B���h�E�̐���
	_main_window = new Window(handle_instance);
	// �����_���\�̐���
	_renderer_device = new RendererDevice(_main_window->GetHandleWindow(), _main_window->GetSizeWindowWidth(), _main_window->GetSizeWindowHeight(),false);
	// �Q�ƌQ�ɓo�^
	Reference::GetInstance().SetRenderer(_renderer_device);
	// �A�v���P�[�V�����̐���
	_applicaion = new Application(_main_window,_renderer_device);

	
}
//=============================================================================
// �I��
void SystemFlow::Finalize()
{
	SafeDelete(_applicaion);
	SafeDelete(_renderer_device);
	SafeDelete(_main_window);
}
//=============================================================================
// ���b�Z�[�W���[�v
void SystemFlow::MessageLoop()
{
	// ����\��ݒ�
	timeBeginPeriod(1);

	u64 exec_last_time = timeGetTime();
	u64 fps_last_time = timeGetTime();
	u64 current_time = 0;
	u64 frame_count = 0;
	u64 fps_count = 0;

	MSG message;
	bool no_exit = true;

	while( no_exit )
	{
		if (PeekMessage(
			&message,	// ���b�Z�[�W���
			nullptr,	// �E�B���h�E�n���h��
			0,			// �ŏ��̃��b�Z�[�W
			0,			// �Ō�̃��b�Z�[�W
			PM_REMOVE))	// ���b�Z�[�W������������ɁA���̃��b�Z�[�W���L���[����폜
		{// ���b�Z�[�W����M������
			if (message.message == WM_QUIT)
			{// PostQuitMessage()���Ă΂ꂽ�烋�[�v�I��
				no_exit = false;
			}
			else
			{// ���b�Z�[�W�̖|��Ƒ��o
				TranslateMessage(&message);
				DispatchMessage(&message);
			}
		}
		else
		{// �ʏ�̃��[�v
			current_time = timeGetTime();
			if (current_time - fps_last_time >= 500)
			{// 0.5�b���ƂɎ��s(fps�̊m�F)
				fps_count = frame_count * 1000 / (current_time - fps_last_time);
				fps_last_time = current_time;
				frame_count = 0;
			}

			if (current_time - exec_last_time >= 1000 / 60)
			{// fps����
				exec_last_time = current_time;

				// �X�V
				_applicaion->Update();

				// �`��
				_applicaion->Draw();

				frame_count = 0;
			}
		}
	}
	timeEndPeriod(1);
}
