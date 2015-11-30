//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// 
// xactマネージャー
// 
// Created by Ryusei Kajiya on 20151021
// 
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//*****************************************************************************
// インクルード
#include "sound/xact/xact_manager.h"
#include "sound/xact/xact_manager.h"
#include "common/safe_delete.h"
#include "sound/speaker/speaker_bgm.h"
#include "sound/speaker/speaker_3d.h"

#include "System/application.h"
#include "Camera/camera_manager.h"
#include "Camera/Camera/camera_game_main.h"

//=============================================================================
// 初期化処理
bool XactManager::Initialize(void)
{
	ASSERT(InitializeEngine() == S_OK,"Xactエンジンの初期化失敗");
	ASSERT(InitializeWaveBank() == S_OK, "Waveバンクの初期化失敗");
	ASSERT(InitializeSoundBank() == S_OK, "サウンドバンクの初期化失敗");
	_xact_engine->DoWork();

	_speaker_3d = new Speaker3D(XACTCUEINDEX_WATER, _application);
	_speaker_bgm = new SpeakerBGM(XACTCUEINDEXBGM_GAME, _application);

	return true;
}

//=============================================================================
// 終了処理
void XactManager::Finalize(void)
{
	SafeDelete(_speaker_3d);
	SafeDelete(_speaker_bgm);

	if (_xact_engine != nullptr)
	{
		_xact_engine->ShutDown();
		_xact_engine->Release();
		_xact_engine = nullptr;
	}

	if (_streaming_wavebank_handle != INVALID_HANDLE_VALUE)
	{
		CloseHandle(_streaming_wavebank_handle);
		_streaming_wavebank_handle = nullptr;
	}

	if (_wavebank_in_memory_buffer != nullptr)
	{
		UnmapViewOfFile(_wavebank_in_memory_buffer);
	}

	SafeDeleteArray(_soundbank_buffer);

	SafeDeleteArray(_dsp_setting.pMatrixCoefficients);

	// COMの終了処理
	CoUninitialize();
}

