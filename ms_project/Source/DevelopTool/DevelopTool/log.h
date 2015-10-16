//==============================================================================
//
// ���O�o�̓N���X[log.h]
// Author : Toshihiko Tsukamoto
//          Kajiya Ryusei
//
// �����F
//  ���O���e�L�X�g�t�@�C���ŏo�͂���N���X(exe������LOG�t�H���_�𐶐�)
//  �o�͕������o�b�t�@�����O���A�����ς��ɂȂ�����e�L�X�g�ɏ����o���B
//
// �g�p���@�F
//  DebugManager�ɂ��̃N���X�̃C���X�^���X���������������B
//  �C���X�^���X���Q�Ƃ�Output���ĂԂƃ��O���\�������B
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
// (�o�͌���)
//   --12��31��23��59��59�b----------------
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
  const s16 kBufferMax = 2048;       // Buffer���m�ۂ���傫��
  const s16 kBufferWriteSize = 2000; // Buffer�ł���傫���i�������ރ^�C�~���O�j
  const s16 kSpaceSize = 8;          // ���O�ƃ��b�Z�[�W�̃X�y�[�X��
  const s16 kNameMax = 24;           // ���O�̍ő啶����
  const s16 kTimeBufferMax = 24;     // ��؂莞�Ԃ̃o�b�t�@�T�C�Y
  const s16 kMessageMax = 48;        // ���b�Z�[�W�̍ő啶����
}// namespace

//==============================================================================
// �O���錾
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
// ���O�\���N���X
//==============================================================================
class Log {
#ifndef _RELEASE
 public:
  // �o�b�t�@�ɏ������ށB
   void Output(const char *name, const char *message);
   void Output(const char *name, const s32 value);

  // �R���X�g���N�^ �e�L�X�g�Ɏ��Ԃ̋�؂��\��
   Log();
  // �f�X�g���N�^
   virtual ~Log();

 private:
  // �o�b�t�@���e�L�X�g�ɂ܂Ƃ߂ď������ޏ����B
  void WriteBuffer();
  // �o�b�t�@�̏�����
  void DeleteBuffer();
  // �r�������p�C���X�^���X
  general::thread::ciritical_section::CiriticalSection *cs;
  // �o�b�t�@
  char text_buffer[kBufferMax];
#endif
};
} // develop_tool
} // vg
#endif  // VG_DEBUG_LOGOUTPUT_H_
//EOF