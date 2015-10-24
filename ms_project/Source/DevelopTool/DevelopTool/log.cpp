//==============================================================================
//
// ���O�o�̓N���X[log.cpp]
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
// �R���X�g���N�^
//------------------------------------------------------------------------------
Log::Log(){
  // �o�b�t�@�̏�����
  DeleteBuffer();
  
  // ���Ԃ��擾
  SYSTEMTIME time;
  GetLocalTime(&time);
  // exe�����Ƀt�H���_�쐬
  _mkdir("Debug\\Log");
  // ���Ԃ𕶎���ɕϊ�
  char string[kTimeBufferMax] = { 0 };
  std::sprintf(string, "--%d��%d��%d��%d��%d�b",
    time.wMonth,
    time.wDay,
    time.wHour,
    time.wMinute,
    time.wSecond);

  // �r������
  cs = new CiriticalSection();
  CiriticalSection::Lock a(*cs);
  
  // ���Ԃ̋�؂蕶����\��
  std::fstream fs;
  fs.open("Debug\\Log\\Log.txt", std::fstream::app);
  fs << std::endl << string << "----------------------------------------\n";
  fs.close();
}
//==============================================================================
// �f�X�g���N�^
//------------------------------------------------------------------------------
Log::~Log(){
  // �o�b�t�@�̏�������
  WriteBuffer();
  // ���
  common::SafeDelete(cs);
}
//==============================================================================
// �o�b�t�@�ɏ�������
//------------------------------------------------------------------------------
void Log::Output(const char *name, const char *message){

  // �o�b�t�@�ɒǉ�
  std::strncat(text_buffer, name, kNameMax);
  int name_num = std::strlen(name);
  // ���O���������ȓ�
  if (name_num < kNameMax){
    for (int i = 0; i < kNameMax - name_num + kSpaceSize; i++){
      std::strcat(text_buffer, " ");
    }
  }
  // ���O�������������Ă�Ƃ�
  else{
    for (int i = 0; i < kSpaceSize; i++){
      std::strcat(text_buffer, " ");
    }
  }

  std::strcat(text_buffer, message);
  std::strcat(text_buffer, "\n");

  // �o�b�t�@�����ʒ������珑������ŏ��������s��
  if (kBufferWriteSize < std::strlen(text_buffer)){
    WriteBuffer();
  }
}
//==============================================================================
// �o�b�t�@�ɏ�������
//------------------------------------------------------------------------------
void Log::Output(const char *name, const s32 value){

  std::strncat(text_buffer, name, kNameMax);
  int name_num = std::strlen(name);
  // ���O���������ȓ�
  if (name_num < kNameMax){
    for (int i = 0; i < kNameMax - name_num + kSpaceSize; i++){
      std::strcat(text_buffer, " ");
    }
  }
  // ���O�������������Ă�Ƃ�
  else{
    for (int i = 0; i < kSpaceSize; i++){
      std::strcat(text_buffer, " ");
    }
  }
  char string_value[kMessageMax] = { 0 };
  _itoa(value, string_value, 10);   // 10�i��
  std::strcat(text_buffer, string_value);
  std::strcat(text_buffer, "\n");

  // �o�b�t�@�����ʒ������珑������ŏ��������s��
  if (kBufferWriteSize < std::strlen(text_buffer)){
    WriteBuffer();
  }
}
//==============================================================================
// �o�b�t�@����e�L�X�g�ɂ܂Ƃ߂ď����o��
//------------------------------------------------------------------------------
void Log::WriteBuffer(){
{
  // �r������
  CiriticalSection::Lock a(*cs);

  // �o�b�t�@����e�L�X�g�ɏ�������
  std::fstream fs;
  fs.open("LOG\\Log.txt", std::fstream::app);
  fs << text_buffer;
  fs.close();
}
// �o�b�t�@�̏�����
DeleteBuffer();
}
//==============================================================================
// �o�b�t�@�̏�����
//------------------------------------------------------------------------------
void Log::DeleteBuffer(){
  std::strcpy(text_buffer, "");
}
} // develop_tool
} // vg
#endif
//EOF