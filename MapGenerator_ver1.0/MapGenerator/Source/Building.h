//=============================================================================
//
// ビル [Building.h]
// Author : KEITA OHUCHI
//
//=============================================================================
#ifndef _BUILDING_H_
#define _BUILDING_H_

#include "Main.h"
#include "Scene.h"


// 衝突判定の半径
#define BUILDING_RADIUS (2.0f)


//-----------------------------------------------------------------------------
// 前方宣言
//-----------------------------------------------------------------------------
class Model;


//-----------------------------------------------------------------------------
// クラス定義
//-----------------------------------------------------------------------------
class Building : public Scene {
public:
	//=========================================================================
	// コンストラクタとデストラクタ
	//=========================================================================
	Building(int priority = PRIORITY_BUILDING);
	virtual ~Building();

	//=========================================================================
	// 初期化処理
	//=========================================================================
	HRESULT Init();
	HRESULT Init(const char *modelFilePath, const char *textureFilePath);
	HRESULT Init(const char *modelFilePath, const char *textureFilePath, D3DXVECTOR3 position, D3DXVECTOR3 rotation, D3DXVECTOR3 scale);
	//=========================================================================
	// 更新処理
	//=========================================================================
	void Update();
	//=========================================================================
	// 描画処理
	//=========================================================================
	void Draw();

	//=========================================================================
	// 回転角の取得
	//=========================================================================
	D3DXVECTOR3 GetRotation() { return rotation_; };
	//=========================================================================
	// 回転角の取得
	//=========================================================================
	D3DXVECTOR3 GetScale() { return scale_; };
	//=========================================================================
	// IDの取得
	//=========================================================================
	int GetId() { return id_; };

	//=========================================================================
	// ファイルパスの取得
	//=========================================================================
	char *GetModelFilePath() { return modelFilePath_; }
	//=========================================================================
	// ファイルパスの取得
	//=========================================================================
	char *GetTextureFilePath() { return textureFilePath_; }

	//=========================================================================
	// X座標の設定
	//=========================================================================
	void SetPositionX(float x) { position_.x = x; };
	//=========================================================================
	// Y座標の設定
	//=========================================================================
	void SetPositionY(float y) { position_.y = y; };
	//=========================================================================
	// Z座標の設定
	//=========================================================================
	void SetPositionZ(float z) { position_.z = z; };

	//=========================================================================
	// X軸回転の設定
	//=========================================================================
	void SetRotationX(float x) { rotation_.x = x; };
	//=========================================================================
	// Y軸回転の設定
	//=========================================================================
	void SetRotationY(float y) { rotation_.y = y; };
	//=========================================================================
	// Z軸回転の設定
	//=========================================================================
	void SetRotationZ(float z) { rotation_.z = z; };

	//=========================================================================
	// X方向スケールの設定
	//=========================================================================
	void SetScaleX(float x) { scale_.x = x; };
	//=========================================================================
	// Y方向スケールの設定
	//=========================================================================
	void SetScaleY(float y) { scale_.y = y; };
	//=========================================================================
	// Z方向スケールの設定
	//=========================================================================
	void SetScaleZ(float z) { scale_.z = z; };


	//=========================================================================
	// 回転角の設定
	//=========================================================================
	void SetRotation(D3DXVECTOR3 rotation) { rotation_ = rotation; };
	//=========================================================================
	// IDの設定
	//=========================================================================
	void SetId(int id) { id_ = id; };




protected:
	D3DXVECTOR3	rotation_;		// 回転角
	D3DXVECTOR3 scale_;			// スケール
	D3DXMATRIX	worldMatrix_;	// ワールドマトリクス

	Model		*model_;		// モデルのポインタ

	int			id_;			// 一意のID

	char		*modelFilePath_;
	char		*textureFilePath_;
};


#endif


// End of file