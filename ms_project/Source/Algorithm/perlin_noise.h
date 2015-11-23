//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// �p�[�����m�C�Y
//
// Created by Ryusei Kajiya on 20151109
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//*****************************************************************************
// ���d��`�h�~
#pragma once

//*****************************************************************************
// �N���X�݌v
class PerlinNoise
{
 public:

   // �m�C�Y��ԕ��@
   enum InterpolationType
   {
     LINEAR_INTERPOLATION,  // ���`���
     COSINE_INTERPOLATION,  // �R�T�C�����
     MAX_INTERPOLATION,
   };

  PerlinNoise();

  ~PerlinNoise();

  // �m�C�Y���d�˂鐔�ݒ�
  // �ʏ��6�B�����̏d���ɂ���Ă�4�Ȃǂ�
  void SetOctaves(int oct);

  // ���g���ݒ�
  // �����قǃm�C�Y���ׂ����Ȃ�
  // �Ⴂ�قǃm�C�Y���e���Ȃ�
  void SetFrequency(float freq);

  // Persistence�ݒ�
  // �����قǗאڂ����m�C�Y�ƒl�������Ȃ�
  // �Ⴂ�قǗאڂ����m�C�Y�ƒl���߂��Ȃ�
  void SetPersistence(float per);

  // ��ԕ��@�ݒ�
  void SetInterpolationType(InterpolationType type);

  // �V�[�h�l�ݒ�
  void SetSeed(int seed);

  // �m�C�Y�擾
  float GetNoise(float n) const;
  float GetNoise(float x, float y) const;

private:

   // �m�C�Y���
   float InterpolateNoise(float n) const;
   float InterpolateNoise(float x, float y) const;

  // �t�B���^���������m�C�Y
   float FilteredNoise(int n) const;
   float FilteredNoise(int x, int y) const;

  // ���`���
   float InterpolationLinear(float f0, float f1, float d) const;
  // �R�T�C�����
   float InterpolationCosine(float f0, float f1, float d) const;

  // �m�C�Y�W�F�l���[�^
  // -1.0 ^ 1.0�̕���������Ԃ�
   float RawPerlinNoise(int n) const;
   float RawPerlinNoise(int x, int y) const;

 private:

  // �I�N�^�[�u��
  int _octaves;

  // ���g��
  float _frequency;

  // ����
  float _persistence;

  // �m�C�Y��ԕ��@
  InterpolationType _interpolation_type;

  // ��ԕ��@�e�[�u��
  static float(PerlinNoise::*InterpolationTable[MAX_INTERPOLATION])(
    float /* ��Ԏn�_�l */,
    float /* ��ԏI�_�l*/,
    float /* ��ԌW��(0~1) */) const;

  // �V�[�h
  static int _seed;
};
