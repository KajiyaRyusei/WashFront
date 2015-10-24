//=============================================================================
//
// ���Ԍv���N���X[debug_time_measurement.cpp]
//
//=============================================================================
#include "develop_tool\time_measurement.h"
#ifndef _RELEASE

namespace vg {
namespace develop_tool {

//==============================================================================
// �v���g�^�C�v�錾
//------------------------------------------------------------------------------
// timeGetTime���g�p�����v��(�~���b�P��)
void StartTimeGetTime();
f64 EndTimeGetTime();

// �v���J�E���^
static LARGE_INTEGER g_query_freq;
static LARGE_INTEGER g_query_counter;
static f64 g_time_counter;

//==============================================================================
// �v���̊J�n(QueryPerformanceCounter)
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
// �v���̏I��(QueryPerformanceCounter)
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
// �v���̊J�n(TImeGetTime)
//------------------------------------------------------------------------------
void StartTimeGetTime()
{
  g_time_counter = timeGetTime();
}

//==============================================================================
// �v���̏I��(TImeGetTime)
//------------------------------------------------------------------------------
f64 EndTimeGetTime()
{
  f64 end_time = timeGetTime();
  return static_cast<double>(end_time - g_time_counter) / 1000;
}

} // develop_tool
} // vg

#endif