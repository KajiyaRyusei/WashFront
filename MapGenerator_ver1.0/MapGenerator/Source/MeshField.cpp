//=============================================================================
//
// メッシュフィールド [MeshField.cpp]
// Author : KEITA OHUCHI
//
//=============================================================================

#include "Main.h"
#include "Manager.h"
#include "Renderer.h"
#include "MeshField.h"
#include <stdio.h>


//-----------------------------------------------------------------------------
// マクロ定義
//-----------------------------------------------------------------------------
// 隅の座標
#define EDGE_POS_X (-blockSizeX_ * blockNumX_ / 2.0f)
#define EDGE_POS_Z (blockSizeZ_ * blockNumZ_ / 2.0f)

// 色
#define TOP_DIFFUSE_COLOR (D3DXCOLOR(0.40f, 0.62f, 0.23f, 1.0f))
#define BOTTOM_DIFFUSE_COLOR (D3DXCOLOR(0.41f, 0.36f, 0.31f, 1.0f))
// 色の設定用の高さ
#define TOP_HEIGHT		(13.0f)
#define BOTTOM_HEIGHT	(0.0f)


//=============================================================================
// コンストラクタ
//=============================================================================
MeshField::MeshField(int priority) : Scene3D(priority)
{
	// メンバ変数の初期化
	indexBuffer_ = nullptr;
	indexNum_ = 0;
	vertexNum_ = 0;
	polygonNum_ = 0;
	blockNumX_ = 0;
	blockNumZ_ = 0;
	blockSizeX_ = 0.0f;
	blockSizeZ_ = 0.0f;
	faceNormal_ = nullptr;
}

//=============================================================================
// デストラクタ
//=============================================================================
MeshField::~MeshField()
{

	// ポインタ変数の解放
	SafeRelease(indexBuffer_);
	SafeDelete(faceNormal_);

}


