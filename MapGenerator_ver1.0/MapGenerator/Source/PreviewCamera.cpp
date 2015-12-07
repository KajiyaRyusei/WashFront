//=============================================================================
//
// プレビュー用カメラクラス [PreviewCamera.cpp]
// Author : KEITA OHUCHI
//
//=============================================================================

#include "Main.h"
#include "PreviewCamera.h"
#include "Manager.h"
#include "ObjectManager.h"
#include "Keyboard.h"
#include "Mouse.h"
#include "RouteManager.h"


//-----------------------------------------------------------------------------
// マクロ定義
//-----------------------------------------------------------------------------
#define DEFAULT_POSITION (D3DXVECTOR3(0.f, 30.f, -50.f))
#define DEFAULT_LOOK_POSITION (D3DXVECTOR3(0.f, 0.f, 0.0f))

#define CAMERA_ROT_DAMPING	(0.15f)	// カメラの回転の割合
#define CAMERA_MOVE_DAMPING	(0.3f)	// カメラの移動の割合
#define CAMERA_HEIGHT		(1.0f)	// フィールドから視点までの高さ
#define LOOK_POS_LENGTH		(0.4f)	// プレイヤーから注視点までの距離

#define CAMERA_SPEED		(0.05f)

#define CAMERA_HEIGHT_MIN	(0.5f)	// 視点の最低点


//=========================================================================
// コンストラクタ
//=========================================================================
PreviewCamera::PreviewCamera() :
time_(0),
length_(0)
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
PreviewCamera::~PreviewCamera()
{
}

//=========================================================================
// 初期化処理
//=========================================================================
HRESULT PreviewCamera::Init()
{
	time_ = 0.0f;
	length_ = 3.0f;

	currentPoint_ = Manager::GetInstance()->GetRouteManager()->GetRoutePoint((int)time_);
	nextPoint_ = Manager::GetInstance()->GetRouteManager()->GetRoutePoint((int)time_ + 1);


	return S_OK;
}

//=========================================================================
// 更新処理
//=========================================================================
void PreviewCamera::Update()
{
	D3DXVECTOR3 cameraDirection(0, 0, length_);

	time_ += 0.01f;
	int cursor = (int)time_;
	currentPoint_ = Manager::GetInstance()->GetRouteManager()->GetRoutePoint(cursor);
	nextPoint_ = Manager::GetInstance()->GetRouteManager()->GetRoutePoint(cursor + 1);


	float t = time_ - cursor;

	//D3DXVECTOR3 rotation = currentPoint_.rotation * (1 - t) + nextPoint_.rotation * t;

	//D3DXMATRIX m;
	//D3DXMatrixIdentity(&m);
	//D3DXMatrixRotationYawPitchRoll(&m, rotation.y, rotation.x, rotation.z);
	//D3DXVec3TransformCoord(&cameraDirection, &cameraDirection, &m);


	D3DXQUATERNION q, q1, q2;
	D3DXMATRIX m, m1, m2;
	D3DXMatrixIdentity(&m1);
	D3DXMatrixRotationYawPitchRoll(&m1, currentPoint_.rotation.y, currentPoint_.rotation.x, currentPoint_.rotation.z);
	D3DXMatrixIdentity(&m2);
	D3DXMatrixRotationYawPitchRoll(&m2, nextPoint_.rotation.y, nextPoint_.rotation.x, nextPoint_.rotation.z);
	D3DXQuaternionRotationMatrix(&q1, &m1);
	D3DXQuaternionRotationMatrix(&q2, &m2);

	D3DXQuaternionSlerp(&q, &q1, &q2, t);
	D3DXMatrixRotationQuaternion(&m, &q);

	D3DXVec3TransformCoord(&cameraDirection, &cameraDirection, &m);


	position_ = currentPoint_.position * (1 - t) + nextPoint_.position * t;
	lookPosition_ = position_ + cameraDirection;

}


// End of file