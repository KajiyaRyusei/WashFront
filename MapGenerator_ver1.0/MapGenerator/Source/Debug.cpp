//=============================================================================
//
// �f�o�b�O�N���X [Debug.cpp]
// Author : KEITA OHUCHI
//
//=============================================================================

#include "Debug.h"
#include "Manager.h"
#include "Main.h"
#include <stdio.h>
#include <tchar.h>


//-----------------------------------------------------------------------------
// �ÓI�����o�ϐ�
//-----------------------------------------------------------------------------
LPD3DXFONT DebugProc::font_ = nullptr;
char DebugProc::string_[STR_MAX] = {};


//=============================================================================
// �R���X�g���N�^
//=============================================================================
DebugProc::DebugProc()
{
	font_ = nullptr;
	memset(string_, 0, sizeof(string_));
}

//=============================================================================
// �f�X�g���N�^
//
// DATE : 2014/05/13
//=============================================================================
DebugProc::~DebugProc()
{

	// �t�H���g�|�C���^�̉��
	SafeRelease(font_);

}

//=========================================================================
// ����������
//=========================================================================
HRESULT DebugProc::Init()
{
	// �f�o�C�X�̎擾
	Renderer *renderer = Manager::GetInstance()->GetRenderer();
	LPDIRECT3DDEVICE9 device = renderer->GetDevice();

	// �t�H���g�̐���
	D3DXCreateFont(device, 18, 0, 0, 0, FALSE, SHIFTJIS_CHARSET,
				   OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH,
				   "Terminal", &font_);

	return S_OK;
}

//=========================================================================
// �X�V����
//=========================================================================
void DebugProc::Update()
{
	// �����񏉊���
	memset(string_, 0, sizeof(string_));
}

//=========================================================================
// �`�揈��
//=========================================================================
void DebugProc::Draw()
{
	// �`��͈�
	RECT rect;
	rect.left = 0;
	rect.top = 0;
	rect.right = SCREEN_WIDTH;
	rect.bottom = SCREEN_HEIGHT;

	// �e�L�X�g�`��
	font_->DrawText(nullptr, string_, -1, &rect, DT_LEFT,
					 D3DXCOLOR(1.0f, 0.0f, 0.3f, 1.0f));
}

#ifdef _DEBUG
//=========================================================================
// �\������
//=========================================================================
void DebugProc::Printf(char *fmt, ...)
{
	// �ψ������X�g
	va_list list;
	char *cur;
	char buf[256] = {0};
	char work[32];

	// �ψ����A�N�Z�X�̑O����
	va_start(list, fmt);
	// �J�[�\��������������̐擪��
	cur = fmt;

	// ���������񂪏I������܂Ń��[�v
	for ( ; *cur; ++cur) {
		if (*cur != '%') {
			// �ꕶ���ۑ�
			_stprintf_s(work, "%c", *cur);
		} else {
			cur++;
			switch (*cur) {
			case 'c':
				// ������ۑ�
				_stprintf_s(work, "%c", va_arg(list, char));
				break;

			case 'd':
				// �����l�ۑ�
				_stprintf_s(work, "%d", va_arg(list, int));
				break;

			case 'f':
				// ���ϒ�������float��double�^�ɕϊ������
				_stprintf_s(work, "%.2lf", va_arg(list, double));
				break;
			}
		}
		// ���[�N�̓��e���o�b�t�@�ɕt��������
		strcat_s(buf, work);
	}

	// �ψ����A�N�Z�X�㏈��
	va_end(list);
	// �o�b�t�@�̓��e�������o�ϐ��ɕt��������
	strcat_s(string_, buf);
}
#endif


// End of file