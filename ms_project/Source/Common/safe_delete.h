//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// �Z�[�t�f���[�g
//
// Created by Ryusei Kajiya on 20151005
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//*****************************************************************************
// ���d�C���N���[�h�h�~
#pragma once

//=============================================================================
// ���S�ȍ폜
template<typename T> inline void SafeDelete(T*& ptr)
{
	if (ptr != nullptr)
	{
		delete ptr;
		ptr = nullptr;
	}
}
//=============================================================================
// ���S�Ȕz��폜
template<typename T> inline void SafeDeleteArray(T*& ptr)
{
	if (ptr != nullptr)
	{
		delete[] ptr;
		ptr = nullptr;
	}
}