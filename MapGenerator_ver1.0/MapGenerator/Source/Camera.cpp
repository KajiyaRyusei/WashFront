//=============================================================================
//
// カメラクラス [Camera.cpp]
// Author : KEITA OHUCHI
//
//=============================================================================

#include "Camera.h"
#include "Manager.h"


//=========================================================================
// コンストラクタ
//=========================================================================
Camera::Camera()
{
	// メンバ変数の初期化
	position_ = D3DXVECTOR3(0.0f, 0.0f, 0.0f);  // 視点の座標
	lookPosition_ = D3DXVECTOR3(0.0f, 0.0f, 0.0f);  // 注視点の座標
	upperVector_ = D3DXVECTOR3(0.0f, 1.0f, 0.0f);  // 上方向ベクトル
	rotation_ = D3DXVECTOR3(0.0f, 0.0f, 0.0f);  // 向き
	D3DXMatrixIdentity(&viewMatrix_);  // ビューマトリクス
	D3DXMatrixIdentity(&projectionMatrix_);;  // プロジェクションマトリクス
	destRotation_ = rotation_;
}

//=========================================================================
// デストラクタ
//=========================================================================
Camera::~Camera()
{
}


//=========================================================================
// スクリーン座標からワールド座標への変換
//=========================================================================
D3DXVECTOR3 Camera::CalcScreenToWorld(D3DXVECTOR3 screenPosition, D3DXVECTOR2 windowSize)
{
	// 各行列の逆行列を算出
	D3DXMATRIX InvView, InvPrj, VP, InvViewport;
	D3DXMatrixInverse(&InvView, NULL, &viewMatrix_);
	D3DXMatrixInverse(&InvPrj, NULL, &projectionMatrix_);
	D3DXMatrixIdentity(&VP);
	VP._11 = windowSize.x / 2.0f; VP._22 = -windowSize.y / 2.0f;
	VP._41 = windowSize.x / 2.0f; VP._42 = windowSize.y / 2.0f;
	D3DXMatrixInverse(&InvViewport, NULL, &VP);

	// 逆変換
	D3DXVECTOR3 worldPosition;
	D3DXMATRIX tmp = InvViewport * InvPrj * InvView;
	D3DXVec3TransformCoord(&worldPosition, &screenPosition, &tmp);

	return worldPosition;
}


// End of file