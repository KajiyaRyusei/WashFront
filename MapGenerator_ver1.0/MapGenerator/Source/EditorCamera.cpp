//=============================================================================
//
// エディット用カメラクラス [EditorCamera.cpp]
// Author : KEITA OHUCHI
//
//=============================================================================

#include "Main.h"
#include "EditorCamera.h"
#include "Manager.h"
#include "ObjectManager.h"
#include "Keyboard.h"
#include "Mouse.h"


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
EditorCamera::EditorCamera()
{
	// メンバ変数の初期化
	position_ = D3DXVECTOR3(0.0f, 0.0f, 0.0f);  // 視点の座標
	lookPosition_ = D3DXVECTOR3(0.0f, 0.0f, 0.0f);  // 注視点の座標
	upperVector_ = D3DXVECTOR3(0.0f, 1.0f, 0.0f);  // 上方向ベクトル
	rotation_ = D3DXVECTOR3(0.0f, 0.0f, 0.0f);  // 向き
	D3DXMatrixIdentity(&viewMatrix_);  // ビューマトリクス
	D3DXMatrixIdentity(&projectionMatrix_);  // プロジェクションマトリクス
	destRotation_ = rotation_;
}

//=========================================================================
// デストラクタ
//=========================================================================
EditorCamera::~EditorCamera()
{
}

//=========================================================================
// 初期化処理
//=========================================================================
HRESULT EditorCamera::Init(D3DXVECTOR3 pos, D3DXVECTOR3 look_pos)
{
	// メンバ変数の初期化
	position_ = pos;
	lookPosition_ = look_pos;

	// 高さの取得
	/*
	Game *game = Manager::GetInstance()->GetGame();
	MeshField *field = game->GetField();
	float height = field->GetHeight(position_);
	position_.y = m_dest_pos.y = height + CAMERA_HEIGHT;

	Player *player = game->GetPlayer();
	D3DXVECTOR3 player_pos = player->GetPosition();
	lookPosition_.y = m_dest_look_pos.y = player_pos.y;
	*/
	return S_OK;
}

HRESULT EditorCamera::Init()
{
	position_ = DEFAULT_POSITION;
	lookPosition_ = DEFAULT_LOOK_POSITION;

	upperVector_ = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	rotation_ = D3DXVECTOR3(atan2f(lookPosition_.y - position_.y, lookPosition_.z - position_.z),
		atan2f(lookPosition_.x - position_.x, lookPosition_.z - position_.z),
		atan2f(lookPosition_.x - position_.x, lookPosition_.y - position_.y));

	length_ = sqrtf((lookPosition_.x - position_.x) * (lookPosition_.x - position_.x)
		+ (lookPosition_.y - position_.y) * (lookPosition_.y - position_.y)
		+ (lookPosition_.z - position_.z) * (lookPosition_.z - position_.z));


	return S_OK;
}

//=========================================================================
// 更新処理
//=========================================================================
void EditorCamera::Update()
{
	Mouse *mouse = Manager::GetInstance()->GetMouse();
	DIMOUSESTATE state = mouse->GetPressMouse();

	// マウスホイールクリックで平行移動
	if (state.rgbButtons[BUTTON_SCROLL] & BUTTON_MASK) {
		// カメラの視点の更新
		position_.x += sinf(rotation_.y - D3DX_PI / 2) * state.lX * CAMERA_SPEED * (length_ * 0.1f);
		position_.y += sinf(rotation_.x + D3DX_PI / 2) * state.lY * CAMERA_SPEED * (length_ * 0.1f);
		position_.z += cosf(rotation_.y - D3DX_PI / 2) * state.lX * CAMERA_SPEED * (length_ * 0.1f);

		// カメラの注視点の更新
		lookPosition_.x = position_.x + sinf(rotation_.y) * cosf(rotation_.x) * length_;
		lookPosition_.y = position_.y + sinf(rotation_.x) * length_;
		lookPosition_.z = position_.z + cosf(rotation_.y) * cosf(rotation_.x) * length_;
	} else {
		// マウスホイールでズーム
		length_ -= 0.03f * state.lZ;
		if (length_ < 0.2f) {
			length_ = 0.2f;
		}

		// 右クリック中視点移動
		if (state.rgbButtons[BUTTON_RIGHT] & BUTTON_MASK) {
			rotation_.y += 0.01f * state.lX;
			if (rotation_.y < -D3DX_PI) {
				rotation_.y += D3DX_PI * 2;
			}
			else if (D3DX_PI < rotation_.y) {
				rotation_.y -= D3DX_PI * 2;
			}
			rotation_.x -= 0.01f * state.lY;
			if (rotation_.x < -D3DX_PI * 0.4999f) {
				rotation_.x = -D3DX_PI * 0.4999f;
			}
			else if (D3DX_PI * 0.4999f < rotation_.x) {
				rotation_.x = D3DX_PI * 0.4999f;
			}
		}

		position_.x = lookPosition_.x - sinf(rotation_.y) * cosf(rotation_.x) * length_;
		position_.y = lookPosition_.y - sinf(rotation_.x) * length_;
		position_.z = lookPosition_.z - cosf(rotation_.y) * cosf(rotation_.x) * length_;
	}

}

//=========================================================================
// 描画処理
//=========================================================================
void EditorCamera::Set()
{
	Renderer *renderer = Manager::GetInstance()->GetRenderer();
	LPDIRECT3DDEVICE9 device = renderer->GetDevice();

	// ビューマトリクスの設定
	D3DXMatrixIdentity(&viewMatrix_);  // 単位行列で初期化
	D3DXMatrixLookAtLH(&viewMatrix_, &position_, &lookPosition_, &upperVector_);
	device->SetTransform(D3DTS_VIEW, &viewMatrix_);


	// プロジェクションマトリクスの設定
	D3DXMatrixIdentity(&projectionMatrix_);  // 単位行列で初期化
	D3DXMatrixPerspectiveFovLH(
		&projectionMatrix_,  // プロジェクションマトリクスの生成
		D3DX_PI / 4.0f,  // 視野角(π/4)
		(float)SCREEN_WIDTH / (float)SCREEN_HEIGHT,  // アスペクト比(幅 / 高さ)
		0.1f,  // near値
		1000.0f);  // far値
	device->SetTransform(D3DTS_PROJECTION, &projectionMatrix_);


	D3DVIEWPORT9 viewport;
	viewport.X = 0;
	viewport.Y = 0;
	viewport.Width = SCREEN_WIDTH;
	viewport.Height = SCREEN_HEIGHT;
	viewport.MinZ = 0.0f;
	viewport.MaxZ = 1.0f;
	device->SetViewport(&viewport);
}

// End of file