//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// �p�[�����m�C�Y
//
// Created by Ryusei Kajiya on 20151109
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//*****************************************************************************
// include
#include "perlin_noise.h"
#include <math.h>

//*****************************************************************************
// �ÓI�����o�ϐ�
//*****************************************************************************
// �����V�[�h
int PerlinNoise::_seed = 0;

//=============================================================================
// �R���X�g���N�^
//=============================================================================
PerlinNoise::PerlinNoise() :
  _octaves(6),
  _frequency(0.008f),
  _persistence(0.5f),
  _interpolation_type(COSINE_INTERPOLATION)
{

}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
PerlinNoise::~PerlinNoise()
{

}

//=============================================================================
// �I�N�^�[�u���ݒ�
//=============================================================================
void PerlinNoise::SetOctaves(int oct)
{
  _octaves = oct;
}

//=============================================================================
// ���g���ݒ�
//=============================================================================
void PerlinNoise::SetFrequency(float freq)
{
  _frequency = freq;
}

//=============================================================================
// Persistence�ݒ�
//=============================================================================
void PerlinNoise::SetPersistence(float per)
{
  _persistence = per;
}

//=============================================================================
// ��ԕ��@�ݒ�
//=============================================================================
void PerlinNoise::SetInterpolationType(InterpolationType type)
{
  _interpolation_type = type;
}

//=============================================================================
// �V�[�h�l�ݒ�
//=============================================================================
void PerlinNoise::SetSeed(int seed)
{
  this->_seed = seed;
}

//=============================================================================
// �m�C�Y�擾
//=============================================================================
float PerlinNoise::GetNoise(float n) const
{
  float sum = 0;
  float amplitude = 1;
  float tempFreq = _frequency;

  for(int i = 0; i < _octaves; i++)
  {
    sum += InterpolateNoise(n * tempFreq) * amplitude;

    // ���g��2�{
    tempFreq *= 2;
    // �g�̍���
    amplitude *= _persistence;
  }

  return sum;
}

//=============================================================================
// �m�C�Y�擾
//=============================================================================
float PerlinNoise::GetNoise(float x, float y) const
{
  float sum = 0;
  float amplitude = 1;
  float tempFreq = _frequency;

  for(int i = 0; i < _octaves; i++)
  {
    sum += InterpolateNoise(x * tempFreq, y * tempFreq) * amplitude;

    // ���g��2�{
    tempFreq *= 2;
    // �g�̍���
    amplitude *= _persistence;
  }

  return sum;
}

//=============================================================================
// �m�C�Y���
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
// �m�C�Y���
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
// �m�C�Y�t�B���^
//=============================================================================
float PerlinNoise::FilteredNoise(int n) const
{
  return (RawPerlinNoise(n) / 2 + (RawPerlinNoise(n - 1) + RawPerlinNoise(n + 1)) / 4);
}

//=============================================================================
// �m�C�Y�t�B���^
//=============================================================================
float PerlinNoise::FilteredNoise(int x, int y) const
{
  // 3x3�K�E�V�A���t�B���^
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
// �l�̕��(���`)
//=============================================================================
float PerlinNoise::InterpolationLinear(float f0, float f1, float d) const
{
  // ���`���
  return (f0 * (1.0f - d) + f1 * d);
}

//=============================================================================
// �l�̕��(�R�T�C��)
//=============================================================================
float PerlinNoise::InterpolationCosine(float f0, float f1, float d) const
{
  // �R�T�C�����
  float rad = d * 3.1415926535f;
  d = (1.0f - cosf(rad)) * 0.5f;	// 0 ~ 1
  return (f0 * (1.0f - d) + f1 * d);
}

//=============================================================================
// �m�C�Y�W�F�l���[�^	
// -1.0 ^ 1.0�̕���������Ԃ�
//=============================================================================
float PerlinNoise::RawPerlinNoise(int n) const
{
  n += _seed;

  n = (n << 13) ^ n;

  int noise = (n * (n * n * 15731 + 122033) + 1376312589) & 0x7fffffff;

  return 1.0f - ((float)noise / 1073741824.0f);
}

//=============================================================================
// �m�C�Y�W�F�l���[�^	
// -1.0 ^ 1.0�̕���������Ԃ�
//=============================================================================
float PerlinNoise::RawPerlinNoise(int x, int y) const
{
  int n = _seed + x + y * 2677;

  n = (n << 13) ^ n;

  int noise = (n * (n * n * 15731 + 122033) + 1376312589) & 0x7fffffff;

  return 1.0f - ((float)noise / 1073741824.0f);
}