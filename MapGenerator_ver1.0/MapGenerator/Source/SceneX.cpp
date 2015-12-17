//=============================================================================
//
// Xファイルモデルクラス [SceneX.cpp]
// Author : KEITA OHUCHI
//
//=============================================================================

#include "Main.h"
#include "SceneX.h"
#include "Manager.h"
#include "Keyboard.h"
#include "ModelFactory.h"
#include "Debug.h"


//=============================================================================
// コンストラクタ
//=============================================================================
SceneX::SceneX(int priority) : Scene(priority)
{
	// メンバ変数の初期化
	model_ = nullptr;
	D3DXMatrixIdentity(&worldMatrix_);
	scale_ = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	rotation_ = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

//=============================================================================
// デストラクタ
//=============================================================================
SceneX::~SceneX()
{
	SafeRelease(materialBuffer_);
	SafeRelease(mesh_);
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT SceneX::Init()
{
	return S_OK;
}

HRESULT SceneX::Init(char *modelFileName)
{
	// モデルの取得
	// Xファイルの読み込み
	if (FAILED(D3DXLoadMeshFromX(
		modelFileName,
		D3DXMESH_SYSTEMMEM,
		Manager::GetInstance()->GetRenderer()->GetDevice(),
		nullptr,
		&materialBuffer_,
		nullptr,
		&materialNum_,
		&mesh_))) {
		return false;
	}


	return S_OK;
}

HRESULT SceneX::Init(char *modelFileName, char *textureFileName)
{
	// モデルの取得
	model_ = Manager::GetInstance()->GetModelFactory()->GetModel(modelFileName);


	// テクスチャの読み込み
	SetTexture(textureFileName);

	return S_OK;
}

//=============================================================================
// 更新処理
//=============================================================================
void SceneX::Update()
{
}

//=============================================================================
// 描画処理
//=============================================================================
void SceneX::Draw()
{
	Renderer *renderer = Manager::GetInstance()->GetRenderer();
	LPDIRECT3DDEVICE9 device = renderer->GetDevice();
	D3DXMATRIX mtxScl, mtxRot, mtxTranslate, worldMatrix;  // 大きさ, 回転, 位置の行列

	D3DXMatrixIdentity(&worldMatrix);

	D3DXMatrixScaling(&mtxScl, scale_.x, scale_.y, scale_.z);  // 地面のスケールを反映
	D3DXMatrixMultiply(&worldMatrix, &worldMatrix, &mtxScl);  // 行列のかけ合わせ

	D3DXMatrixRotationYawPitchRoll(&mtxRot, rotation_.y, rotation_.x, rotation_.z);  // 地面の回転を反映(y, x, z)
	D3DXMatrixMultiply(&worldMatrix, &worldMatrix, &mtxRot);  // 行列のかけ合わせ

	D3DXMatrixTranslation(&mtxTranslate, position_.x, position_.y, position_.z);  // 地面の位置を反映
	D3DXMatrixMultiply(&worldMatrix, &worldMatrix, &mtxTranslate);  // 行列のかけ合わせ

	D3DXMatrixMultiply(&worldMatrix_, &worldMatrix, &worldMatrix_);

	device->SetTransform(D3DTS_WORLD, &worldMatrix_);  // 行列の設定


	//device->SetRenderState(D3DRS_LIGHTING, FALSE);

	// 描画
	D3DXMATERIAL *material;
	D3DMATERIAL9 materialDefault;



	// マテリアルの取り出し
	device->GetMaterial(&materialDefault);
	material = (D3DXMATERIAL *)materialBuffer_->GetBufferPointer();


	for (int count = 0; static_cast<unsigned>(count) < materialNum_; ++count) {
		// テクスチャの設定
		device->SetTexture(0, nullptr);
		// マテリアルの設定
		device->SetMaterial(&material[count].MatD3D);
		// 描画
		mesh_->DrawSubset(count);
	}

	device->SetTexture(0, nullptr);
	device->SetMaterial(&materialDefault);


	device->SetRenderState(D3DRS_LIGHTING, TRUE);

	// ワールドマトリックスの設定
	D3DXMatrixIdentity(&worldMatrix_);  // 単位行列で初期化
}

//=============================================================================
// 生成処理
//=============================================================================
SceneX *SceneX::Create()
{
	// 生成
	SceneX *scene = new SceneX;
	// 初期化
	scene->Init();

	return scene;
}

//=========================================================================
// モデルの設定
//=========================================================================
void SceneX::SetModel(char *xFileName)
{
	// モデルの取得
	model_ = Manager::GetInstance()->GetModelFactory()->GetModel(xFileName);
}


// End of file