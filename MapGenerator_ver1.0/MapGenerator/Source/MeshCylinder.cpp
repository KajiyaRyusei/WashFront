//=============================================================================
//
// メッシュシリンダークラス [MeshCylinder.cpp]
// Author : KEITA OHUCHI
//
//=============================================================================

#include "MeshCylinder.h"
#include "Main.h"
#include "Manager.h"
#include "Renderer.h"
#include "ObjectManager.h"
#include "CameraManager.h"
#include "Camera.h"


//-----------------------------------------------------------------------------
// マクロ定義
//-----------------------------------------------------------------------------
#define UV_OFFSET (0.01f)


//=============================================================================
// コンストラクタ
//=============================================================================
MeshCylinder::MeshCylinder(int priority) : Scene3D(priority)
{
	// メンバ変数のクリア
	radius_ = 0.0f;
	indexBuffer_ = nullptr;
	indexNum_ = 0;
	vertexNum_ = 0;
	blockNumX_ = 0;
	blockNumY_ = 0;
	polygonNum_ = 0;
}

//=============================================================================
// デストラクタ
//=============================================================================
MeshCylinder::~MeshCylinder()
{

	SafeRelease(indexBuffer_);

}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT MeshCylinder::Init(D3DXVECTOR3 pos,
	int block_num_x, int block_num_y,
	float radius, float height)
{
	Renderer *renderer = Manager::GetInstance()->GetRenderer();
	LPDIRECT3DDEVICE9 device = renderer->GetDevice();

	// 引数による変数の初期化
	blockNumX_ = block_num_x;
	blockNumY_ = block_num_y;
	radius_ = radius;
	height_ = height;

	// ポリゴンの描画に必要な変数の初期化
	const int vertical_line_num = blockNumX_ + 1;  // ブロックを書くために必要な垂直線の本数
	const int horizon_line_num = blockNumY_ + 1;  // ブロックを書くために必要な水平線の本数
	const int turn_num = blockNumY_ - 1;  // 折り返し回数
	indexNum_ = vertical_line_num * block_num_y * 2 + turn_num * 2;
	vertexNum_ = vertical_line_num * horizon_line_num;
	polygonNum_ = (blockNumX_ * blockNumY_) * 2 + turn_num * 4;

	// 地面情報の初期化
	position_ = pos;
	rotation_ = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	scale_ = D3DXVECTOR3(1.0f, 1.0f, 1.0f);

	// 頂点バッファの生成
	if (FAILED(device->CreateVertexBuffer(
							sizeof(VERTEX_3D) * vertexNum_,  // 確保するメモリのサイズ
							D3DUSAGE_WRITEONLY,
							FVF_VERTEX_3D,  // 使用する頂点フォーマット
							D3DPOOL_MANAGED,
							&vertexBuffer_,  // 頂点バッファへのポインタ
							nullptr))) {
		return E_FAIL;
	}

	// インデックスバッファの生成
	if (FAILED(device->CreateIndexBuffer(
							sizeof(WORD) * indexNum_,  // 確保するメモリのサイズ
							D3DUSAGE_WRITEONLY,
							D3DFMT_INDEX16,
							D3DPOOL_MANAGED,
							&indexBuffer_,  // インデックスバッファへのポインタ
							nullptr))) {
		return E_FAIL;
	}


	// 頂点座標の設定
	VERTEX_3D *vtx;
	vertexBuffer_->Lock(0, 0, (void**)&vtx, 0);  // 頂点情報のロック

	for (int count_y = 0; count_y < horizon_line_num; ++count_y) {
		for (int count_x = 0; count_x < vertical_line_num; ++count_x) {
			vtx[count_x + count_y * vertical_line_num].vtx = 
				D3DXVECTOR3(sinf(D3DX_PI * 2 / blockNumX_ * count_x) * radius_,
							height_ - (height_ / blockNumY_) * count_y,
							cosf(D3DX_PI * 2 / blockNumX_ * count_x) * radius_);
			vtx[count_x + count_y * vertical_line_num].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
			vtx[count_x + count_y * vertical_line_num].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			vtx[count_x + count_y * vertical_line_num].tex = D3DXVECTOR2(
																(float)count_x / blockNumX_ + UV_OFFSET,
																(float)count_y / blockNumY_ + UV_OFFSET);
		}
	}
	
	vertexBuffer_->Unlock();  // 頂点情報のアンロック


	// インデックスバッファの設定
	WORD *index;
	indexBuffer_->Lock(0, 0, (void**)&index, 0);  // インデックス情報のロック

	const int vtx_id_begined = blockNumX_ + 1; // 開始頂点ID
	int even_number_count = 0;  // 偶数回用カウンタワーク
	int odd_number_count = 0;  // 奇数回用カウンタワーク
	int turn_count = 0;  // 折り返し回数カウンタワーク
	for (int count_y = 0; count_y < blockNumY_; ++count_y) {
		for (int count_x = 0; count_x < vertical_line_num*2; ++count_x) {
			if (count_x % 2 == 0) {  // 偶数回
				index[count_x + count_y * vertical_line_num * 2 + turn_count * 2] =
					vtx_id_begined + even_number_count;  // 開始位置から一つずつずらす
				++even_number_count;
			} else {  // 奇数回
				index[count_x + count_y * vertical_line_num * 2 + turn_count * 2] =
					odd_number_count;  // 左上[0]から一つずつずらす
				++odd_number_count;
			}
			// 折り返し判定
			if ((count_x + 1) == vertical_line_num*2  // 一列設定し終わり
				&& count_y < turn_num) {  // かつ、折り返し回数を超えていなければ
				index[count_x + count_y * vertical_line_num*2 + turn_count*2 + 1] =
					(odd_number_count - 1);  // 縮退ポリゴンを2つ作る
				index[count_x + count_y * vertical_line_num*2 + turn_count*2 + 2] =
					vtx_id_begined + even_number_count;  // 縮退ポリゴンをさらに2つ作る
				++turn_count;
			}
		}
	}

	indexBuffer_->Unlock();  // インデックス情報のアンロック


	// テクスチャの設定
	SetTexture("Resource/Texture/Game/Mountain003.png");


	return S_OK;
}