//=============================================================================
// xactエンジン初期化処理
HRESULT XactManager::InitializeEngine(void)
{
	// COMの初期化
	CoInitializeEx(NULL, COINIT_MULTITHREADED);

	// xactエンジンの作成
	if (FAILED(XACT3CreateEngine(0, &_xact_engine)))
	{
		return E_FAIL;
	}

	// xgsファイルの読み込み
	HANDLE xgsfile_handle = INVALID_HANDLE_VALUE;
	void* xact_global_setting_buffer = nullptr;
	DWORD xact_global_setting_file_size;

#ifndef _RELEASE
	xgsfile_handle = CreateFileA(("Data/Sound/xact_project.xgs"),
#else
	xgsfile_handle = CreateFileA(("Data/Sound/xact_project.xgs"),
#endif
		GENERIC_READ, FILE_SHARE_READ, NULL,
		OPEN_EXISTING, 0, NULL);

	if (xgsfile_handle == INVALID_HANDLE_VALUE)
	{
		return E_FAIL;
	}

	xact_global_setting_file_size = GetFileSize(xgsfile_handle, NULL);

	if (xact_global_setting_file_size == INVALID_FILE_SIZE)
	{
		return E_FAIL;
	}

	xact_global_setting_buffer = CoTaskMemAlloc(xact_global_setting_file_size);

	if (xact_global_setting_buffer == nullptr)
	{
		return E_FAIL;
	}

	DWORD read_byte;

	BOOL read_result = ReadFile(
		xgsfile_handle, xact_global_setting_buffer,
		xact_global_setting_file_size, &read_byte, NULL);

	if (read_result == FALSE)
	{
		return E_FAIL;
	}

	CloseHandle(xgsfile_handle);

	// エンジンの初期化
	XACT_RUNTIME_PARAMETERS parameters = { 0 };
	parameters.lookAheadTime = XACT_ENGINE_LOOKAHEAD_DEFAULT;
	parameters.pGlobalSettingsBuffer = xact_global_setting_buffer;
	parameters.globalSettingsBufferSize = xact_global_setting_file_size;
	parameters.globalSettingsFlags = XACT_FLAG_GLOBAL_SETTINGS_MANAGEDATA;

	if (FAILED(_xact_engine->Initialize(&parameters)))
	{
		return E_FAIL;
	}

	// 3Dオーディオの初期化
	if (FAILED(XACT3DInitialize(_xact_engine, _x3daudio_handle)))
	{
		return E_FAIL;
	}

	WAVEFORMATEXTENSIBLE wave_format;
	_xact_engine->GetFinalMixFormat(&wave_format);

	_dsp_setting.SrcChannelCount = 1;
	_dsp_setting.DstChannelCount = wave_format.Format.nChannels;
	_dsp_setting.pMatrixCoefficients = 
	new FLOAT32[_dsp_setting.SrcChannelCount * _dsp_setting.DstChannelCount];

	return S_OK;
}

//=============================================================================
// ウェーブバンク初期化処理
//=============================================================================
HRESULT XactManager::InitializeWaveBank(void)
{
	HANDLE file_handle = INVALID_HANDLE_VALUE;

	// インメモリーの読み込み
#ifndef _RELEASE
	file_handle = CreateFileA(("Data/Sound/in_memory.xwb"),
#else
	file_handle = CreateFileA(("Data/Sound/in_memory.xwb"),
#endif
	GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING,
	0, NULL);

	if (file_handle == INVALID_HANDLE_VALUE)
	{
		return E_FAIL;
	}

	DWORD file_size = GetFileSize(file_handle, NULL);

	if (file_size == -1)
	{
		return E_FAIL;
	}

	HANDLE map_file_handle = CreateFileMapping(
		file_handle,
		NULL,
		PAGE_READONLY,
		0, file_size, NULL);

	if (map_file_handle == NULL)
	{
		return E_FAIL;
	}

	_wavebank_in_memory_buffer = MapViewOfFile(
		map_file_handle,
		FILE_MAP_READ,
		0, 0, 0);

	if (_wavebank_in_memory_buffer == NULL)
	{
		return E_FAIL;
	}

	HRESULT result= _xact_engine->CreateInMemoryWaveBank(
		_wavebank_in_memory_buffer,
		file_size, 0, 0,
		&_wavebank_in_memory);

	CloseHandle(map_file_handle);
	CloseHandle(file_handle);

	if (FAILED(result))
	{
		return E_FAIL;
	}

	// ストリーミングの読み取り
#ifndef _RELEASE
	_streaming_wavebank_handle = CreateFileA("Data/Sound/streaming.xwb",
#else
	_streaming_wavebank_handle = CreateFileA("Data/Sound/streaming.xwb",
#endif
		GENERIC_READ, FILE_SHARE_READ,
		NULL, OPEN_EXISTING,
		FILE_FLAG_OVERLAPPED |
		FILE_FLAG_NO_BUFFERING, NULL);

	if (_streaming_wavebank_handle == INVALID_HANDLE_VALUE)
	{
		return E_FAIL;
	}

	XACT_WAVEBANK_STREAMING_PARAMETERS streaming_parameters = {};
	streaming_parameters.file = _streaming_wavebank_handle;
	streaming_parameters.packetSize = 64;

	result = _xact_engine->CreateStreamingWaveBank(
		&streaming_parameters,
		&_wavebank_streaming);

	if (FAILED(result))
	{
		return E_FAIL;
	}

	return S_OK;
}

//=============================================================================
// サウンドバンク初期化処理
//=============================================================================
HRESULT XactManager::InitializeSoundBank(void)
{
#ifndef _RELEASE
	HANDLE file_handle = CreateFileA("Data/Sound/soundbank.xsb",
#else
	HANDLE file_handle = CreateFileA("Data/Sound/soundbank.xsb",
#endif
		GENERIC_READ, FILE_SHARE_READ, nullptr,
		OPEN_EXISTING, 0, nullptr);

	if (file_handle == INVALID_HANDLE_VALUE)
	{
		return E_FAIL;
	}

	DWORD file_size = GetFileSize(file_handle, nullptr);

	if (file_size == -1)
	{
		return E_FAIL;
	}

	_soundbank_buffer = new BYTE[file_size];

	if (_soundbank_buffer == nullptr)
	{
		return E_FAIL;
	}

	DWORD read_byte;

	BOOL read_result = ReadFile(
		file_handle,
		_soundbank_buffer,
		file_size,
		&read_byte,
		nullptr);

	if (read_result == FALSE)
	{
		return E_FAIL;
	}

	HRESULT result;
	result = _xact_engine->CreateSoundBank(
		_soundbank_buffer,
		file_size,
		0, 0, &_soundbank);

	CloseHandle(file_handle);

	if (FAILED(result))
	{
		return E_FAIL;
	}

	return S_OK;
}

//=============================================================================
// 更新処理
//=============================================================================
void XactManager::Update(void)
{
	// カメラの座標をリスナーにセットする
	CameraGameMain* camera = static_cast<CameraGameMain*>(_application->GetCameraManager()->GetCamera(CAMERA_TYPE_GAME_MAIN));
	
	_listener.Position = camera->GetVectorEye();
	_listener.OrientTop = camera->GetVectorUp();
	_listener.OrientFront = camera->GetVectorLookAt() - camera->GetVectorEye();

	_speaker_3d->Update();
	_speaker_bgm->Update();

	_xact_engine->DoWork();
}

