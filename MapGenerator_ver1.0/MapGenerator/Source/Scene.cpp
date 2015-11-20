//=============================================================================
//
// オブジェクトのスーパークラス [Scene.cpp]
// Author : KEITA OHUCHI
//
//=============================================================================

#include "Main.h"
#include "Scene.h"
#include "Manager.h"
#include "TextureFactory.h"


//-----------------------------------------------------------------------------
// 静的メンバ変数
//-----------------------------------------------------------------------------
Scene *Scene::first_[PRIORITY_MAX] = {};	// リストの先頭アドレス
Scene *Scene::last_[PRIORITY_MAX] = {};	// リストの終端アドレス


//=========================================================================
// コンストラクタ
//=========================================================================
Scene::Scene(int priority) : renderFlag_(true)
{
	// メンバ変数の初期化
	texture_ = nullptr;
	position_ = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	priority_ = priority;
	deleteFlag_ = false;
	type_ = OBJECTTYPE_NONE;

	// リストに追加
	LinkList();
}

//=========================================================================
// デストラクタ
//=========================================================================
Scene::~Scene()
{
	// リストから削除
	UnlinkList();
}

//=========================================================================
// 解放処理
//=========================================================================
void Scene::Release()
{
	// 削除フラグON
	deleteFlag_ = true;
}

//=========================================================================
// 全インスタンスの更新処理
//=========================================================================
void Scene::UpdateAll()
{

	// 更新ループ
	for (int count = 0; count < PRIORITY_MAX; ++count) {
		Scene *curr = first_[count];
		Scene *next;

		// 全インスタンスの更新
		while (curr) {
			next = curr->next_;
			curr->Update();  // 更新処理

			// 削除フラグの確認
			if (curr->deleteFlag_) {
				// インスタンスの削除
				delete curr;
			}
			curr = next;  // カレントをずらす
		}
	}

}

//=========================================================================
// 全インスタンスの描画処理
//=========================================================================
void Scene::DrawAll()
{

	for (int count = 0; count < PRIORITY_MAX; ++count) {
		Scene *curr = first_[count];
		Scene *next;

		// 全インスタンスの更新
		while (curr) {
			next = curr->next_;  // 次のポインタ保存
			if (curr->renderFlag_) {
				curr->Draw();  // 描画処理
			}
			curr = next;  // カレントをずらす
		}
	}

}

//=========================================================================
// 全インスタンスの解放処理
//=========================================================================
void Scene::ReleaseAll()
{

	for (int count = 0; count < PRIORITY_MAX; ++count) {
		Scene *curr = first_[count];
		Scene *next;

		// 全インスタンスの更新
		while (curr) {
			next = curr->next_;  // 次のポインタ保存
			delete curr;  // 解放処理
			curr = next;  // カレントをずらす
		}
	}

}

//=========================================================================
// リストに追加する処理
//=========================================================================
void Scene::LinkList()
{

	if (!first_[priority_]) {  // リストが空の場合
		prev_ = nullptr;
		next_ = nullptr;
		first_[priority_] = this;
		last_[priority_] = this;
	} else {  // リストが存在する場合
		prev_ = last_[priority_];
		next_ = nullptr;
		prev_->next_ = this;
		last_[priority_] = this;
	}

}

//=========================================================================
// リストから削除する処理
//=========================================================================
void Scene::UnlinkList()
{

	if (first_[priority_] == last_[priority_]) {  // リストの要素がひとつの場合
		first_[priority_] = nullptr;
		last_[priority_] = nullptr;
	} else {  // 複数存在する場合
		if (this == first_[priority_]) {  // リストの先頭
			first_[priority_] = next_;
			next_->prev_ = nullptr;
		} else if (this == last_[priority_]) {  // リストの終端
			last_[priority_] = prev_;
			prev_->next_ = nullptr;
		} else {  // リストの中間
			prev_->next_ = next_;
			next_->prev_ = prev_;
		}
	}

}

//=========================================================================
// テクスチャ設定
//=========================================================================
void Scene::SetTexture(char *fileName)
{
	if (fileName) {
		texture_ = Manager::GetInstance()->GetTextureFactory()->GetTexture(fileName);
	}
}


// End of file