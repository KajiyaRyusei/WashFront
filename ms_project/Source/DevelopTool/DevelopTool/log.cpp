//==============================================================================
//
// ログ出力クラス[log.cpp]
// Author : Toshihiko Tsukamoto
//          Kajiya Ryusei
//
//==============================================================================
#include <fstream>
#include <direct.h>
#include "general\thread\critical_section\critical_section.h"
#include "log.h"

#ifndef _RELEASE

using namespace vg::general::thread::ciritical_section;

namespace vg{
namespace develop_tool{
//==============================================================================
// コンストラクタ
//------------------------------------------------------------------------------
Log::Log(){
  // バッファの初期化
  DeleteBuffer();
  
  // 時間を取得
  SYSTEMTIME time;
  GetLocalTime(&time);
  // exe直下にフォルダ作成
  _mkdir("Debug\\Log");
  // 時間を文字列に変換
  char string[kTimeBufferMax] = { 0 };
  std::sprintf(string, "--%d月%d日%d時%d分%d秒",
    time.wMonth,
    time.wDay,
    time.wHour,
    time.wMinute,
    time.wSecond);

  // 排他処理
  cs = new CiriticalSection();
  CiriticalSection::Lock a(*cs);
  
  // 時間の区切り文字を表示
  std::fstream fs;
  fs.open("Debug\\Log\\Log.txt", std::fstream::app);
  fs << std::endl << string << "----------------------------------------\n";
  fs.close();
}
//==============================================================================
// デストラクタ
//------------------------------------------------------------------------------
Log::~Log(){
  // バッファの書き込み
  WriteBuffer();
  // 解放
  common::SafeDelete(cs);
}
//==============================================================================
// バッファに書き込む
//------------------------------------------------------------------------------
void Log::Output(const char *name, const char *message){

  // バッファに追加
  std::strncat(text_buffer, name, kNameMax);
  int name_num = std::strlen(name);
  // 名前が文字数以内
  if (name_num < kNameMax){
    for (int i = 0; i < kNameMax - name_num + kSpaceSize; i++){
      std::strcat(text_buffer, " ");
    }
  }
  // 名前が文字数超えてるとき
  else{
    for (int i = 0; i < kSpaceSize; i++){
      std::strcat(text_buffer, " ");
    }
  }

  std::strcat(text_buffer, message);
  std::strcat(text_buffer, "\n");

  // バッファが一定量超えたら書き込んで初期化を行う
  if (kBufferWriteSize < std::strlen(text_buffer)){
    WriteBuffer();
  }
}
//==============================================================================
// バッファに書き込む
//------------------------------------------------------------------------------
void Log::Output(const char *name, const s32 value){

  std::strncat(text_buffer, name, kNameMax);
  int name_num = std::strlen(name);
  // 名前が文字数以内
  if (name_num < kNameMax){
    for (int i = 0; i < kNameMax - name_num + kSpaceSize; i++){
      std::strcat(text_buffer, " ");
    }
  }
  // 名前が文字数超えてるとき
  else{
    for (int i = 0; i < kSpaceSize; i++){
      std::strcat(text_buffer, " ");
    }
  }
  char string_value[kMessageMax] = { 0 };
  _itoa(value, string_value, 10);   // 10進数
  std::strcat(text_buffer, string_value);
  std::strcat(text_buffer, "\n");

  // バッファが一定量超えたら書き込んで初期化を行う
  if (kBufferWriteSize < std::strlen(text_buffer)){
    WriteBuffer();
  }
}
//==============================================================================
// バッファからテキストにまとめて書き出す
//------------------------------------------------------------------------------
void Log::WriteBuffer(){
{
  // 排他処理
  CiriticalSection::Lock a(*cs);

  // バッファからテキストに書き込み
  std::fstream fs;
  fs.open("LOG\\Log.txt", std::fstream::app);
  fs << text_buffer;
  fs.close();
}
// バッファの初期化
DeleteBuffer();
}
//==============================================================================
// バッファの初期化
//------------------------------------------------------------------------------
void Log::DeleteBuffer(){
  std::strcpy(text_buffer, "");
}
} // develop_tool
} // vg
#endif
//EOF