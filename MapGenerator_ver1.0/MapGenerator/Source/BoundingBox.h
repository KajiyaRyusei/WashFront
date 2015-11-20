//=============================================================================
//
// AABB 軸平衡境界ボックスクラス [BoundingBox.h]
// Author : KEITA OHUCHI
//
//=============================================================================
#ifndef _BOUNDING_BOX_H_
#define _BOUNDING_BOX_H_

#include "Manager.h"
#include "Renderer.h"
#include "Shape.h"


//-----------------------------------------------------------------------------
// クラス定義
//-----------------------------------------------------------------------------
class BoundingBox : public Shape{
public:
	//=========================================================================
	// コンストラクタとデストラクタ
	//=========================================================================
	BoundingBox() {};
	virtual ~BoundingBox() {};

	//=========================================================================
	// 描画処理
	//=========================================================================
	void Draw() {
		D3DXVECTOR3 vertexPos[8] = {
			D3DXVECTOR3(min_.x, max_.y, max_.z),
			D3DXVECTOR3(max_.x, max_.y, max_.z),
			D3DXVECTOR3(min_.x, max_.y, min_.z),
			D3DXVECTOR3(max_.x, max_.y, min_.z),
			D3DXVECTOR3(min_.x, min_.y, max_.z),
			D3DXVECTOR3(max_.x, min_.y, max_.z),
			D3DXVECTOR3(min_.x, min_.y, min_.z),
			D3DXVECTOR3(max_.x, min_.y, min_.z)
		};

		int line[12][2] = {
			{0, 1},
			{2, 3},
			{4, 5},
			{6, 7},
			{0, 2},
			{1, 3},
			{4, 6},
			{5, 7},
			{0, 4},
			{1, 5},
			{2, 6},
			{3, 7},
		};

		VERTEX_3D vertex[2];
		vertex[0].diffuse = D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f);
		vertex[1].diffuse = D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f);

		LPDIRECT3DDEVICE9 device = Manager::GetInstance()->GetRenderer()->GetDevice();
		device->SetFVF(FVF_VERTEX_3D);		// 頂点フォーマットの設定

		// ワールドマトリックスの設定
		D3DXMATRIX worldMatrix;
		D3DXMatrixIdentity(&worldMatrix);
		device->SetTransform(D3DTS_WORLD, &worldMatrix);

		for (int count = 0; count < 12; ++count) {
			vertex[0].vtx = vertexPos[line[count][0]];
			vertex[1].vtx = vertexPos[line[count][1]];

			device->DrawPrimitiveUP(D3DPT_LINELIST, 1, vertex, sizeof(VERTEX_3D));
		}
	};


	//=========================================================================
	// 形状の取得処理
	//=========================================================================
	SHAPE_TYPE GetType() { return SHAPE_TYPE_BOX; };
	//=========================================================================
	// 最小座標の取得処理
	//=========================================================================
	D3DXVECTOR3 GetMin() { return min_; };
	//=========================================================================
	// 最大座標の取得処理
	//=========================================================================
	D3DXVECTOR3 GetMax() { return max_; };

	//=========================================================================
	// 最小座標の設定処理
	//=========================================================================
	void SetMin(D3DXVECTOR3 min) { min_ = min; };
	//=========================================================================
	// 最大座標の設定処理
	//=========================================================================
	void SetMax(D3DXVECTOR3 max) { max_ = max; };

	//=========================================================================
	// 座標の設定処理
	//=========================================================================
	void SetCenterPosition(D3DXVECTOR3 position, D3DXVECTOR3 scale) {
		min_ = position - scale / 2;
		max_ = position + scale / 2;
	};


private:
	D3DXVECTOR3 min_;  // 最小座標
	D3DXVECTOR3 max_;  // 最大座標
};


#endif


// End of file