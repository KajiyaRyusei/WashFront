//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// アサート
// 
// Created by Ryusei Kajiya on 20151005
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//*****************************************************************************
// 多重インクルード防止
#pragma once

// ブレークポイント発生
#define BLAKEPOINT __asm int 3

// カスタム用のアサートがあることを外部に知らせる
#define CUSTOM_ASSERT_ENABLE

// アサ―トのメッセージを出力
#define OUTPUT_ASSERT_STRING

// アサ―とをMessageBoxで知らせる
#define OUTPUT_ASSERT_BOX

// コメントアウトでアサ―との切り替え
#ifndef _RELEASE
#define DO_ASSERT
#endif

#define DO_STRONG_ASSERT

#ifdef DO_ASSERT
// 条件式が偽なら警告
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
