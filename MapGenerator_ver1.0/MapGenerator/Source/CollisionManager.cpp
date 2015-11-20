//=============================================================================
//
// 衝突判定管理クラス [CollisionManager.cpp]
// Author : KEITA OHUCHI
//
//=============================================================================

#include "CollisionManager.h"
#include "BoxAndBox.h"
#include "BoxAndSphere.h"
#include "SphereAndSphere.h"
#include "Scene.h"
#ifdef _DEBUG
#include "Keyboard.h"
#include "Debug.h"
#endif


//-----------------------------------------------------------------------------
// 静的メンバ変数
//-----------------------------------------------------------------------------
// [0 or 1] : 判定するかどうか決める
// [false]  : 判定は必ず行われない
bool CollisionManager::collisionLayer_[COLLISION_LAYER_MAX][COLLISION_LAYER_MAX] = {
	/*
	{0,	 0,	 0,	 0,	 0,	 0,	 0,	 0,	 0,	 0},  // NONE
	{false, 0,	 0,	 0,	 0,	 0,	 0,	 0,	 0,	 1},  // PLAYER
	{false, false, 0,	 0,	 0,	 0,	 0,	 0,	 0,	 0},  // ENEMY
	{false, false, false, 0,	 0,	 0,	 0,	 0,	 0,	 0},  // BULLET
	{false, false, false, false, 0,	 0,	 0,	 0,	 0,	 0},  // TREE
	{false, false, false, false, false, 0,	 0,	 0,	 0,	 0},  // WEED
	{false, false, false, false, false, false, 0,	 0,	 0,	 0},  // EXPLOSION
	{false, false, false, false, false, false, false, 0,	 0,	 0},  // ITEM
	{false, false, false, false, false, false, false, false, 0,	 0},  // GIMMICK
	{false, false, false, false, false, false, false, false, false, 0},  // GOAL
	*/
};


//=========================================================================
// コンストラクタ
//=========================================================================
CollisionManager::CollisionManager()
{
	// 衝突判定テーブルの生成
	checkTable_[SHAPE_TYPE_BOX][SHAPE_TYPE_BOX] = new BoxAndBox();
	checkTable_[SHAPE_TYPE_BOX][SHAPE_TYPE_SPHERE] = new BoxAndSphere();
	checkTable_[SHAPE_TYPE_SPHERE][SHAPE_TYPE_BOX] = new BoxAndSphere();
	checkTable_[SHAPE_TYPE_SPHERE][SHAPE_TYPE_SPHERE] = new SphereAndSphere();

	collisionLayer_[COLLISION_LAYER_PLAYER][COLLISION_LAYER_ENEMY] = true;
	//collisionLayer_[COLLISION_LAYER_ENEMY][COLLISION_LAYER_ENEMY] = true;
	collisionLayer_[COLLISION_LAYER_PLAYER][COLLISION_LAYER_ITEM] = true;

#ifdef _DEBUG
	shapeRenderFlag_ = false;
#else
	shapeRenderFlag_ = false;
#endif
}

//=========================================================================
// デストラクタ
//=========================================================================
CollisionManager::~CollisionManager()
{
	for (int i = 0; i < SHAPE_TYPE_MAX; ++i) {
		for (int j = 0; j < SHAPE_TYPE_MAX; ++j) {
			delete checkTable_[i][j];
		}
	}
}

//=========================================================================
// 初期化処理
//=========================================================================
HRESULT CollisionManager::Init()
{
	return S_OK;
}