//=============================================================================
// 初期化処理
//=============================================================================
HRESULT MeshField::Init(int block_num_x, int block_num_z,
	float block_size_x, float block_size_z,
	D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	Renderer *renderer = Manager::GetInstance()->GetRenderer();
	LPDIRECT3DDEVICE9 device = renderer->GetDevice();

	// 引数による変数の初期化
	blockNumX_ = block_num_x;
	blockNumZ_ = block_num_z;
	blockSizeX_ = block_size_x;
	blockSizeZ_ = block_size_z;
	position_ = pos;
	rotation_ = rot;

	// ポリゴンの描画に必要な変数の初期化
	const int vertical_line_num = blockNumX_ + 1;  // ブロックを書くために必要な垂直線の本数
	const int horizon_line_num = blockNumZ_ + 1;  // ブロックを書くために必要な水平線の本数
	const int turn_num = blockNumZ_ - 1;  // 折り返し回数
	indexNum_ = vertical_line_num * blockNumZ_ * 2 + turn_num * 2;
	vertexNum_ = vertical_line_num * horizon_line_num;
	polygonNum_ = (blockNumX_ * blockNumZ_) * 2 + turn_num * 4;

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


	// 高さマップの生成
	/*
	float *height_map = new float[vertexNum_];
	memset(height_map, nullptr, sizeof(float *) * vertexNum_);
	CreateHeightMap(height_map);
	*/

	// 頂点座標の設定
	VERTEX_3D *pVtx;
	vertexBuffer_->Lock(0, 0, (void**)&pVtx, 0);  // 頂点情報のロック
	
	// 頂点情報の保存
	float height = rand() % 100 * 0.01f + 0.5f;
	float offset = rand() % 314 * 0.01f;
	for (int count_z = 0; count_z < horizon_line_num; ++count_z) {
		for (int count_x = 0; count_x < vertical_line_num; ++count_x) {
			float x, z;
			x = pVtx[count_x + count_z * vertical_line_num].vtx.x = EDGE_POS_X + blockSizeX_ * count_x;
			z = pVtx[count_x + count_z * vertical_line_num].vtx.z = EDGE_POS_Z - blockSizeZ_ * count_z;
			x -= EDGE_POS_X;
			z -= EDGE_POS_Z;
			float length = sqrtf(x * x + z * z);
			pVtx[count_x + count_z * vertical_line_num].vtx.y = 0.0f;
			//pVtx[count_x + count_z * vertical_line_num].vtx.y = sinf(length * 0.3f + offset) * height;
			pVtx[count_x + count_z * vertical_line_num].diffuse = TOP_DIFFUSE_COLOR;
			pVtx[count_x + count_z * vertical_line_num].tex = D3DXVECTOR2((float)count_x, (float)count_z);
		}
		if ((count_z / 40) % 2) {
			height += rand() % 10 * 0.01f + 0.05f;
		} else {
			height -= rand() % 10 * 0.01f + 0.05f;
		}
	}

	// 高さマップの解放
	//delete[] height_map;

	// 面の法線情報格納ワークを確保
	faceNormal_ = new D3DXVECTOR3[blockNumX_ * 2 * blockNumZ_];

	// 面の法線情報の保存
	for (int count_z = 0; count_z < blockNumZ_; ++count_z) {
		for (int count_x = 0; count_x < blockNumX_; ++count_x) {
			D3DXVECTOR3 vec0, vec1, vecN, nor;
			// 面を構成するベクトルの計算
			vec0 = pVtx[count_x + count_z * vertical_line_num].vtx
					- pVtx[count_x + (count_z + 1) * vertical_line_num].vtx;
			vec1 = pVtx[count_x + (count_z + 1) * vertical_line_num + 1].vtx
					- pVtx[count_x + (count_z + 1) * vertical_line_num].vtx;
			// 外積で法線の向きを計算
			D3DXVec3Cross(&vecN, &vec0, &vec1);
			// 法線の向きのベクトルを正規化
			D3DXVec3Normalize(&nor, &vecN);
			// 法線情報を保存
			faceNormal_[count_z * blockNumX_ * 2 + count_x * 2] = nor;

			// 面を構成するベクトルの計算
			vec0 = pVtx[count_x + (count_z + 1) * vertical_line_num + 1].vtx
					- pVtx[count_x + count_z * vertical_line_num + 1].vtx;
			vec1 = pVtx[count_x + count_z * vertical_line_num].vtx
					- pVtx[count_x + count_z * vertical_line_num + 1].vtx;
			// 外積で法線の向きを計算
			D3DXVec3Cross(&vecN, &vec0, &vec1);
			// 法線の向きのベクトルを正規化
			D3DXVec3Normalize(&nor, &vecN);
			// 法線情報を保存
			faceNormal_[count_z * blockNumX_ * 2 + count_x * 2 + 1] = nor;
		}
	}

	// 頂点の法線情報の保存
	for (int count_z = 0; count_z < horizon_line_num; ++count_z) {
		for (int count_x = 0; count_x < vertical_line_num; ++count_x) {
			D3DXVECTOR3 nor;
			// 左上
			if (count_x == 0 && count_z == 0) {
				nor = (faceNormal_[0] + faceNormal_[1]) * 0.5f;
				D3DXVec3Normalize(&nor, &nor);
				pVtx[count_x + count_z * vertical_line_num].nor = nor;
			// 左下
			} else if (count_x == 0 && count_z == horizon_line_num - 1) {
				pVtx[count_x + count_z * vertical_line_num].nor =
					faceNormal_[(blockNumZ_ - 1) * (blockNumX_ * 2)];
			// 右上
			} else if (count_x == vertical_line_num - 1 && count_z == 0) {
				pVtx[count_x + count_z * vertical_line_num].nor =
					faceNormal_[blockNumX_ * 2 - 1];
			// 右下
			} else if (count_x == vertical_line_num - 1 && count_z == horizon_line_num - 1) {
				nor = (faceNormal_[(blockNumZ_ - 1) * (blockNumX_ * 2) + blockNumX_ * 2 - 2]
						+ faceNormal_[(blockNumZ_ - 1) * (blockNumX_ * 2) + blockNumX_ * 2 - 1]) * 0.5f;
				D3DXVec3Normalize(&nor, &nor);
				pVtx[count_x + count_z * vertical_line_num].nor = nor;
			// 上端
			} else if (0 < count_x && count_x < vertical_line_num - 1
				&& count_z == 0) {
				
				nor = faceNormal_[count_x * 2 - 1] + (faceNormal_[count_x * 2] + faceNormal_[count_x * 2 + 1]) * 0.5f;
				D3DXVec3Normalize(&nor, &nor);
				pVtx[count_x + count_z * vertical_line_num].nor = nor;
			// 下端
			} else if (0 < count_x && count_x < vertical_line_num - 1
				&& count_z == horizon_line_num - 1) {
				
				nor = (faceNormal_[(blockNumZ_ - 1) * (blockNumX_ * 2) + count_x * 2 - 1]
						+ faceNormal_[(blockNumZ_ - 1) * (blockNumX_ * 2) + count_x * 2]) * 0.5f
							+ faceNormal_[(blockNumZ_ - 1) * (blockNumX_ * 2) + count_x * 2 + 1];
				D3DXVec3Normalize(&nor, &nor);
				pVtx[count_x + count_z * vertical_line_num].nor = nor;
			// 左端
			} else if (count_x == 0
				&& 0 < count_z && count_z < horizon_line_num - 1) {
				
				nor = faceNormal_[(count_z - 1) * (blockNumX_ * 2)]
						+ (faceNormal_[count_z * (blockNumX_ * 2)]
							+ faceNormal_[count_z * (blockNumX_ * 2) + 1]) * 0.5f;
				D3DXVec3Normalize(&nor, &nor);
				pVtx[count_x + count_z * vertical_line_num].nor = nor;
			// 右端
			} else if (count_x == vertical_line_num - 1
				&& 0 < count_z && count_z < horizon_line_num - 1) {
				
				nor = (faceNormal_[(count_z - 1) * (blockNumX_ * 2) + blockNumX_ * 2 - 2]
						+ faceNormal_[(count_z - 1) * (blockNumX_ * 2) + blockNumX_ * 2 - 1]) * 0.5f
							+ faceNormal_[count_z * (blockNumX_ * 2) + blockNumX_ * 2 - 1];
				D3DXVec3Normalize(&nor, &nor);
				pVtx[count_x + count_z * vertical_line_num].nor = nor;
			// 内側の法線
			} else {
				nor = (faceNormal_[(count_z - 1) * (blockNumX_ * 2) + count_x * 2 - 2]
						+ faceNormal_[(count_z - 1) * (blockNumX_ * 2) + count_x * 2 - 1]) * 0.5f
							+ faceNormal_[(count_z - 1) * (blockNumX_ * 2) + count_x * 2]
								+ faceNormal_[count_z * (blockNumX_ * 2) + count_x * 2 - 1]
									+ (faceNormal_[count_z * (blockNumX_ * 2) + count_x * 2]
										+ faceNormal_[count_z * (blockNumX_ * 2) + count_x * 2 + 1]) * 0.5f;
				D3DXVec3Normalize(&nor, &nor);
				pVtx[count_x + count_z * vertical_line_num].nor = nor;
			}
		}
	}
	
	vertexBuffer_->Unlock();  // 頂点情報のアンロック


	// インデックスバッファの設定
	WORD *pIndex;
	indexBuffer_->Lock(0, 0, (void**)&pIndex, 0);  // インデックス情報のロック

	const int vtx_id_begined = blockNumX_ + 1; // 開始頂点ID
	int even_nucounter_ = 0;  // 偶数回用カウンタワーク
	int odd_nucounter_ = 0;  // 奇数回用カウンタワーク
	int turn_count = 0;  // 折り返し回数カウンタワーク

	for (int count_z = 0; count_z < blockNumZ_; ++count_z) {
		for (int count_x = 0; count_x < vertical_line_num*2; ++count_x) {
			if (count_x % 2 == 0) {  // 偶数回
				pIndex[count_x + count_z * vertical_line_num * 2 + turn_count * 2] =
					vtx_id_begined + even_nucounter_;  // 開始位置から一つずつずらす
				++even_nucounter_;
			} else {  // 奇数回
				pIndex[count_x + count_z * vertical_line_num * 2 + turn_count * 2] =
					odd_nucounter_;  // 左上[0]から一つずつずらす
				++odd_nucounter_;
			}

			// 折り返し判定
			if ((count_x + 1) == vertical_line_num * 2  // 一列設定し終わり
				&& count_z < turn_num) {  // かつ、折り返し回数を超えていなければ
				pIndex[count_x + count_z * vertical_line_num * 2 + turn_count*2 + 1] =
					(odd_nucounter_ - 1);  // 縮退ポリゴンを2つ作る
				pIndex[count_x + count_z * vertical_line_num * 2 + turn_count*2 + 2] =
					vtx_id_begined + even_nucounter_;  // 縮退ポリゴンをさらに2つ作る
				++turn_count;
			}
		}
	}

	indexBuffer_->Unlock();  // インデックス情報のアンロック

	// テクスチャの読み込み
	//SetTexture("Resource/Texture/Game/Field.jpg");


	return S_OK;
}


