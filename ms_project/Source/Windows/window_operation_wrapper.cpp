//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// 
// �E�B���h�E�ɑ΂��鑀��̃��b�p�[�Q
// 
// Created by Ryusei Kajiya on 20151005
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//*****************************************************************************
// �C���N���[�h
#include "window_operation_wrapper.h"

namespace wow
{
	//====================================
	// �E�B���h�E��^�񒆂Ɏ����Ă���
	//------------------------------------
	void WindowCenter(HWND handle_window)
	{
		HWND handle_window_owener;
		RECT rect_child, rect_owener;

		// �e�E�B���h�E�̃n���h�����擾
		handle_window_owener = GetParent(handle_window);

		if (handle_window_owener == nullptr)
		{// �e�̃E�B���h�E�����݂��Ȃ�������V�X�e���S�̂ɂ�����p�����[�^���擾�܂��͐ݒ肷��
			SystemParametersInfo(
				SPI_GETWORKAREA,// �擾�܂��͐ݒ肷�ׂ��V�X�e���p�����[�^
				0,				// ���{���鑀��
				&rect_child,	// ���{���鑀��Q
				0);				// ���[�U�[�v���t�@�C���̍X�V�I�v�V����   
		}
		else
		{// �N���C�A���g���W�̎擾
			GetClientRect(
				handle_window_owener,// �E�B���h�E�n���h��
				&rect_child);		 // �N���C�A���g���W

		}

		// �X�N���[�����W���擾
		GetWindowRect(
			handle_window,
			&rect_owener);

		// �E�B���h�E�̈ʒu�v�Z
		s32 x = ((rect_child.right - rect_child.left) - (rect_owener.right - rect_owener.left)) / 2 + rect_child.left;
		s32 y = ((rect_child.bottom - rect_child.top) - (rect_owener.bottom - rect_owener.top)) / 2 + rect_child.top;

		// �E�B���h�E�̃|�W�V�����ݒ�
		SetWindowPos(
			handle_window,// �E�B���h�E�n���h��
			HWND_TOP,	  // �z�u�����̃n���h��
			x, y,		  // �c�������̃n���h��
			0, 0,		  // ���A����
			SWP_NOSIZE);  // �E�B���h�E�ʒu�̃I�v�V����(�T�C�Y�̕ύX�͂Ȃ�)
	}
};

