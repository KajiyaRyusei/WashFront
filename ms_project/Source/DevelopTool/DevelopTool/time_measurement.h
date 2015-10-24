//=============================================================================
//
// ���Ԍv���N���X[debug_time_measurement.h]
// Author : Ryusei Kajiya
//          Toshihiko Tsukamoto
//          �勴�̏���
//
// �g�p���@�F�}�C�N���b�P�ʂŌv�����܂��B
//
// using namespace vg::develop_tool::measurement;
//
// StartPerformanceCounter();
//
// #����
// 
// f64 time = EndPerformanceCounter();
// 
// printf("�������ԁF%f", time);
// 
//=============================================================================
#pragma once

#ifndef VG_DEGUB_TIMEMEASUREMENT_H_
#define VG_DEGUB_TIMEMEASUREMENT_H_



namespace vg {
namespace develop_tool{

#ifndef _RELEASE
 // QueryPerformanceCounter���g�p�����v��(�}�C�N���b�P��)
 void StartPerformanceCounter();
 f64 EndPerformanceCounter();
#endif

} // develop_tool
} // vg



#endif // VG_DEGUB_TIMEMEASUREMENT_H_


