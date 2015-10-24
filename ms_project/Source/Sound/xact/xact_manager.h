//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// 
// xactマネージャー
// 
// Created by Ryusei Kajiya on 20151021
// 
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//*****************************************************************************
// 多重インクルード防止
#pragma once


//*****************************************************************************
// 前方宣言
class Speaker3D;
class SpeakerBGM;
class Application;

//*****************************************************************************
// クラス設計
class XactManager
{
public:
	XactManager(Application* application) :
	_xact_engine(nullptr),
	_soundbank(nullptr),
	_soundbank_buffer(nullptr),
	_wavebank_in_memory(nullptr),
	_wavebank_in_memory_buffer(nullptr),
	_streaming_wavebank_handle(INVALID_HANDLE_VALUE),
	_application(application)
	{
		ZeroMemory(&_x3daudio_handle, sizeof(_x3daudio_handle));
		ZeroMemory(&_dsp_setting, sizeof(_dsp_setting));
		ZeroMemory(&_listener, sizeof(_listener));
		_listener.OrientFront = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
		_listener.OrientTop = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		_listener.Position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		_listener.Velocity = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		Initialize();
	}
	
	
	virtual ~XactManager(void)
	{
		Finalize();
	}
	bool Initialize(void);
	void Finalize(void);
	void Update(void);

	X3DAUDIO_HANDLE* GetHandleX3daudio(void){ return &_x3daudio_handle; }
	X3DAUDIO_DSP_SETTINGS GetDspSeetting(void){ return _dsp_setting; }
	X3DAUDIO_LISTENER GetListener(void){ return _listener; }
	IXACT3SoundBank* GetSoundbank(void){ return _soundbank; }
	IXACT3WaveBank* GetWavebankInMemory(void){ return _wavebank_in_memory; }
	IXACT3WaveBank* GetWavebankStreaming(void){ return _wavebank_streaming; }
	IXACT3Engine* GetXactEngine(void){ return _xact_engine; }

	Speaker3D* Get3DSound(){ return _speaker_3d; }
	SpeakerBGM* GetBGMSound(){ return _speaker_bgm; }


private:

	// xactエンジンの初期化
	HRESULT InitializeEngine(void);

	// ウェーブバンク(InMemory/Streaming)の初期化
	HRESULT InitializeWaveBank(void);

	// サウンドバンクの初期化
	HRESULT InitializeSoundBank(void);

	IXACT3Engine* _xact_engine;
	IXACT3WaveBank* _wavebank_streaming;
	IXACT3WaveBank* _wavebank_in_memory;
	IXACT3SoundBank* _soundbank;
	X3DAUDIO_HANDLE _x3daudio_handle;
	X3DAUDIO_DSP_SETTINGS _dsp_setting;
	void* _wavebank_in_memory_buffer;
	BYTE* _soundbank_buffer;
	HANDLE _streaming_wavebank_handle;
	X3DAUDIO_LISTENER _listener;

	Speaker3D* _speaker_3d;
	SpeakerBGM* _speaker_bgm;

	// アプリケーション
	Application* _application;

};