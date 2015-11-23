//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// パーリンノイズ
//
// Created by Ryusei Kajiya on 20151109
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//*****************************************************************************
// 多重定義防止
#pragma once

//*****************************************************************************
// クラス設計
class PerlinNoise
{
 public:

   // ノイズ補間方法
   enum InterpolationType
   {
     LINEAR_INTERPOLATION,  // 線形補間
     COSINE_INTERPOLATION,  // コサイン補間
     MAX_INTERPOLATION,
   };

  PerlinNoise();

  ~PerlinNoise();

  // ノイズを重ねる数設定
  // 通常は6。処理の重さによっては4なども
  void SetOctaves(int oct);

  // 周波数設定
  // 高いほどノイズが細かくなる
  // 低いほどノイズが粗くなる
  void SetFrequency(float freq);

  // Persistence設定
  // 高いほど隣接したノイズと値が遠くなる
  // 低いほど隣接したノイズと値が近くなる
  void SetPersistence(float per);

  // 補間方法設定
  void SetInterpolationType(InterpolationType type);

  // シード値設定
  void SetSeed(int seed);

  // ノイズ取得
  float GetNoise(float n) const;
  float GetNoise(float x, float y) const;

private:

   // ノイズ補間
   float InterpolateNoise(float n) const;
   float InterpolateNoise(float x, float y) const;

  // フィルタをかけたノイズ
   float FilteredNoise(int n) const;
   float FilteredNoise(int x, int y) const;

  // 線形補間
   float InterpolationLinear(float f0, float f1, float d) const;
  // コサイン補間
   float InterpolationCosine(float f0, float f1, float d) const;

  // ノイズジェネレータ
  // -1.0 ^ 1.0の浮動小数を返す
   float RawPerlinNoise(int n) const;
   float RawPerlinNoise(int x, int y) const;

 private:

  // オクターブ数
  int _octaves;

  // 周波数
  float _frequency;

  // 高さ
  float _persistence;

  // ノイズ補間方法
  InterpolationType _interpolation_type;

  // 補間方法テーブル
  static float(PerlinNoise::*InterpolationTable[MAX_INTERPOLATION])(
    float /* 補間始点値 */,
    float /* 補間終点値*/,
    float /* 補間係数(0~1) */) const;

  // シード
  static int _seed;
};
