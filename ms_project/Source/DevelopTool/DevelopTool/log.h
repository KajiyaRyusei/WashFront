//==============================================================================
//
// ログ出力クラス[log.h]
// Author : Toshihiko Tsukamoto
//          Kajiya Ryusei
//
// 説明：
//  ログをテキストファイルで出力するクラス(exe直下にLOGフォルダを生成)
//  出力文字をバッファリングし、いっぱいになったらテキストに書き出す。
//
// 使用方法：
//  DebugManagerにこのクラスのインスタンスを一つだけ持たせる。
//  インスタンスを参照しOutputを呼ぶとログが表示される。
// 
//  *************************************
// (ex)
//   develop_tool::log::Log n;
//   int a = 100;
//   char c[8] = { "abcedef" };
//   n.Output("saboten", 222);
//   n.Output("saboten", "aaa");
//   n.Output("saboten", a);
//   n.Output("saboten", c);
//  *************************************
// (出力結果)
//   --12月31日23時59分59秒----------------
//   saboten          222
//   saboten          aaa
//   saboten          100
//   saboten          abcedef
//  *************************************
//==============================================================================
#pragma once
#ifndef VG_DEBUG_LOGOUTPUT_H_
#define VG_DEBUG_LOGOUTPUT_H_

//==============================================================================
// const
//==============================================================================
namespace{
  const s16 kBufferMax = 2048;       // Bufferを確保する大きさ
  const s16 kBufferWriteSize = 2000; // Bufferできる大きさ（書き込むタイミング）
  const s16 kSpaceSize = 8;          // 名前とメッセージのスペース数
  const s16 kNameMax = 24;           // 名前の最大文字数
  const s16 kTimeBufferMax = 24;     // 区切り時間のバッファサイズ
  const s16 kMessageMax = 48;        // メッセージの最大文字数
}// namespace

//==============================================================================
// 前方宣言
//==============================================================================

namespace vg{
namespace general{
namespace thread{
namespace ciritical_section{
class CiriticalSection;
} // ciritical_section
} // thread
} // general
namespace develop_tool{
//==============================================================================
// ログ表示クラス
//==============================================================================
class Log {
#ifndef _RELEASE
 public:
  // バッファに書き込む。
   void Output(const char *name, const char *message);
   void Output(const char *name, const s32 value);

  // コンストラクタ テキストに時間の区切りを表示
   Log();
  // デストラクタ
   virtual ~Log();

 private:
  // バッファをテキストにまとめて書き込む処理。
  void WriteBuffer();
  // バッファの初期化
  void DeleteBuffer();
  // 排他処理用インスタンス
  general::thread::ciritical_section::CiriticalSection *cs;
  // バッファ
  char text_buffer[kBufferMax];
#endif
};
} // develop_tool
} // vg
#endif  // VG_DEBUG_LOGOUTPUT_H_
//EOF