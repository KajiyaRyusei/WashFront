//=============================================================================
//
// モデルクラス [Model.h]
// Author : KEITA OHUCHI
//
//=============================================================================

#include "Model.h"
#include "Manager.h"
#include "Renderer.h"
#include "TextureFactory.h"


//=========================================================================
// コンストラクタ
//=========================================================================
Model::Model()
{

	texture_ = nullptr;
	materialBuffer_ = nullptr;
	materialNum_ = 0;
	mesh_ = nullptr;
	filePath_ = nullptr;

}

//=========================================================================
// デストラクタ
//=========================================================================
Model::~Model()
{

	// マテリアルバッファの開放処理
	SafeRelease(materialBuffer_);
	// メッシュの開放処理
	SafeRelease(mesh_);
	// テクスチャの開放処理
	SafeDelete(texture_);

}


//=========================================================================
// 初期化処理
//=========================================================================
bool Model::Init(LPCSTR xFileName)
{

	filePath_ = xFileName;


	// Xファイルの読み込み
	if (FAILED(D3DXLoadMeshFromX(
			xFileName,
			D3DXMESH_SYSTEMMEM,
			Manager::GetInstance()->GetRenderer()->GetDevice(),
			nullptr,
			&materialBuffer_,
			nullptr,
			&materialNum_,
			&mesh_))) {
		return false;
	}


	// テクスチャ関連
	texture_ = new LPDIRECT3DTEXTURE9[materialNum_];
	D3DXMATERIAL *pD3DXMat = nullptr;
	pD3DXMat = (D3DXMATERIAL*)materialBuffer_->GetBufferPointer();

	for (int count = 0; count < (int)materialNum_; ++count) {
		// テクスチャポインタの初期化
		texture_[count] = nullptr;
		// 使用しているテクスチャがあれば読み込む
		if (pD3DXMat[count].pTextureFilename != nullptr && lstrlen(pD3DXMat[count].pTextureFilename) > 0) {
			// テクスチャの取得
			// texture_[count] = Manager::GetInstance()->GetTextureFactory()->GetTexture(pD3DXMat[count].pTextureFilename);
		}
	}


	return true;

}

//=========================================================================
// 描画処理
//=========================================================================
void Model::Draw()
{

	LPDIRECT3DDEVICE9 device = Manager::GetInstance()->GetRenderer()->GetDevice();
	D3DXMATERIAL *material;
	D3DMATERIAL9 materialDefault;

	// マテリアルの取り出し
	device->GetMaterial(&materialDefault);
	material = (D3DXMATERIAL *)materialBuffer_->GetBufferPointer();


	for (int count = 0; static_cast<unsigned>(count) < materialNum_; ++count) {
		// マテリアルの設定
		device->SetMaterial(&material[count].MatD3D);
		// テクスチャの設定
		device->SetTexture(0, texture_[count]);
		// 描画
		mesh_->DrawSubset(count);
	}

	device->SetTexture(0, nullptr);
	device->SetMaterial(&materialDefault);

}

//=========================================================================
// 生成処理
//=========================================================================
Model* Model::Create(LPCSTR xFileName)
{

	Model *model = nullptr;
	model = new Model();
	model->Init(xFileName);


	return model;

}


// End of file