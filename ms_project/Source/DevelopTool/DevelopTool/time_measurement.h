//=============================================================================
//
// 時間計測クラス[debug_time_measurement.h]
// Author : Ryusei Kajiya
//          Toshihiko Tsukamoto
//          大橋の助言
//
// 使用方法：マイクロ秒単位で計測します。
//
// using namespace vg::develop_tool::measurement;
//
// StartPerformanceCounter();
//
// #処理
// 
// f64 time = EndPerformanceCounter();
// 
// printf("処理時間：%f", time);
// 
//=============================================================================
#pragma once

#ifndef VG_DEGUB_TIMEMEASUREMENT_H_
#define VG_DEGUB_TIMEMEASUREMENT_H_



namespace vg {
namespace develop_tool{

#ifndef _RELEASE
 // QueryPerformanceCounterを使用した計測(マイクロ秒単位)
 void StartPerformanceCounter();
 f64 EndPerformanceCounter();
#endif

} // develop_tool
} // vg



#endif // VG_DEGUB_TIMEMEASUREMENT_H_


