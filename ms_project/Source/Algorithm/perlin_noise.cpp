//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// パーリンノイズ
//
// Created by Ryusei Kajiya on 20151109
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//*****************************************************************************
// include
#include "perlin_noise.h"
#include <math.h>

//*****************************************************************************
// 静的メンバ変数
//*****************************************************************************
// 乱数シード
int PerlinNoise::_seed = 0;

//=============================================================================
// コンストラクタ
//=============================================================================
PerlinNoise::PerlinNoise() :
  _octaves(6),
  _frequency(0.008f),
  _persistence(0.5f),
  _interpolation_type(COSINE_INTERPOLATION)
{

}

//=============================================================================
// デストラクタ
//=============================================================================
PerlinNoise::~PerlinNoise()
{

}

//=============================================================================
// オクターブ数設定
//=============================================================================
void PerlinNoise::SetOctaves(int oct)
{
  _octaves = oct;
}

//=============================================================================
// 周波数設定
//=============================================================================
void PerlinNoise::SetFrequency(float freq)
{
  _frequency = freq;
}

//=============================================================================
// Persistence設定
//=============================================================================
void PerlinNoise::SetPersistence(float per)
{
  _persistence = per;
}

//=============================================================================
// 補間方法設定
//=============================================================================
void PerlinNoise::SetInterpolationType(InterpolationType type)
{
  _interpolation_type = type;
}

//=============================================================================
// シード値設定
//=============================================================================
void PerlinNoise::SetSeed(int seed)
{
  this->_seed = seed;
}

//=============================================================================
// ノイズ取得
//=============================================================================
float PerlinNoise::GetNoise(float n) const
{
  float sum = 0;
  float amplitude = 1;
  float tempFreq = _frequency;

  for(int i = 0; i < _octaves; i++)
  {
    sum += InterpolateNoise(n * tempFreq) * amplitude;

    // 周波数2倍
    tempFreq *= 2;
    // 波の高さ
    amplitude *= _persistence;
  }

  return sum;
}

//=============================================================================
// ノイズ取得
//=============================================================================
float PerlinNoise::GetNoise(float x, float y) const
{
  float sum = 0;
  float amplitude = 1;
  float tempFreq = _frequency;

  for(int i = 0; i < _octaves; i++)
  {
    sum += InterpolateNoise(x * tempFreq, y * tempFreq) * amplitude;

    // 周波数2倍
    tempFreq *= 2;
    // 波の高さ
    amplitude *= _persistence;
  }

  return sum;
}

//=============================================================================
// ノイズ補間
//=============================================================================
float PerlinNoise::InterpolateNoise(float n) const
{
  int intN = (int)n;
  float fractionN = n - intN;

  float f0, f1;

  f0 = FilteredNoise(intN);
  f1 = FilteredNoise(intN + 1);

  return InterpolationLinear(f0, f1, fractionN);
}

//=============================================================================
// ノイズ補間
//=============================================================================
float PerlinNoise::InterpolateNoise(float x, float y) const
{
  int intX = (int)x;
  float fractionX = x - intX;

  int intY = (int)y;
  float fractionY = y - intY;

  float f0, f1;

  f0 = InterpolationLinear(
    FilteredNoise(intX, intY),
    FilteredNoise(intX + 1, intY),
    fractionX);
  f1 = InterpolationLinear(
    FilteredNoise(intX, intY + 1),
    FilteredNoise(intX + 1, intY + 1),
    fractionX);

  return InterpolationLinear(f0, f1, fractionY);
}

//=============================================================================
// ノイズフィルタ
//=============================================================================
float PerlinNoise::FilteredNoise(int n) const
{
  return (RawPerlinNoise(n) / 2 + (RawPerlinNoise(n - 1) + RawPerlinNoise(n + 1)) / 4);
}

//=============================================================================
// ノイズフィルタ
//=============================================================================
float PerlinNoise::FilteredNoise(int x, int y) const
{
  // 3x3ガウシアンフィルタ
  float n = RawPerlinNoise(x, y) / 4;
  n += (RawPerlinNoise(x - 1, y) +
    RawPerlinNoise(x, y - 1) +
    RawPerlinNoise(x + 1, y) +
    RawPerlinNoise(x, y + 1)) / 8;
  n += (RawPerlinNoise(x - 1, y - 1) +
    RawPerlinNoise(x + 1, y - 1) +
    RawPerlinNoise(x - 1, y + 1) +
    RawPerlinNoise(x + 1, y + 1)) / 16;

  return n;
}

//=============================================================================
// 値の補間(線形)
//=============================================================================
float PerlinNoise::InterpolationLinear(float f0, float f1, float d) const
{
  // 線形補間
  return (f0 * (1.0f - d) + f1 * d);
}

//=============================================================================
// 値の補間(コサイン)
//=============================================================================
float PerlinNoise::InterpolationCosine(float f0, float f1, float d) const
{
  // コサイン補間
  float rad = d * 3.1415926535f;
  d = (1.0f - cosf(rad)) * 0.5f;	// 0 ~ 1
  return (f0 * (1.0f - d) + f1 * d);
}

//=============================================================================
// ノイズジェネレータ	
// -1.0 ^ 1.0の浮動小数を返す
//=============================================================================
float PerlinNoise::RawPerlinNoise(int n) const
{
  n += _seed;

  n = (n << 13) ^ n;

  int noise = (n * (n * n * 15731 + 122033) + 1376312589) & 0x7fffffff;

  return 1.0f - ((float)noise / 1073741824.0f);
}

//=============================================================================
// ノイズジェネレータ	
// -1.0 ^ 1.0の浮動小数を返す
//=============================================================================
float PerlinNoise::RawPerlinNoise(int x, int y) const
{
  int n = _seed + x + y * 2677;

  n = (n << 13) ^ n;

  int noise = (n * (n * n * 15731 + 122033) + 1376312589) & 0x7fffffff;

  return 1.0f - ((float)noise / 1073741824.0f);
}