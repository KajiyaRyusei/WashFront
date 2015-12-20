//=============================================================================
//
// �T�E���h����[sound.h]
// ����� 2014 / 9 /  1
// �X�V�� 2015 / 3 / 18
// Author : 20274	�]�� ���I
//
//=============================================================================
#ifndef _SOUND_H_
#define _SOUND_H_

//*****************************************************************************
// �C���N���[�h�t�@�C��
//*****************************************************************************
#include "Renderer\directx9.h"
#include "XAudio2.h"

//*****************************************************************************
// ���C�u�����Q��
//*****************************************************************************

//*****************************************************************************
// �O���錾
//*****************************************************************************

//*****************************************************************************
// const�ϐ�
//*****************************************************************************

//*****************************************************************************
// define��`
//*****************************************************************************

//*****************************************************************************
// �񋓑ђ�`
//*****************************************************************************
// �T�E���h�t�@�C��
enum SOUND_LABEL
{
	BGM_RESULT = 0,
	BGM_GAME,
	BGM_TITLE,
	SE_DECIDE,
	SE_COUNT,
	SE_REWARD,
	SE_OVERHEAT,
	SE_SCORE_ADD,
	SE_WATER_BULLET,
	SE_WEAPON_CHANGE,
	SE_OVERHEAT_2,
	SE_SCORE_ADD_2,
	SE_WATER_BULLET_2,
	SE_WEAPON_CHANGE_2,
	SOUND_LABEL_MAX
};

//*****************************************************************************
// �\���̒�`
//*****************************************************************************
// �p�����[�^�\����
struct PARAM
{
	LPCWSTR filename;	// �t�@�C����
	bool bLoop;			// ���[�v���邩�ǂ���
};

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CSound
{
public:
	// �R���X�g���N�^
	CSound();
	// �f�X�g���N�^
	~CSound();

	// ������
	HRESULT Init( HWND hWnd );
	// �I��
	void	Uninit( void );
	// �Đ�
	HRESULT Play( SOUND_LABEL label );
	// �Đ�( ���ϑO )
	HRESULT PlaySE(SOUND_LABEL label);
	// ��~( ���x���w�� )
	void	Stop( SOUND_LABEL label );
	// ��~( �S�� )
	void	Stop(void);
	// ??
	HRESULT CheckChunk( HANDLE hFile , DWORD format , DWORD *pChunkSize , DWORD *pChunkDataPosition );
	// ??
	HRESULT ReadChunkData( HANDLE hFile , void *pBuffer , DWORD dwBuffersize , DWORD dwBufferoffset );

protected:

private:
	// XAudio2�I�u�W�F�N�g�ւ̃C���^�[�t�F�C�X
	IXAudio2				*m_pXAudio2;
	// �}�X�^�[�{�C�X
	IXAudio2MasteringVoice	*m_pMasteringVoice;
	// �\�[�X�{�C�X
	IXAudio2SourceVoice		*m_pSourceVoice[ SOUND_LABEL_MAX ];
	// �I�[�f�B�I�f�[�^
	BYTE					*m_pDataAudio[ SOUND_LABEL_MAX ];
	// �I�[�f�B�I�f�[�^�T�C�Y
	DWORD					m_sizeAudio[SOUND_LABEL_MAX];					
};


#endif