//=============================================================================
// 更新処理
//=============================================================================
void MeshCylinder::Update()
{
	Camera *camera = Manager::GetInstance()->GetCameraManager()->GetCamera();
	D3DXVECTOR3 pos = camera->GetPosition();
	position_.x = pos.x;
	position_.z = pos.z;
}

//=============================================================================
// 描画処理
//=============================================================================
void MeshCylinder::Draw()
{
	Renderer *renderer = Manager::GetInstance()->GetRenderer();
	LPDIRECT3DDEVICE9 device = renderer->GetDevice();
	D3DXMATRIX mtxScl, mtxRot, mtxTranslate;  // 大きさ, 回転, 位置の行列

	// ワールドマトリックスの設定
	D3DXMatrixIdentity(&worldMatrix_);  // 単位行列で初期化

	// 地面のスケールを反映
	D3DXMatrixScaling(&mtxScl, scale_.x, scale_.y, scale_.z);
	D3DXMatrixMultiply(&worldMatrix_, &worldMatrix_, &mtxScl);  // 行列のかけ合わせ
	// 地面の回転を反映(y, x, z)
	D3DXMatrixRotationYawPitchRoll(&mtxRot, rotation_.y, rotation_.x, rotation_.z);
	D3DXMatrixMultiply(&worldMatrix_, &worldMatrix_, &mtxRot);  // 行列のかけ合わせ
	// 地面の位置を反映
	D3DXMatrixTranslation(&mtxTranslate, position_.x, position_.y, position_.z);
	D3DXMatrixMultiply(&worldMatrix_, &worldMatrix_, &mtxTranslate);  // 行列のかけ合わせ
	
	device->SetTransform(D3DTS_WORLD, &worldMatrix_);  // 行列の設定


	// ライトを無効にする
	device->SetRenderState(D3DRS_LIGHTING, FALSE);
	// Zバッファを使用しない
	device->SetRenderState(D3DRS_ZENABLE, FALSE);
	// フォグを使用しない
    device->SetRenderState(D3DRS_FOGENABLE, FALSE);



	// 3Dポリゴンの描画
	device->SetStreamSource(0, vertexBuffer_, 0, sizeof(VERTEX_3D));  // 頂点バッファをデータストリームにバインド
	device->SetIndices(indexBuffer_);  // インデックスバッファをバインド
	device->SetFVF(FVF_VERTEX_3D);  // 頂点フォーマットの設定
	device->SetTexture(0, texture_);  // テクスチャの設定
	device->DrawIndexedPrimitive(
		D3DPT_TRIANGLESTRIP,
		0, 0, vertexNum_, 0, polygonNum_);


	// ライトを有効にする
	device->SetRenderState(D3DRS_LIGHTING, TRUE);
	// Zバッファを使用する
	device->SetRenderState(D3DRS_ZENABLE, TRUE);
	// フォグを使用する
    device->SetRenderState(D3DRS_FOGENABLE, TRUE);

}

//=========================================================================
// 生成処理
//========================================================================
MeshCylinder *MeshCylinder::Create(D3DXVECTOR3 pos,
							 int block_num_x, int block_num_y,
							 float radius, float height)
{
	// 生成
	MeshCylinder *cylinder = new MeshCylinder();
	// 初期化
	cylinder->Init(pos, block_num_x, block_num_y, radius, height);


	return cylinder;
}


// End Of File