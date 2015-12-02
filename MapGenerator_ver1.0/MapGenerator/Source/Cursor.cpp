//=============================================================================
//
// カーソル [Cursor.cpp]
// Author : KEITA OHUCHI
//
//=============================================================================

#include "Main.h"
#include "Cursor.h"
#include "Renderer.h"
#include "ObjectManager.h"
#include "CameraManager.h"
#include "Camera.h"
#include "Manager.h"
#include "Mouse.h"
#include "Debug.h"
#include "TextureFactory.h"


//-----------------------------------------------------------------------------
// マクロ定義
//-----------------------------------------------------------------------------
#define POLYGON_WIDTH (1.0f)
#define POLYGON_HEIGHT (1.0f)


//=========================================================================
// コンストラクタ
//=========================================================================
Cursor::Cursor(int priority) : SceneBillboard(priority)
{
}

//=========================================================================
// デストラクタ
//=========================================================================
Cursor::~Cursor()
{
}

//=========================================================================
// 初期化処理
//=========================================================================
HRESULT Cursor::Init()
{
	// 頂点座標の設定
	Renderer *renderer = Manager::GetInstance()->GetRenderer();
	LPDIRECT3DDEVICE9 device = renderer->GetDevice();

	// 頂点バッファの生成（メモリの確保）
	if (FAILED(device->CreateVertexBuffer(
		sizeof(VERTEX_3D)* 4,  // 確保するメモリのサイズ
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,  // 使用する頂点フォーマット
		D3DPOOL_MANAGED,
		&vertexBuffer_,  // 頂点バッファの先頭アドレスの入ったポインタ変数のアドレス
		nullptr))) {
		return E_FAIL;
	}

	float fAngle = atan2f(POLYGON_WIDTH / 2, POLYGON_HEIGHT / 2);  // 対角線のなす角初期化
	float fLength = sqrtf((POLYGON_WIDTH / 2) * (POLYGON_WIDTH / 2)
		+ (POLYGON_HEIGHT / 2) * (POLYGON_HEIGHT / 2));  // 対角線の長さ初期化

	// 頂点座標の設定
	VERTEX_3D *pVtx;
	vertexBuffer_->Lock(0, 0, (void**)&pVtx, 0);  // 頂点情報をロック

	pVtx[0].vtx = D3DXVECTOR3(-sinf(fAngle) * fLength, cosf(fAngle) * fLength, 0.0f);
	pVtx[1].vtx = D3DXVECTOR3(sinf(fAngle) * fLength, cosf(fAngle) * fLength, 0.0f);
	pVtx[2].vtx = D3DXVECTOR3(-sinf(fAngle) * fLength, -cosf(fAngle) * fLength, 0.0f);
	pVtx[3].vtx = D3DXVECTOR3(sinf(fAngle) * fLength, -cosf(fAngle) * fLength, 0.0f);

	pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	pVtx[0].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	// テクスチャ情報の初期化
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	vertexBuffer_->Unlock();  // 頂点情報をアンロック


	texture_ = Manager::GetInstance()->GetTextureFactory()->GetTexture(
		"./Resource/Texture/Game/texture000.png");


	return S_OK;
}

//=========================================================================
// 更新処理
//=========================================================================
void Cursor::Update()
{
	Camera *camera = Manager::GetInstance()->GetCameraManager()->GetCamera();

	// ウィンドウ情報取得
	HWND hWnd = GetWindowHandle();
	RECT rectWindow, rectClient;
	GetWindowRect(hWnd, &rectWindow);
	GetClientRect(hWnd, &rectClient);

	// マウスのスクリーン座標
	POINT screenPosition;
	GetCursorPos(&screenPosition);
	ScreenToClient(hWnd, &screenPosition);


	// マウスのレイ
	D3DXVECTOR3 nearPosition;
	D3DXVECTOR3 farPosition;
	D3DXVECTOR3 ray;
	nearPosition = camera->CalcScreenToWorld(D3DXVECTOR3((float)screenPosition.x, (float)screenPosition.y, 0.0f),
		D3DXVECTOR2((float)rectClient.right, (float)rectClient.bottom));
	farPosition = camera->CalcScreenToWorld(D3DXVECTOR3((float)screenPosition.x, (float)screenPosition.y, 1.0f),
		D3DXVECTOR2((float)rectClient.right, (float)rectClient.bottom));
	ray = farPosition - nearPosition;
	float length1 = nearPosition.y;
	float length2 = -farPosition.y;
	D3DXVECTOR3 v12 = ray * length1 / (length1 + length2);

	position_ = nearPosition + v12;

}

//=========================================================================
// 描画処理
//=========================================================================
void Cursor::Draw()
{
	if (GetMode() == MODE_ROUTE) {
		Renderer *renderer = Manager::GetInstance()->GetRenderer();
		LPDIRECT3DDEVICE9 device = renderer->GetDevice();

		device->SetRenderState(D3DRS_ZENABLE, false);
		SceneBillboard::Draw();
		device->SetRenderState(D3DRS_ZENABLE, true);
	}
}


// End of file