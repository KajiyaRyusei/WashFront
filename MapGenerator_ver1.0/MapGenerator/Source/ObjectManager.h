//=============================================================================
//
// オブジェクトマネージャクラス [ObjectManager.h]
// Author : KEITA OHUCHI
//
//=============================================================================
#ifndef _OBJECT_MANAGER_H_
#define _OBJECT_MANAGER_H_

#include "Main.h"



//-----------------------------------------------------------------------------
// STL使用宣言
//-----------------------------------------------------------------------------
using namespace std;
#include <vector>


//-----------------------------------------------------------------------------
// 前方宣言
//-----------------------------------------------------------------------------

// ゲームオブジェクト
class MeshField;
class MeshCylinder;
class MeshDome;
class Player;
class Light;
class Scene3D;
class Building;

// 衝突判定
class CollisionManager;

class Cursor;



//-----------------------------------------------------------------------------
// クラス定義
//-----------------------------------------------------------------------------
class ObjectManager {
public:
	//=========================================================================
	// コンストラクタとデストラクタ
	//=========================================================================
	ObjectManager();
	virtual ~ObjectManager();

	//=========================================================================
	// 初期化処理
	//=========================================================================
	HRESULT Init();
	//=========================================================================
	// 更新処理
	//=========================================================================
	void Update();
	//=========================================================================
	// 描画処理
	//=========================================================================
	void Draw();

	//=========================================================================
	// マウスとオブジェクトの衝突判定
	//=========================================================================
	void CheckCollisionMouseAndObject();
	void CollisionMouseAndObject();


	//=========================================================================
	// インスタンスの生成
	//=========================================================================
	Building *CreateBuilding(const char *modelFileName, const char *textureFilePath);
	Building *CreateBuilding(const char *fileName, const char *textureFilePath,
		D3DXVECTOR3 position, D3DXVECTOR3 rotation, D3DXVECTOR3 scale, bool collision);
	Building *CopyBuilding();

	//=========================================================================
	// インスタンスの全削除
	//=========================================================================
	void AllDeleteBuilding();

	//=========================================================================
	// インスタンスの取得
	//=========================================================================
	MeshField *GetField() { return field_; };
	Player *GetPlayer() { return player_;  };
	CollisionManager *GetCollisionManager() { return collisionManager_; };
	Building *GetSelectBuilding();
	Cursor *GetCursor() { return cursor_; }


	//=========================================================================
	// 生成したオブジェクト情報を外部出力
	//=========================================================================
	void SaveBuildingData(FILE *outputFile);

	//=========================================================================
	// 生成するオブジェクト情報を外部入力
	//=========================================================================
	void ReadBuildingData(FILE *inputFile);


#ifdef _DEBUG
	// アップデートフラグの取得
	bool GetUpdateFlag() { return updateFlag_; };
#endif


private:
	static const int LIGHT_NUM = 3;

	Scene3D				*water_;					// 水


	// ライト
	Light				*light_[LIGHT_NUM];

	// ゲームオブジェクト
	MeshField			*field_;					// フィールド
	MeshCylinder		*mountain_;					// 山
	MeshDome			*sky_;						// 空
	Player				*player_;					// プレイヤー

	std::vector <Building*>	buildingList_;			// ビルのリスト
	int						buildingListCursor_;	// カーソル

	// 衝突判定
	CollisionManager	*collisionManager_;			// 衝突判定の管理

	Cursor				*cursor_;


#ifdef _DEBUG
	// 更新フラグ
	bool	updateFlag_;
#endif

};


#endif


// End of file