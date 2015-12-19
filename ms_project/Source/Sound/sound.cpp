//=============================================================================
//
// �T�E���h����[sound.cpp]
// ����� 2014 / 9 /  1
// �X�V�� 2015 / 3 / 18
// Author : 20274	�]�� ���I
//
//=============================================================================

//*****************************************************************************
// �C���N���[�h�t�@�C��
//*****************************************************************************
#include "sound.h"

//*****************************************************************************
// const�ϐ�
//*****************************************************************************
// �e���f�ނ̃p�����[�^
PARAM c_param[ SOUND_LABEL_MAX ] =
{
	{ L"Data/Sound/BGM/result_bgm.wav" , true },
	{ L"Data/Sound/BGM/game_bgm.wav", true },
	{ L"Data/Sound/BGM/title_bgm.wav", true },
	{ L"Data/Sound/SE/decide_se.wav" , false },
	{ L"Data/Sound/SE/count_se.wav", false },
	{ L"Data/Sound/SE/reward_se.wav", false },
	{ L"Data/Sound/SE/overheat_se.wav", false },
	{ L"Data/Sound/SE/score_add.wav", false },
	{ L"Data/Sound/SE/water_bullet.wav", false },
	{ L"Data/Sound/SE/weapon_change_se.wav", false },
	{ L"Data/Sound/SE/overheat_se.wav", false },
	{ L"Data/Sound/SE/score_add.wav", false },
	{ L"Data/Sound/SE/water_bullet.wav", false },
	{ L"Data/Sound/SE/weapon_change_se.wav", false },
};

//*****************************************************************************
// define��`
//*****************************************************************************

//*****************************************************************************
// static�ϐ�
//*****************************************************************************


//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// �R���X�g���N�^
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
CSound::CSound( void )
{
	// �����o�ϐ�������
	m_pXAudio2			= NULL;
	m_pMasteringVoice	= NULL;

	for( int i = 0; i < SOUND_LABEL_MAX; i++ )
	{
		m_pSourceVoice[ i ] = NULL;
		m_pDataAudio[ i ]	= NULL;
		m_sizeAudio[ i ]	= NULL;	
	}
}


