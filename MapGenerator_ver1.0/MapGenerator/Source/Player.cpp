//=============================================================================
//
// プレイヤークラス [Player.cpp]
// Author : KEITA OHUCHI
//
//=============================================================================

#include "Main.h"
#include "Player.h"


//=============================================================================
// コンストラクタ
//=============================================================================
Player::Player(int priority) : Scene(priority)
{
	// メンバ変数のクリア
	type_ = OBJECTTYPE_PLAYER;

	rotation_ = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	destRotation_ = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	velocity_ = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	frontVector_ = D3DXVECTOR3(0, 0, 1);

	D3DXMatrixIdentity(&rotationMatrix_);
	D3DXMatrixIdentity(&worldMatrix_);

	id_ = 0;

	motionType_ = MOTION_TYPE_NEUTRAL;
	motionTime_ = 0.0f;
	keyNum_ = 0;
	motionEndFlag_ = false;
	motionLoopFlag_ = false;

	prevMotionType_ = MOTION_TYPE_NEUTRAL;
	prevMotionTime_ = 0.0f;
	prevKeyNum_ = 0;
	prevMotionLoopFlag_ = false;

	frameBlend_ = 0;
	motionTimeBlend_ = 0.0f;
	motionBlendFlag_ = false;
}

//=============================================================================
// デストラクタ
//=============================================================================
Player::~Player()
{
}


// End of file