//=========================================================================
// 更新処理
//=========================================================================
void CollisionManager::Update()
{
	// 別レイヤーの全オブジェクトの衝突判定
	for (int i = 0; i < COLLISION_LAYER_MAX; ++i) {
		for (int j = i + 1; j < COLLISION_LAYER_MAX; ++j) {
			// テーブルで判定を行うか確認
			if (collisionLayer_[i][j]) {
				// イテレータ
				list<Shape *>::iterator itrA;
				list<Shape *>::iterator itrB;
				
				// リスト内の衝突判定
				for (itrA = objectList_[i].begin();
					 itrA != objectList_[i].end(); ) {
					for (itrB = objectList_[j].begin();
						 itrB != objectList_[j].end(); ) {
							 
						// 衝突判定
						if (CheckCollision((*itrA), (*itrB))) {
							// 親の取得
							Scene *sceneA = (*itrA)->GetParent();
							Scene *sceneB = (*itrB)->GetParent();

							// 衝突処理
							bool eraseFlagA = sceneB->Collision(sceneA);
							bool eraseFlagB = sceneA->Collision(sceneB);

							// リストから削除
							if (eraseFlagA && eraseFlagB) {
								itrA = objectList_[i].erase(itrA);
								objectList_[j].erase(itrB);
								itrB = objectList_[j].begin();
								continue;
							}
							if (eraseFlagA) {
								itrA = objectList_[i].erase(itrA);
								itrB = objectList_[j].begin();
								continue;
							}
							if (eraseFlagB) {
								itrB = objectList_[j].erase(itrB);
								continue;
							}
						}

						itrB++;
					}

					itrA++;
				}
			}
		}
	}

	// 同一レイヤーの全オブジェクトの衝突判定
	for (int i = 0; i < COLLISION_LAYER_MAX; ++i) {
		
		// 判定を行うか確認
		if (collisionLayer_[i][i]) {
			// イテレータ
			list<Shape *>::iterator itrA;
			list<Shape *>::iterator itrB;
				
			// リスト内の衝突判定
			for (itrA = objectList_[i].begin();
				 itrA != objectList_[i].end(); ) {
				itrB = itrA;
				itrB++;

				for (; itrB != objectList_[i].end(); ) {
						
					// 衝突判定
					if (CheckCollision((*itrA), (*itrB))) {
						// 親の取得
						Scene *sceneA = (*itrA)->GetParent();
						Scene *sceneB = (*itrB)->GetParent();

						// 衝突処理
						bool eraseFlagA = sceneB->Collision(sceneA);
						bool eraseFlagB = sceneA->Collision(sceneB);

						// リストから削除
						if (eraseFlagA && eraseFlagB) {
							itrA = objectList_[i].erase(itrA);
							objectList_[i].erase(itrB);
							itrB = itrA;
							itrB++;
							continue;
						}
						if (eraseFlagA) {
							itrA = objectList_[i].erase(itrA);
							itrB = itrA;
							itrB++;
							continue;
						}
						if (eraseFlagB) {
							itrB = objectList_[i].erase(itrB);
							continue;
						}

					}

					itrB++;
				}

				itrA++;
			}
		}
	}


#ifdef _DEBUG
	if (Manager::GetInstance()->GetKeyboard()->GetTriggerKey(DIK_F1)) {
		if (shapeRenderFlag_) {
			shapeRenderFlag_ = false;
		} else {
			shapeRenderFlag_ = true;
		}
	}
	DebugProc::Printf("[F1] : DRAW COLLISION BOX[ON/OFF]\n");
#endif

}

//=========================================================================
// 描画処理
//=========================================================================
void CollisionManager::Draw()
{
	if (shapeRenderFlag_) {
		// ライトOFF
		Manager::GetInstance()->GetRenderer()->GetDevice()->SetRenderState(D3DRS_LIGHTING, FALSE);
		// テクスチャOFF
		Manager::GetInstance()->GetRenderer()->GetDevice()->SetTexture(0, nullptr);
		for (int count = 0; count < COLLISION_LAYER_MAX; ++count) {
			// イテレータ
			list<Shape *>::iterator itr;

			// リスト内の描画処理
			for (itr = objectList_[count].begin();
				 itr != objectList_[count].end();
				 ++itr) {
				(*itr)->Draw();
			}
		}
		// ライトON
		Manager::GetInstance()->GetRenderer()->GetDevice()->SetRenderState(D3DRS_LIGHTING, TRUE);
	}
}

//=========================================================================
// 衝突判定リストの追加処理
//=========================================================================
void CollisionManager::AddList(COLLISION_LAYER layer, Shape *shape)
{
	objectList_[layer].push_back(shape);
}

//=========================================================================
// 衝突判定リストの削除処理
//=========================================================================
void CollisionManager::RemoveList(COLLISION_LAYER layer, Shape *shape)
{
	objectList_[layer].remove(shape);
}

//=========================================================================
// 衝突判定リストの全削除処理
//=========================================================================
void CollisionManager::AllEraseList()
{
	list<Shape *>::iterator itr;
	for (int count = 0; count < COLLISION_LAYER_MAX; ++count) {
		for (itr = objectList_[count].begin();
			 itr != objectList_[count].end(); ) {
			// リストから削除
			itr = objectList_[count].erase(itr);
		}
	}
}

//=========================================================================
// 衝突判定選別処理
//=========================================================================
bool CollisionManager::CheckCollision(Shape *shapeA, Shape *shapeB)
{
	return checkTable_[shapeA->GetType()][shapeB->GetType()]->Check(shapeA, shapeB);
}


// End of file