//=============================================================================
//
// 時間計測クラス[debug_time_measurement.cpp]
//
//=============================================================================
#include "develop_tool\time_measurement.h"
#ifndef _RELEASE

namespace vg {
namespace develop_tool {

//==============================================================================
// プロトタイプ宣言
//------------------------------------------------------------------------------
// timeGetTimeを使用した計測(ミリ秒単位)
void StartTimeGetTime();
f64 EndTimeGetTime();

// 計測カウンタ
static LARGE_INTEGER g_query_freq;
static LARGE_INTEGER g_query_counter;
static f64 g_time_counter;

//==============================================================================
// 計測の開始(QueryPerformanceCounter)
//------------------------------------------------------------------------------
void StartPerformanceCounter()
{
  if (QueryPerformanceFrequency(&g_query_freq)){
    QueryPerformanceCounter(&g_query_counter);
  }
  else{
    StartTimeGetTime();
  }
}

//==============================================================================
// 計測の終了(QueryPerformanceCounter)
//------------------------------------------------------------------------------
f64 EndPerformanceCounter()
{
  LARGE_INTEGER query_end;
  if (QueryPerformanceCounter(&query_end)){
    return static_cast<double>(query_end.QuadPart - g_query_counter.QuadPart)
      / g_query_freq.QuadPart;
  }

  return EndTimeGetTime();
}

//==============================================================================
// 計測の開始(TImeGetTime)
//------------------------------------------------------------------------------
void StartTimeGetTime()
{
  g_time_counter = timeGetTime();
}

//==============================================================================
// 計測の終了(TImeGetTime)
//------------------------------------------------------------------------------
f64 EndTimeGetTime()
{
  f64 end_time = timeGetTime();
  return static_cast<double>(end_time - g_time_counter) / 1000;
}

} // develop_tool
} // vg

#endif