//=============================================================================
//
// ビル [Building.cpp]
// Author : KEITA OHUCHI
//
//=============================================================================

#include "Main.h"
#include "Manager.h"
#include "Renderer.h"
#include "Building.h"
#include "model.h"
#include "ModelFactory.h"
#include "TextureFactory.h"


//=========================================================================
// コンストラクタとデストラクタ
//=========================================================================
Building::Building(int priority) : Scene(priority),
model_(nullptr),
rotation_(D3DXVECTOR3(0, 0, 0)),
scale_(D3DXVECTOR3(1, 1, 1)),
id_(-1),
modelFilePath_(nullptr),
textureFilePath_(nullptr),
selectTexture_(nullptr),
hitTexture_(nullptr),
state_(0)
{
	D3DXMatrixIdentity(&worldMatrix_);
}

Building::~Building()
{
	model_ = nullptr;
}

//=========================================================================
// 初期化処理
//=========================================================================
HRESULT Building::Init()
{
	return S_OK;
}

HRESULT Building::Init(const char *modelFilePath, const char *textureFilePath)
{
	if (modelFilePath)
		model_ = Manager::GetInstance()->GetModelFactory()->GetModel(modelFilePath);
	if (textureFilePath)
		texture_ = Manager::GetInstance()->GetTextureFactory()->GetTexture(textureFilePath);
	selectTexture_ = Manager::GetInstance()->GetTextureFactory()->GetTexture(
		"./Resource/Texture/Game/Select.png");
	hitTexture_ = Manager::GetInstance()->GetTextureFactory()->GetTexture(
		"./Resource/Texture/Game/Hit.png");
	modelFilePath_ = (char *)modelFilePath;
	textureFilePath_ = (char *)textureFilePath;


	return S_OK;
}

HRESULT Building::Init(const char *modelFilePath, const char *textureFilePath, D3DXVECTOR3 position, D3DXVECTOR3 rotation, D3DXVECTOR3 scale)
{
	if (modelFilePath)
		model_ = Manager::GetInstance()->GetModelFactory()->GetModel(modelFilePath);
	if (textureFilePath)
		texture_ = Manager::GetInstance()->GetTextureFactory()->GetTexture(textureFilePath);
	selectTexture_ = Manager::GetInstance()->GetTextureFactory()->GetTexture(
		"./Resource/Texture/Game/Select.png");
	hitTexture_ = Manager::GetInstance()->GetTextureFactory()->GetTexture(
		"./Resource/Texture/Game/Hit.png");
	modelFilePath_ = (char *)modelFilePath;
	textureFilePath_ = (char *)textureFilePath;
	position_ = position;
	rotation_ = rotation;
	scale_ = scale;

	return S_OK;
}

//=========================================================================
// 更新処理
//=========================================================================
void Building::Update()
{
}

//=========================================================================
// 描画処理
//=========================================================================
void Building::Draw()
{

	Renderer *renderer = Manager::GetInstance()->GetRenderer();
	LPDIRECT3DDEVICE9 device = renderer->GetDevice();
	D3DXMATRIX mtxScl, mtxRot, mtxTranslate;  // 大きさ, 回転, 位置の行列

	// ワールドマトリックスの設定
	D3DXMatrixIdentity(&worldMatrix_);  // 単位行列で初期化

	D3DXMatrixScaling(&mtxScl, scale_.x, scale_.y, scale_.z);
	D3DXMatrixMultiply(&worldMatrix_, &worldMatrix_, &mtxScl);  // 行列のかけ合わせ

	// 地面の回転を反映(y, x, z)
	D3DXMatrixRotationYawPitchRoll(&mtxRot, rotation_.y, rotation_.x, rotation_.z);
	D3DXMatrixMultiply(&worldMatrix_, &worldMatrix_, &mtxRot);  // 行列のかけ合わせ

	// 地面の位置を反映
	D3DXMatrixTranslation(&mtxTranslate, position_.x, position_.y, position_.z);
	D3DXMatrixMultiply(&worldMatrix_, &worldMatrix_, &mtxTranslate);  // 行列のかけ合わせ

	device->SetTransform(D3DTS_WORLD, &worldMatrix_);  // 行列の設定

	switch (state_) {
	case SELECT_NONE:
		device->SetTexture(0, texture_);
		break;
	case SELECT_HIT:
		device->SetTexture(0, hitTexture_);
		break;
	case SELECT_SELECT:
		device->SetTexture(0, selectTexture_);
		break;
	default:
		break;
	}
	model_->Draw(worldMatrix_);
	device->SetTexture(0, nullptr);
}


// End of file