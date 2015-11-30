//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// 
// �E�B���h�E�v���V�[�W��
// 
// Created by Ryusei Kajiya on 20151005
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//*****************************************************************************
// �C���N���[�h
#include "window_procedure.h"
#include "window_operation_wrapper.h"

//*****************************************************************************
// �N���X�݌v
LRESULT CALLBACK WindowProcedure(
	HWND handle_window,
	UINT message,
	WPARAM w_paramater,
	LPARAM l_paramater)
{
	switch (message)
	{
		case WM_CREATE:
		{
			// window��^��
			wow::WindowCenter(handle_window);
			// �h���b�O�h���b�v��L���ɂ���
			DragAcceptFiles(handle_window, TRUE);

			break;
		}
		case WM_DESTROY:
		{
			// �V�X�e���ɏI����v��
			PostQuitMessage(0);
			break;
		}
		case WM_CLOSE:
		{
			// �w�肳�ꂽ�E�B���h�E��j��
			DestroyWindow(handle_window);
			break;
		}
		case WM_DROPFILES:
		{
			// �h���b�O�����ʒu���擾
			POINT mouse_position;
			GetCursorPos(&mouse_position);
			 ScreenToClient(
				 handle_window,		// �E�B���h�E�̃n���h��
				 &mouse_position);	// �X�N���[�����W

			 // �h���b�O�����t�@�C�������擾
			 HDROP drop = (HDROP)w_paramater;
			 char file_name[256];
			 DragQueryFileA(drop, 0, file_name, 256);
			 DragFinish(drop);

			 break;
		}
		
		case WM_LBUTTONDOWN:
		{

			break;
		}
		case WM_KEYDOWN:
		{
			switch (w_paramater)
			{
				case VK_ESCAPE:
					DestroyWindow(handle_window);
				break;
			}
			break;
		}
	}

	// �f�t�H���g�̏�����Ԃ�
	return DefWindowProc(handle_window, message, w_paramater, l_paramater);
}