HRESULT MeshField::Init(char *fileName, D3DXVECTOR3 position, D3DXVECTOR3 rotation)
{
	Renderer *renderer = Manager::GetInstance()->GetRenderer();
	LPDIRECT3DDEVICE9 device = renderer->GetDevice();

	int block_num_x, block_num_z;
	float block_size_x, block_size_z;
	float *height_map;

	FILE *file = fopen(fileName, "rb");
	fread(&block_num_x, sizeof(int), 1, file);
	fread(&block_num_z, sizeof(int), 1, file);
	fread(&block_size_x, sizeof(float), 1, file);
	fread(&block_size_z, sizeof(float), 1, file);

	// 引数による変数の初期化
	blockNumX_ = block_num_x;
	blockNumZ_ = block_num_z;
	blockSizeX_ = block_size_x;
	blockSizeZ_ = block_size_z;
	position_ = position;
	rotation_ = rotation;

	// ポリゴンの描画に必要な変数の初期化
	const int vertical_line_num = blockNumX_ + 1;  // ブロックを書くために必要な垂直線の本数
	const int horizon_line_num = blockNumZ_ + 1;  // ブロックを書くために必要な水平線の本数
	const int turn_num = blockNumZ_ - 1;  // 折り返し回数
	indexNum_ = vertical_line_num * blockNumZ_ * 2 + turn_num * 2;
	vertexNum_ = vertical_line_num * horizon_line_num;
	polygonNum_ = (blockNumX_ * blockNumZ_) * 2 + turn_num * 4;

	height_map = new float[vertexNum_];
	fread(height_map, sizeof(float), vertexNum_, file);

	fclose(file);

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


	D3DXCOLOR topColor = TOP_DIFFUSE_COLOR;
	D3DXCOLOR bottomColor = BOTTOM_DIFFUSE_COLOR;
	float y = 0;


	// 頂点座標の設定
	VERTEX_3D *pVtx;
	vertexBuffer_->Lock(0, 0, (void**)&pVtx, 0);  // 頂点情報のロック
	
	// 頂点情報の保存
	float height = rand() % 100 * 0.01f + 0.5f;
	float offset = rand() % 314 * 0.01f;
	for (int count_z = 0; count_z < horizon_line_num; ++count_z) {
		for (int count_x = 0; count_x < vertical_line_num; ++count_x) {
			pVtx[count_x + count_z * vertical_line_num].vtx.x = EDGE_POS_X + blockSizeX_ * count_x;
			pVtx[count_x + count_z * vertical_line_num].vtx.z = EDGE_POS_Z - blockSizeZ_ * count_z;
			y = pVtx[count_x + count_z * vertical_line_num].vtx.y = height_map[count_x + count_z * vertical_line_num];
			if (y < 0) {
				y = 0;
			} else if (TOP_HEIGHT < y) {
				y = TOP_HEIGHT;
			}
			D3DXCOLOR color = topColor * (y / TOP_HEIGHT) + bottomColor * (1.0f - y / TOP_HEIGHT);
			pVtx[count_x + count_z * vertical_line_num].diffuse = color;
			//pVtx[count_x + count_z * vertical_line_num].diffuse = TOP_DIFFUSE_COLOR;
			pVtx[count_x + count_z * vertical_line_num].tex = D3DXVECTOR2((float)count_x / 5.0f, (float)count_z / 5.0f);
		}
		if ((count_z / 40) % 2) {
			height += rand() % 10 * 0.01f + 0.05f;
		} else {
			height -= rand() % 10 * 0.01f + 0.05f;
		}
	}

	delete[] height_map;


	// 面の法線情報格納ワークを確保
	faceNormal_ = new D3DXVECTOR3[blockNumX_ * 2 * blockNumZ_];

	// 面の法線情報の保存
	for (int count_z = 0; count_z < blockNumZ_; ++count_z) {
		for (int count_x = 0; count_x < blockNumX_; ++count_x) {
			D3DXVECTOR3 vec0, vec1, vecN, nor;
			// 面を構成するベクトルの計算
			vec0 = pVtx[count_x + count_z * vertical_line_num].vtx
					- pVtx[count_x + (count_z + 1) * vertical_line_num].vtx;
			vec1 = pVtx[count_x + (count_z + 1) * vertical_line_num + 1].vtx
					- pVtx[count_x + (count_z + 1) * vertical_line_num].vtx;
			// 外積で法線の向きを計算
			D3DXVec3Cross(&vecN, &vec0, &vec1);
			// 法線の向きのベクトルを正規化
			D3DXVec3Normalize(&nor, &vecN);
			// 法線情報を保存
			faceNormal_[count_z * blockNumX_ * 2 + count_x * 2] = nor;

			// 面を構成するベクトルの計算
			vec0 = pVtx[count_x + (count_z + 1) * vertical_line_num + 1].vtx
					- pVtx[count_x + count_z * vertical_line_num + 1].vtx;
			vec1 = pVtx[count_x + count_z * vertical_line_num].vtx
					- pVtx[count_x + count_z * vertical_line_num + 1].vtx;
			// 外積で法線の向きを計算
			D3DXVec3Cross(&vecN, &vec0, &vec1);
			// 法線の向きのベクトルを正規化
			D3DXVec3Normalize(&nor, &vecN);
			// 法線情報を保存
			faceNormal_[count_z * blockNumX_ * 2 + count_x * 2 + 1] = nor;
		}
	}
	

	// 頂点の法線情報の保存
	for (int count_z = 0; count_z < horizon_line_num; ++count_z) {
		for (int count_x = 0; count_x < vertical_line_num; ++count_x) {
			D3DXVECTOR3 nor;
			// 左上
			if (count_x == 0 && count_z == 0) {
				nor = (faceNormal_[0] + faceNormal_[1]) * 0.5f;
				D3DXVec3Normalize(&nor, &nor);
				pVtx[count_x + count_z * vertical_line_num].nor = nor;
			// 左下
			} else if (count_x == 0 && count_z == horizon_line_num - 1) {
				pVtx[count_x + count_z * vertical_line_num].nor =
					faceNormal_[(blockNumZ_ - 1) * (blockNumX_ * 2)];
			// 右上
			} else if (count_x == vertical_line_num - 1 && count_z == 0) {
				pVtx[count_x + count_z * vertical_line_num].nor =
					faceNormal_[blockNumX_ * 2 - 1];
			// 右下
			} else if (count_x == vertical_line_num - 1 && count_z == horizon_line_num - 1) {
				nor = (faceNormal_[(blockNumZ_ - 1) * (blockNumX_ * 2) + blockNumX_ * 2 - 2]
						+ faceNormal_[(blockNumZ_ - 1) * (blockNumX_ * 2) + blockNumX_ * 2 - 1]) * 0.5f;
				D3DXVec3Normalize(&nor, &nor);
				pVtx[count_x + count_z * vertical_line_num].nor = nor;
			// 上端
			} else if (0 < count_x && count_x < vertical_line_num - 1
				&& count_z == 0) {
				
				nor = faceNormal_[count_x * 2 - 1] + (faceNormal_[count_x * 2] + faceNormal_[count_x * 2 + 1]) * 0.5f;
				D3DXVec3Normalize(&nor, &nor);
				pVtx[count_x + count_z * vertical_line_num].nor = nor;
			// 下端
			} else if (0 < count_x && count_x < vertical_line_num - 1
				&& count_z == horizon_line_num - 1) {

				nor = (faceNormal_[(blockNumZ_ - 1) * (blockNumX_ * 2) + count_x * 2 - 1]
						+ faceNormal_[(blockNumZ_ - 1) * (blockNumX_ * 2) + count_x * 2]) * 0.5f
							+ faceNormal_[(blockNumZ_ - 1) * (blockNumX_ * 2) + count_x * 2 + 1];
				D3DXVec3Normalize(&nor, &nor);
				pVtx[count_x + count_z * vertical_line_num].nor = nor;
			// 左端
			} else if (count_x == 0 && 0 < count_z && count_z < horizon_line_num - 1) {
				nor = faceNormal_[(count_z - 1) * (blockNumX_ * 2)]
						+ (faceNormal_[count_z * (blockNumX_ * 2)]
							+ faceNormal_[count_z * (blockNumX_ * 2) + 1]) * 0.5f;
				D3DXVec3Normalize(&nor, &nor);
				pVtx[count_x + count_z * vertical_line_num].nor = nor;
			// 右端
			} else if (count_x == vertical_line_num - 1
				&& 0 < count_z && count_z < horizon_line_num - 1) {

				nor = (faceNormal_[(count_z - 1) * (blockNumX_ * 2) + blockNumX_ * 2 - 2]
						+ faceNormal_[(count_z - 1) * (blockNumX_ * 2) + blockNumX_ * 2 - 1]) * 0.5f
							+ faceNormal_[count_z * (blockNumX_ * 2) + blockNumX_ * 2 - 1];
				D3DXVec3Normalize(&nor, &nor);
				pVtx[count_x + count_z * vertical_line_num].nor = nor;
			// 内側の法線
			} else {
				nor = (faceNormal_[(count_z - 1) * (blockNumX_ * 2) + count_x * 2 - 2]
						+ faceNormal_[(count_z - 1) * (blockNumX_ * 2) + count_x * 2 - 1]) * 0.5f
							+ faceNormal_[(count_z - 1) * (blockNumX_ * 2) + count_x * 2]
								+ faceNormal_[count_z * (blockNumX_ * 2) + count_x * 2 - 1]
									+ (faceNormal_[count_z * (blockNumX_ * 2) + count_x * 2]
										+ faceNormal_[count_z * (blockNumX_ * 2) + count_x * 2 + 1]) * 0.5f;
				D3DXVec3Normalize(&nor, &nor);
				pVtx[count_x + count_z * vertical_line_num].nor = nor;
			}
		}
	}
	
	vertexBuffer_->Unlock();  // 頂点情報のアンロック



	// インデックスバッファの設定
	WORD *pIndex;

	indexBuffer_->Lock(0, 0, (void**)&pIndex, 0);  // インデックス情報のロック

	const int vtx_id_begined = blockNumX_ + 1; // 開始頂点ID
	int even_nucounter_ = 0;  // 偶数回用カウンタワーク
	int odd_nucounter_ = 0;  // 奇数回用カウンタワーク
	int turn_count = 0;  // 折り返し回数カウンタワーク

	for (int count_z = 0; count_z < blockNumZ_; ++count_z) {
		for (int count_x = 0; count_x < vertical_line_num*2; ++count_x) {
			if (count_x % 2 == 0) {  // 偶数回
				pIndex[count_x + count_z * vertical_line_num * 2 + turn_count * 2] =
					vtx_id_begined + even_nucounter_;  // 開始位置から一つずつずらす
				++even_nucounter_;
			} else {  // 奇数回
				pIndex[count_x + count_z * vertical_line_num * 2 + turn_count * 2] =
					odd_nucounter_;  // 左上[0]から一つずつずらす
				++odd_nucounter_;
			}

			// 折り返し判定
			if ((count_x + 1) == vertical_line_num * 2  // 一列設定し終わり
				&& count_z < turn_num) {  // かつ、折り返し回数を超えていなければ
				pIndex[count_x + count_z * vertical_line_num * 2 + turn_count*2 + 1] =
					(odd_nucounter_ - 1);  // 縮退ポリゴンを2つ作る
				pIndex[count_x + count_z * vertical_line_num * 2 + turn_count*2 + 2] =
					vtx_id_begined + even_nucounter_;  // 縮退ポリゴンをさらに2つ作る
				++turn_count;
			}
		}
	}

	indexBuffer_->Unlock();  // インデックス情報のアンロック


	return S_OK;
}

