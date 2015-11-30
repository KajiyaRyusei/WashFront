//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// アサート
// 
// Created by Ryusei Kajiya on 20151005
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//*****************************************************************************
// インクルード
#include "assert.h"

//=============================================================================
// アサート
void Assert(char *experience, char *filename, int line, char *format, ...)
{
	const u16 kStringSize = 128;
	char  stringdisplay[kStringSize];
	char stringresult[512];
	va_list  args;

	va_start(args, format);
	_vsnprintf_s(&stringdisplay[0], sizeof(stringdisplay), _TRUNCATE, format, args);
	va_end(args);
	sprintf_s(&stringresult[0], sizeof(stringresult), "!GFF_ASSERT ERROR! \nExpressinon %s,\nMessage :%s \nErrorFile:%s=> Line:%d\n", experience, (LPCSTR)(&stringdisplay[0]), filename, line);

#ifdef OUTPUT_ASSERT_STRING
	OutputDebugStringA(&stringresult[0]);
#endif

#ifdef OUTPUT_ASSERT_BOX
	MessageBoxA(NULL, &stringresult[0], "ASSERT ERROR", MB_OK);
#endif

}