//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// プレイヤー用カメラ
//
// Created by Ryusei Kajiya on 20151022
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//*****************************************************************************
// 多重インクルード防止
#pragma once

//*****************************************************************************
// include
#include "camera.h"

//*****************************************************************************
// クラス設計
class CameraGamePlayer : public Camera
{
public:

	CameraGamePlayer(Application* application) : Camera(application) { Initialize(); }
	virtual ~CameraGamePlayer(){}

	// 初期化
	virtual void Initialize() override;

	// プロジェクションとビュー行列作成
	virtual void CreateMatrix() override;

	// プレイヤーの座標をセット
	void SetPlayerPosition(D3DXVECTOR3 position){ _player_position = position; }

	// ローテーションを取得
	D3DXVECTOR3& GetCameraRotation(){ return _rotation; }

private:

	
	void Chase();
	void Input();

	// プレイヤーの座標
	D3DXVECTOR3 _player_position;
	// 回転関係
	D3DXVECTOR3 _rotation;
	D3DXVECTOR3 _destnation_rotation_velocity;
	D3DXVECTOR3 _rotation_velocity;
};