//=============================================================================
// 更新処理
//=============================================================================
void MeshField::Update()
{
}

//=============================================================================
// 描画初理
//=============================================================================
void MeshField::Draw()
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

	// 3Dポリゴンの描画
	device->SetStreamSource(0, vertexBuffer_, 0, sizeof(VERTEX_3D));  // 頂点バッファをデータストリームにバインド
	device->SetIndices(indexBuffer_);  // インデックスバッファをバインド
	device->SetFVF(FVF_VERTEX_3D);  // 頂点フォーマットの設定
	device->SetTexture(0, texture_);  // テクスチャの設定
	device->DrawIndexedPrimitive(
		D3DPT_TRIANGLESTRIP,
		0, 0, vertexNum_, 0, polygonNum_);
}

//=========================================================================
// 生成処理
//=========================================================================
MeshField *MeshField::Create(int block_num_x, int block_num_z,
	float block_size_x, float block_size_z,
	D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	// 生成
	MeshField * field = new MeshField();
	// 初期化
	field->Init(block_num_x, block_num_z,
				block_size_x, block_size_z,
				pos, rot);


	return field;
}

MeshField *MeshField::Create(char *fileName, D3DXVECTOR3 position, D3DXVECTOR3 rotation)
{
	// 生成
	MeshField *field = new MeshField();
	// 初期化
	field->Init(fileName, position, rotation);


	return field;
}