//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// �f�X�g���N�^
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
CSound::~CSound( void )
{

}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// ������
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
HRESULT CSound::Init( HWND hWnd )
{
	HRESULT hr;

	// COM���C�u�����̏�����
	CoInitializeEx( NULL , COINIT_MULTITHREADED );

	// XAudio2�I�u�W�F�N�g�̍쐬
	hr = XAudio2Create( &m_pXAudio2 , 0 );
	if( FAILED( hr ) )
	{
		MessageBox( hWnd , L"XAudio2�I�u�W�F�N�g�̍쐬�Ɏ��s�I", L"�x���I", MB_ICONWARNING );

		// COM���C�u�����̏I������
		CoUninitialize();
		return E_FAIL;
	}
	
	// �}�X�^�[�{�C�X�̐���
	hr = m_pXAudio2->CreateMasteringVoice( &m_pMasteringVoice );
	if( FAILED( hr ) )
	{
		MessageBox( hWnd , L"�}�X�^�[�{�C�X�̐����Ɏ��s�I", L"�x���I", MB_ICONWARNING );

		if( m_pXAudio2 )
		{
			// XAudio2�I�u�W�F�N�g�̊J��
			m_pXAudio2->Release();
			m_pXAudio2 = NULL;
		}

		// COM���C�u�����̏I������
		CoUninitialize();

		return E_FAIL;
	}

	// �T�E���h�f�[�^�̏�����
	for( int nCntSound = 0; nCntSound < SOUND_LABEL_MAX; nCntSound++ )
	{
		HANDLE hFile;
		DWORD dwChunkSize = 0;
		DWORD dwChunkPosition = 0;
		DWORD dwFiletype;
		WAVEFORMATEXTENSIBLE wfx;
		XAUDIO2_BUFFER buffer;

		// �o�b�t�@�̃N���A
		memset( &wfx , 0 , sizeof( WAVEFORMATEXTENSIBLE ) );
		memset( &buffer , 0 , sizeof( XAUDIO2_BUFFER  ) );

		

		// �T�E���h�f�[�^�t�@�C���̐���
		hFile = CreateFile( ( LPCWSTR )c_param[ nCntSound ].filename , GENERIC_READ , FILE_SHARE_READ , NULL , OPEN_EXISTING , 0 , NULL );
		if(hFile == INVALID_HANDLE_VALUE)
		{
			MessageBox( hWnd , L"�T�E���h�f�[�^�t�@�C���̐����Ɏ��s�I(1)" , L"�x���I" , MB_ICONWARNING );
			return HRESULT_FROM_WIN32( GetLastError() );
		}
		if(SetFilePointer( hFile , 0 , NULL , FILE_BEGIN ) == INVALID_SET_FILE_POINTER )
		{// �t�@�C���|�C���^��擪�Ɉړ�
			MessageBox( hWnd , L"�T�E���h�f�[�^�t�@�C���̐����Ɏ��s�I(2)" , L"�x���I" , MB_ICONWARNING );
			return HRESULT_FROM_WIN32( GetLastError() );
		}
	
		// WAVE�t�@�C���̃`�F�b�N
		hr = CheckChunk(hFile, 'FFIR', &dwChunkSize, &dwChunkPosition);
		if( FAILED( hr ) )
		{
			MessageBox( hWnd , L"WAVE�t�@�C���̃`�F�b�N�Ɏ��s�I(1)" , L"�x���I" , MB_ICONWARNING );
			return S_FALSE;
		}
		hr = ReadChunkData( hFile , &dwFiletype , sizeof( DWORD ) , dwChunkPosition );
		if( FAILED( hr ) )
		{
			MessageBox( hWnd , L"WAVE�t�@�C���̃`�F�b�N�Ɏ��s�I(2)" , L"�x���I" , MB_ICONWARNING );
			return S_FALSE;
		}
		if( dwFiletype != 'EVAW' )
		{
			MessageBox( hWnd , L"WAVE�t�@�C���̃`�F�b�N�Ɏ��s�I(3)" , L"�x���I" , MB_ICONWARNING );
			return S_FALSE;
		}
	
		// �t�H�[�}�b�g�`�F�b�N
		hr = CheckChunk( hFile , ' tmf' , &dwChunkSize , &dwChunkPosition );
		if( FAILED( hr ) )
		{
			MessageBox( hWnd , L"�t�H�[�}�b�g�`�F�b�N�Ɏ��s�I(1)" , L"�x���I" , MB_ICONWARNING );
			return S_FALSE;
		}
		hr = ReadChunkData( hFile , &wfx , dwChunkSize , dwChunkPosition );
		if(FAILED(hr))
		{
			MessageBox( hWnd , L"�t�H�[�}�b�g�`�F�b�N�Ɏ��s�I(2)" , L"�x���I" , MB_ICONWARNING );
			return S_FALSE;
		}

		// �I�[�f�B�I�f�[�^�ǂݍ���
		hr = CheckChunk( hFile , 'atad' , &m_sizeAudio[ nCntSound ] , &dwChunkPosition );
		if(FAILED(hr))
		{
			MessageBox( hWnd , L"�I�[�f�B�I�f�[�^�ǂݍ��݂Ɏ��s�I(1)" , L"�x���I" , MB_ICONWARNING );
			return S_FALSE;
		}
		m_pDataAudio[ nCntSound ] = ( BYTE* )malloc( m_sizeAudio[nCntSound] );
		hr = ReadChunkData( hFile , m_pDataAudio[nCntSound ] , m_sizeAudio[ nCntSound ] , dwChunkPosition );
		if( FAILED( hr ) )
		{
			MessageBox( hWnd , L"�I�[�f�B�I�f�[�^�ǂݍ��݂Ɏ��s�I(2)" , L"�x���I" , MB_ICONWARNING );
			return S_FALSE;
		}
	
		// �\�[�X�{�C�X�̐���
		hr = m_pXAudio2->CreateSourceVoice( &m_pSourceVoice[ nCntSound ] , &( wfx.Format ) );
		if( FAILED( hr ) )
		{
			MessageBox( hWnd , L"�\�[�X�{�C�X�̐����Ɏ��s�I" , L"�x���I" , MB_ICONWARNING );
			return S_FALSE;
		}

		memset( &buffer , 0 , sizeof( XAUDIO2_BUFFER ) );
		buffer.AudioBytes = m_sizeAudio[ nCntSound ];
		buffer.pAudioData = m_pDataAudio[ nCntSound ];
		buffer.Flags      = XAUDIO2_END_OF_STREAM;
		buffer.LoopCount  = 0;

		// �I�[�f�B�I�o�b�t�@�̓o�^
		m_pSourceVoice[ nCntSound ]->SubmitSourceBuffer( &buffer );
	}


	return S_OK;
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// �I��
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void CSound::Uninit( void )
{
	
	// �ꎞ��~
	for( int nCntSound = 0; nCntSound < SOUND_LABEL_MAX; nCntSound++ )
	{
		if( m_pSourceVoice[ nCntSound ] )
		{
			// �ꎞ��~
			m_pSourceVoice[ nCntSound ]->Stop(0);
	
			// �\�[�X�{�C�X�̔j��
			m_pSourceVoice[ nCntSound ]->DestroyVoice();
			m_pSourceVoice[ nCntSound ] = NULL;
	
			// �I�[�f�B�I�f�[�^�̊J��
			free( m_pDataAudio[ nCntSound ] );
			m_pDataAudio[ nCntSound ] = NULL;
		}
	}

	// �}�X�^�[�{�C�X�̔j��
	m_pMasteringVoice->DestroyVoice();
	m_pMasteringVoice = NULL;
	
	if( m_pXAudio2 )
	{
		// XAudio2�I�u�W�F�N�g�̊J��
		m_pXAudio2->Release();
		m_pXAudio2 = NULL;
	}
	
	// COM���C�u�����̏I������
	CoUninitialize();
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// �Đ�
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
HRESULT CSound::Play( SOUND_LABEL label )
{
	XAUDIO2_VOICE_STATE xa2state;
	XAUDIO2_BUFFER buffer;

	memset( &buffer , 0 , sizeof( XAUDIO2_BUFFER ) );
	buffer.AudioBytes = m_sizeAudio[ label ];
	buffer.pAudioData = m_pDataAudio[ label ];
	buffer.Flags      = XAUDIO2_END_OF_STREAM;
	buffer.LoopCount  = 0;
	if( c_param[ label ].bLoop )
	{
		buffer.LoopCount= XAUDIO2_LOOP_INFINITE;
	}

	// ��Ԏ擾
	m_pSourceVoice[ label ]->GetState( &xa2state );
	if(xa2state.BuffersQueued > 1)
	{// �Đ���

		return E_FAIL;
		// �ꎞ��~
		//m_pSourceVoice[ label ]->Stop(0);
		// �I�[�f�B�I�o�b�t�@�̍폜
		//m_pSourceVoice[ label ]->FlushSourceBuffers();
	}

	// �I�[�f�B�I�o�b�t�@�̓o�^
	m_pSourceVoice[ label ]->SubmitSourceBuffer(&buffer);

	// �Đ�
	m_pSourceVoice[ label ]->Start(0);

	return S_OK;
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// ��~
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void CSound::Stop( SOUND_LABEL label )
{
	XAUDIO2_VOICE_STATE xa2state;

	// ��Ԏ擾
	if( m_pSourceVoice[label] ==nullptr)
	{
		return;
	}
	m_pSourceVoice[label]->GetState(&xa2state);
	if( xa2state.BuffersQueued != 0 )
	{// �Đ���
		// �ꎞ��~
		m_pSourceVoice[label]->Stop(0);

		// �I�[�f�B�I�o�b�t�@�̍폜
		m_pSourceVoice[label]->FlushSourceBuffers();
	}
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// ��~
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void CSound::Stop( void )
{
	// �ꎞ��~
	for( int nCntSound = 0; nCntSound < SOUND_LABEL_MAX; nCntSound++ )
	{
		if( m_pSourceVoice[ nCntSound ] )
		{
			// �ꎞ��~
			m_pSourceVoice[ nCntSound ]->Stop( 0 );
		}
	}
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// ??
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
HRESULT CSound::CheckChunk( HANDLE hFile , DWORD format , DWORD *pChunkSize , DWORD *pChunkDataPosition )
{
	HRESULT hr = S_OK;
	DWORD dwRead;
	DWORD dwChunkType;
	DWORD dwChunkDataSize;
	DWORD dwRIFFDataSize = 0;
	DWORD dwFileType;
	DWORD dwBytesRead = 0;
	DWORD dwOffset = 0;
	
	if( SetFilePointer( hFile , 0 , NULL , FILE_BEGIN ) == INVALID_SET_FILE_POINTER)
	{// �t�@�C���|�C���^��擪�Ɉړ�
		return HRESULT_FROM_WIN32(GetLastError());
	}
	
	while( hr == S_OK )
	{
		if( ReadFile( hFile , &dwChunkType , sizeof( DWORD ) , &dwRead , NULL ) == 0 )
		{// �`�����N�̓ǂݍ���
			hr = HRESULT_FROM_WIN32( GetLastError() );
		}

		if( ReadFile( hFile , &dwChunkDataSize , sizeof( DWORD ) , &dwRead , NULL ) == 0 )
		{// �`�����N�f�[�^�̓ǂݍ���
			hr = HRESULT_FROM_WIN32( GetLastError() );
		}

		switch( dwChunkType )
		{
		case 'FFIR':
			dwRIFFDataSize  = dwChunkDataSize;
			dwChunkDataSize = 4;
			if( ReadFile( hFile , &dwFileType , sizeof(DWORD) , &dwRead , NULL ) == 0 )
			{// �t�@�C���^�C�v�̓ǂݍ���
				hr = HRESULT_FROM_WIN32( GetLastError() );
			}
			break;

		default:
			if( SetFilePointer( hFile , dwChunkDataSize, NULL , FILE_CURRENT ) == INVALID_SET_FILE_POINTER )
			{// �t�@�C���|�C���^���`�����N�f�[�^���ړ�
				return HRESULT_FROM_WIN32( GetLastError() );
			}
		}

		dwOffset += sizeof( DWORD ) * 2;
		if(dwChunkType == format)
		{
			*pChunkSize         = dwChunkDataSize;
			*pChunkDataPosition = dwOffset;

			return S_OK;
		}

		dwOffset += dwChunkDataSize;
		if(dwBytesRead >= dwRIFFDataSize)
		{
			return S_FALSE;
		}
	}
	return S_OK;
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// ??
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
HRESULT CSound::ReadChunkData( HANDLE hFile , void *pBuffer , DWORD dwBuffersize , DWORD dwBufferoffset )
{
	DWORD dwRead;
	
	if( SetFilePointer( hFile , dwBufferoffset , NULL , FILE_BEGIN ) == INVALID_SET_FILE_POINTER )
	{// �t�@�C���|�C���^���w��ʒu�܂ňړ�
		return HRESULT_FROM_WIN32( GetLastError() );
	}

	if( ReadFile( hFile , pBuffer , dwBuffersize , &dwRead , NULL ) == 0 )
	{// �f�[�^�̓ǂݍ���
		return HRESULT_FROM_WIN32(GetLastError());
	}
	return S_OK;
}