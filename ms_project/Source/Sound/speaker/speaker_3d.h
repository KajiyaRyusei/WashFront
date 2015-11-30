//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// 
// 3Dサウンドスピーカー
// 
// Created by Ryusei Kajiya on 20151021
// 
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//*****************************************************************************
// 多重インクルード防止
#pragma once

//*****************************************************************************
// include
#include "speaker.h"

//*****************************************************************************
// 前方宣言
class Application;

//*****************************************************************************
// クラス設計
class Speaker3D : public Speaker
{
public:
	Speaker3D(XactCueIndex cue_index, Application* application) :
		Speaker(cue_index, application)
	{
		_emitter.pCone = nullptr;
		_emitter.OrientFront = D3DXVECTOR3(0.0f, 0.0f, 1.0f);         // エミッタの正面ベクトル
		_emitter.OrientTop = D3DXVECTOR3(0.0f, 1.0f, 0.0f);             // エミッタの上ベクトル
		_emitter.Position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);            // エミッタの座標
		_emitter.Velocity = D3DXVECTOR3(0.0f, 0.0f, 0.0f);            // エミッタの速度(ドップラーに使用)
		_emitter.ChannelCount = 1;                                    // エミッタのチャンネルカウント(エミッタの数。0より大きい値を指定)
		_emitter.ChannelRadius = 0.0f;                                // チャンネルカウントが1以上の場合にエミッタが配置される座標からの距離。マルチチャンネルエミッタで使用
		_emitter.CurveDistanceScaler = 1.0f;                          // カーブ距離スケーラ(#1)
		_emitter.pChannelAzimuths = nullptr;                          // ラジアン単位の方位角で表したチャンネル位置テーブル。マルチチャンネルエミッタで使用
		_emitter.pVolumeCurve = nullptr;                              // ボリュームレベルカーブ(#1)
		_emitter.pLFECurve = nullptr;                                 // LFE ロールオフ距離カーブ(#1)
		_emitter.pLPFDirectCurve = nullptr;                           // ローパス フィルター (LPF) ダイレクト パス係数距離カーブ(#1)
		_emitter.pLPFReverbCurve = nullptr;                           // LPF リバーブ パス係数距離カーブ(#1)
		_emitter.pReverbCurve = nullptr;                              // リバーブ センド レベル距離カーブ(#1)
		_emitter.DopplerScaler = 1.0f;                                // ドップラー偏移効果を強調するために使用するドップラー偏移スケーラー(#1)
		_emitter.InnerRadius = 10.0f;                                 // 内部半径の計算に使用される値(これをうまく設定しないと、エミッタ座標がリスナー座標に重なったとき音が変になる)
	}
	virtual ~Speaker3D(){}
	bool Play(void);
	void Pause(void);
	void Stop(void);

	bool IsPlaying(void) const;

	void Update(void);

	void SetEmitterPosition(D3DXVECTOR3 position)
	{
		_emitter.Position = position;
	}

private:
	X3DAUDIO_EMITTER _emitter;
};