//=========================================================================
// 高さマップ生成処理
//=========================================================================
void MeshField::CreateHeightMap(float *map)
{
}

//=========================================================================
// プレイヤーのy座標を求める処理
//=========================================================================
float MeshField::GetHeight(D3DXVECTOR3 pos)
{
	D3DXVECTOR3 pos0, pos1, pos2, pos3;
	D3DXVECTOR3 vec0, vec1, vec2;
	D3DXVECTOR3 vec_p0, vec_p1, vec_p2;
	float height = 0;
	VERTEX_3D *vtx;
	
	//D3DXMATRIX mtx;
	//D3DXMatrixIdentity(&mtx);
	//D3DXMatrixRotationYawPitchRoll(&mtx, rotation_.y, rotation_.x, rotation_.z);

	int	x,	z;
	// グリッドの指標を抽出
	x = (int)((pos.x - EDGE_POS_X) / blockSizeX_);
	z = (int)((pos.z - EDGE_POS_Z) / blockSizeZ_);
	if (x < 0) {
		x = -x;
	}
	if (z < 0) {
		z = -z;
	}
	
	// 頂点情報のロック
	vertexBuffer_->Lock(0, 0, (void**)&vtx, 0);
			
	pos0 = vtx[x + (z + 1) * (blockNumX_ + 1)].vtx;
	pos1 = vtx[x + z * (blockNumX_ + 1)].vtx;
	pos2 = vtx[x + (z + 1) * (blockNumX_ + 1) + 1].vtx;
	pos3 = vtx[x + z * (blockNumX_ + 1) + 1].vtx;

	//D3DXVec3TransformCoord(&pos0, &pos0, &mtx);
	//D3DXVec3TransformCoord(&pos1, &pos1, &mtx);
	//D3DXVec3TransformCoord(&pos2, &pos2, &mtx);
	//D3DXVec3TransformCoord(&pos3, &pos3, &mtx);

	// 一枚目のポリゴン
	vec0 = pos1 - pos0;
	vec1 = pos2 - pos1;
	vec2 = pos0 - pos2;
	vec_p0 = pos - pos0;
	vec_p1 = pos - pos1;
	vec_p2 = pos - pos2;

	// 外積による内外判定
	if ((vec0.x * vec_p0.z - vec0.z * vec_p0.x) <= 0
		&& (vec1.x * vec_p1.z - vec1.z * vec_p1.x) <= 0
		&& (vec2.x * vec_p2.z - vec2.z * vec_p2.x) <= 0) {
		D3DXVECTOR3 face_nor = faceNormal_[x * 2 + z * blockNumX_ * 2];
		//D3DXVec3TransformCoord(&face_nor, &faceNormal_[x * 2 + z * blockNumX_ * 2], &mtx);
				
		// 高さを取得
		height = GetHeightPolygon(pos0, pos, face_nor);

		// 頂点情報のアンロック
		vertexBuffer_->Unlock();


		return height;
	}

	// 二枚目のポリゴン
	vec0 = pos1 - pos2;
	vec1 = pos3 - pos1;
	vec2 = pos2 - pos3;
	vec_p0 = pos - pos2;
	vec_p1 = pos - pos1;
	vec_p2 = pos - pos3;

	// 外積による内外判定
	if ((vec0.x * vec_p0.z - vec0.z * vec_p0.x) <= 0
		&& (vec1.x * vec_p1.z - vec1.z * vec_p1.x) <= 0
		&& (vec2.x * vec_p2.z - vec2.z * vec_p2.x) <= 0) {
		// 回転後の法線の計算
		D3DXVECTOR3 face_nor = faceNormal_[x * 2 + z * blockNumX_ * 2 + 1];
		//D3DXVec3TransformCoord(&face_nor, &faceNormal_[x * 2 + z * blockNumX_ * 2 + 1], &mtx);

		// 高さを取得
		height = GetHeightPolygon(pos3, pos, face_nor);

		// 頂点情報のアンロック
		vertexBuffer_->Unlock();


		return height;
	}

	// 頂点情報のアンロック
	vertexBuffer_->Unlock();


	return height;
}

//=========================================================================
// 高さの計算処理
//=========================================================================
float MeshField::GetHeightPolygon(D3DXVECTOR3 pos0, D3DXVECTOR3 pos1, D3DXVECTOR3 nor)
{
	if (nor.y) {
		float height;
		height = pos0.y - ((pos1.x - pos0.x) * nor.x + (pos1.z - pos0.z) * nor.z) / nor.y;
		return height;
	}


	return 0.0f;
}


// End of file.