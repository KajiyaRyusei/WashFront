//=============================================================================
//
// サウンド処理[sound.cpp]
// 製作日 2014 / 9 /  1
// 更新日 2015 / 3 / 18
// Author : 20274	望月 利紀
//
//=============================================================================

//*****************************************************************************
// インクルードファイル
//*****************************************************************************
#include "sound.h"

//*****************************************************************************
// const変数
//*****************************************************************************
// 各音素材のパラメータ
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
// define定義
//*****************************************************************************

//*****************************************************************************
// static変数
//*****************************************************************************


//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// コンストラクタ
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
CSound::CSound( void )
{
	// メンバ変数初期化
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
// デストラクタ
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
CSound::~CSound( void )
{

}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// 初期化
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
HRESULT CSound::Init( HWND hWnd )
{
	HRESULT hr;

	// COMライブラリの初期化
	CoInitializeEx( NULL , COINIT_MULTITHREADED );

	// XAudio2オブジェクトの作成
	hr = XAudio2Create( &m_pXAudio2 , 0 );
	if( FAILED( hr ) )
	{
		MessageBox( hWnd , L"XAudio2オブジェクトの作成に失敗！", L"警告！", MB_ICONWARNING );

		// COMライブラリの終了処理
		CoUninitialize();
		return E_FAIL;
	}
	
	// マスターボイスの生成
	hr = m_pXAudio2->CreateMasteringVoice( &m_pMasteringVoice );
	if( FAILED( hr ) )
	{
		MessageBox( hWnd , L"マスターボイスの生成に失敗！", L"警告！", MB_ICONWARNING );

		if( m_pXAudio2 )
		{
			// XAudio2オブジェクトの開放
			m_pXAudio2->Release();
			m_pXAudio2 = NULL;
		}

		// COMライブラリの終了処理
		CoUninitialize();

		return E_FAIL;
	}

	// サウンドデータの初期化
	for( int nCntSound = 0; nCntSound < SOUND_LABEL_MAX; nCntSound++ )
	{
		HANDLE hFile;
		DWORD dwChunkSize = 0;
		DWORD dwChunkPosition = 0;
		DWORD dwFiletype;
		WAVEFORMATEXTENSIBLE wfx;
		XAUDIO2_BUFFER buffer;

		// バッファのクリア
		memset( &wfx , 0 , sizeof( WAVEFORMATEXTENSIBLE ) );
		memset( &buffer , 0 , sizeof( XAUDIO2_BUFFER  ) );

		

		// サウンドデータファイルの生成
		hFile = CreateFile( ( LPCWSTR )c_param[ nCntSound ].filename , GENERIC_READ , FILE_SHARE_READ , NULL , OPEN_EXISTING , 0 , NULL );
		if(hFile == INVALID_HANDLE_VALUE)
		{
			MessageBox( hWnd , L"サウンドデータファイルの生成に失敗！(1)" , L"警告！" , MB_ICONWARNING );
			return HRESULT_FROM_WIN32( GetLastError() );
		}
		if(SetFilePointer( hFile , 0 , NULL , FILE_BEGIN ) == INVALID_SET_FILE_POINTER )
		{// ファイルポインタを先頭に移動
			MessageBox( hWnd , L"サウンドデータファイルの生成に失敗！(2)" , L"警告！" , MB_ICONWARNING );
			return HRESULT_FROM_WIN32( GetLastError() );
		}
	
		// WAVEファイルのチェック
		hr = CheckChunk(hFile, 'FFIR', &dwChunkSize, &dwChunkPosition);
		if( FAILED( hr ) )
		{
			MessageBox( hWnd , L"WAVEファイルのチェックに失敗！(1)" , L"警告！" , MB_ICONWARNING );
			return S_FALSE;
		}
		hr = ReadChunkData( hFile , &dwFiletype , sizeof( DWORD ) , dwChunkPosition );
		if( FAILED( hr ) )
		{
			MessageBox( hWnd , L"WAVEファイルのチェックに失敗！(2)" , L"警告！" , MB_ICONWARNING );
			return S_FALSE;
		}
		if( dwFiletype != 'EVAW' )
		{
			MessageBox( hWnd , L"WAVEファイルのチェックに失敗！(3)" , L"警告！" , MB_ICONWARNING );
			return S_FALSE;
		}
	
		// フォーマットチェック
		hr = CheckChunk( hFile , ' tmf' , &dwChunkSize , &dwChunkPosition );
		if( FAILED( hr ) )
		{
			MessageBox( hWnd , L"フォーマットチェックに失敗！(1)" , L"警告！" , MB_ICONWARNING );
			return S_FALSE;
		}
		hr = ReadChunkData( hFile , &wfx , dwChunkSize , dwChunkPosition );
		if(FAILED(hr))
		{
			MessageBox( hWnd , L"フォーマットチェックに失敗！(2)" , L"警告！" , MB_ICONWARNING );
			return S_FALSE;
		}

		// オーディオデータ読み込み
		hr = CheckChunk( hFile , 'atad' , &m_sizeAudio[ nCntSound ] , &dwChunkPosition );
		if(FAILED(hr))
		{
			MessageBox( hWnd , L"オーディオデータ読み込みに失敗！(1)" , L"警告！" , MB_ICONWARNING );
			return S_FALSE;
		}
		m_pDataAudio[ nCntSound ] = ( BYTE* )malloc( m_sizeAudio[nCntSound] );
		hr = ReadChunkData( hFile , m_pDataAudio[nCntSound ] , m_sizeAudio[ nCntSound ] , dwChunkPosition );
		if( FAILED( hr ) )
		{
			MessageBox( hWnd , L"オーディオデータ読み込みに失敗！(2)" , L"警告！" , MB_ICONWARNING );
			return S_FALSE;
		}
	
		// ソースボイスの生成
		hr = m_pXAudio2->CreateSourceVoice( &m_pSourceVoice[ nCntSound ] , &( wfx.Format ) );
		if( FAILED( hr ) )
		{
			MessageBox( hWnd , L"ソースボイスの生成に失敗！" , L"警告！" , MB_ICONWARNING );
			return S_FALSE;
		}

		memset( &buffer , 0 , sizeof( XAUDIO2_BUFFER ) );
		buffer.AudioBytes = m_sizeAudio[ nCntSound ];
		buffer.pAudioData = m_pDataAudio[ nCntSound ];
		buffer.Flags      = XAUDIO2_END_OF_STREAM;
		buffer.LoopCount  = 0;

		// オーディオバッファの登録
		m_pSourceVoice[ nCntSound ]->SubmitSourceBuffer( &buffer );
	}


	return S_OK;
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// 終了
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void CSound::Uninit( void )
{
	
	// 一時停止
	for( int nCntSound = 0; nCntSound < SOUND_LABEL_MAX; nCntSound++ )
	{
		if( m_pSourceVoice[ nCntSound ] )
		{
			// 一時停止
			m_pSourceVoice[ nCntSound ]->Stop(0);
	
			// ソースボイスの破棄
			m_pSourceVoice[ nCntSound ]->DestroyVoice();
			m_pSourceVoice[ nCntSound ] = NULL;
	
			// オーディオデータの開放
			free( m_pDataAudio[ nCntSound ] );
			m_pDataAudio[ nCntSound ] = NULL;
		}
	}

	// マスターボイスの破棄
	m_pMasteringVoice->DestroyVoice();
	m_pMasteringVoice = NULL;
	
	if( m_pXAudio2 )
	{
		// XAudio2オブジェクトの開放
		m_pXAudio2->Release();
		m_pXAudio2 = NULL;
	}
	
	// COMライブラリの終了処理
	CoUninitialize();
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// 再生
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

	// 状態取得
	m_pSourceVoice[ label ]->GetState( &xa2state );
	if(xa2state.BuffersQueued > 1)
	{// 再生中

		return E_FAIL;
		// 一時停止
		//m_pSourceVoice[ label ]->Stop(0);
		// オーディオバッファの削除
		//m_pSourceVoice[ label ]->FlushSourceBuffers();
	}

	// オーディオバッファの登録
	m_pSourceVoice[ label ]->SubmitSourceBuffer(&buffer);

	// 再生
	m_pSourceVoice[ label ]->Start(0);

	return S_OK;
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// 停止
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void CSound::Stop( SOUND_LABEL label )
{
	XAUDIO2_VOICE_STATE xa2state;

	// 状態取得
	if( m_pSourceVoice[label] ==nullptr)
	{
		return;
	}
	m_pSourceVoice[label]->GetState(&xa2state);
	if( xa2state.BuffersQueued != 0 )
	{// 再生中
		// 一時停止
		m_pSourceVoice[label]->Stop(0);

		// オーディオバッファの削除
		m_pSourceVoice[label]->FlushSourceBuffers();
	}
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// 停止
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void CSound::Stop( void )
{
	// 一時停止
	for( int nCntSound = 0; nCntSound < SOUND_LABEL_MAX; nCntSound++ )
	{
		if( m_pSourceVoice[ nCntSound ] )
		{
			// 一時停止
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
	{// ファイルポインタを先頭に移動
		return HRESULT_FROM_WIN32(GetLastError());
	}
	
	while( hr == S_OK )
	{
		if( ReadFile( hFile , &dwChunkType , sizeof( DWORD ) , &dwRead , NULL ) == 0 )
		{// チャンクの読み込み
			hr = HRESULT_FROM_WIN32( GetLastError() );
		}

		if( ReadFile( hFile , &dwChunkDataSize , sizeof( DWORD ) , &dwRead , NULL ) == 0 )
		{// チャンクデータの読み込み
			hr = HRESULT_FROM_WIN32( GetLastError() );
		}

		switch( dwChunkType )
		{
		case 'FFIR':
			dwRIFFDataSize  = dwChunkDataSize;
			dwChunkDataSize = 4;
			if( ReadFile( hFile , &dwFileType , sizeof(DWORD) , &dwRead , NULL ) == 0 )
			{// ファイルタイプの読み込み
				hr = HRESULT_FROM_WIN32( GetLastError() );
			}
			break;

		default:
			if( SetFilePointer( hFile , dwChunkDataSize, NULL , FILE_CURRENT ) == INVALID_SET_FILE_POINTER )
			{// ファイルポインタをチャンクデータ分移動
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
	{// ファイルポインタを指定位置まで移動
		return HRESULT_FROM_WIN32( GetLastError() );
	}

	if( ReadFile( hFile , pBuffer , dwBuffersize , &dwRead , NULL ) == 0 )
	{// データの読み込み
		return HRESULT_FROM_WIN32(GetLastError());
	}
	return S_OK;
}