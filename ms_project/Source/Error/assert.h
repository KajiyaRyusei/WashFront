//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// �A�T�[�g
// 
// Created by Ryusei Kajiya on 20151005
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//*****************************************************************************
// ���d�C���N���[�h�h�~
#pragma once

// �u���[�N�|�C���g����
#define BLAKEPOINT __asm int 3

// �J�X�^���p�̃A�T�[�g�����邱�Ƃ��O���ɒm�点��
#define CUSTOM_ASSERT_ENABLE

// �A�T�\�g�̃��b�Z�[�W���o��
#define OUTPUT_ASSERT_STRING

// �A�T�\�Ƃ�MessageBox�Œm�点��
#define OUTPUT_ASSERT_BOX

// �R�����g�A�E�g�ŃA�T�\�Ƃ̐؂�ւ�
#ifndef _RELEASE
#define DO_ASSERT
#endif

#define DO_STRONG_ASSERT

#ifdef DO_ASSERT
// ���������U�Ȃ�x��
#define ASSERT(exp,format,...) \
if (exp){}\
else{\
	Assert(#exp,__FILE__,__LINE__,format,__VA_ARGS__);\
	BLAKEPOINT\
}
#else
#define ASSERT(exp,format,...) (exp)
#endif


#ifdef DO_STORONG_ASSERT
#define STRONG_ASSERT(exp,format,...)\
if (exp){}\
else{\
	vg::common::Assert(#exp, __FILE__, __LINE__, format, __VA_ARGS__); \
	BLAKEPOINT\
}
#else STRONG_ASSERT(exp,format,...)
#endif

#ifndef _RELEASE
#define BREAK_IF( exp ) { if( ( exp ) ) { __debugbreak(); } }
#else
#define BREAK_IF __noop
#endif

void Assert(char *experience, char *filename, int line, char *format, ...);
