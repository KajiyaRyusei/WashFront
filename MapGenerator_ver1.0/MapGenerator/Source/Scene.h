//=============================================================================
//
// オブジェクトのスーパークラス [Scene.h]
// Author : KEITA OHUCHI
//
//=============================================================================
#ifndef _SCENE_H_
#define _SCENE_H_

#include <Windows.h>
#include "Main.h"


//-----------------------------------------------------------------------------
// 列挙型定義
//-----------------------------------------------------------------------------
enum {  // プライオリティ
	PRIORITY_WATER = (0),
	PRIORITY_SKY,
	PRIORITY_MOUNTAIN,
	PRIORITY_FIELD,
	PRIORITY_STENCIL_SHADOW,
	PRIORITY_BUILDING,
	PRIORITY_PLAYER,
	PRIORITY_ENEMY,
	PRIORITY_ORBIT,
	PRIORITY_ITEM,
	PRIORITY_WEED,
	PRIORITY_TREE,
	PRIORITY_UI,
	PRIORITY_FADE,
	PRIORITY_MAX
};

enum OBJECTTYPE {  // オブジェクトの種類
	OBJECTTYPE_NONE = (0),
	OBJECTTYPE_PLAYER,
	OBJECTTYPE_ENEMY,
	OBJECTTYPE_BULLET,
	OBJECTTYPE_TREE,
	OBJECTTYPE_WEED,
	OBJECTTYPE_EXPLOSION,
	OBJECTTYPE_ITEM,
	OBJECTTYPE_GIMMICK,
	OBJECTTYPE_GOAL,
	OBJECTTYPE_MAX
};


//-----------------------------------------------------------------------------
// 前方宣言
//
// ※当たり判定を行うすべてのクラスを列挙すること
//-----------------------------------------------------------------------------
class PlayerBird;
class Enemy;
class ItemPlus;


//-----------------------------------------------------------------------------
// クラス定義
//-----------------------------------------------------------------------------
class Scene {
public:
	//=========================================================================
	// コンストラクタとデストラクタ
	//=========================================================================
	Scene(int priotiry);
	virtual ~Scene();

	//=========================================================================
	// 初期化処理
	//=========================================================================
	virtual HRESULT Init() = 0;
	//=========================================================================
	// 更新処理
	//=========================================================================
	virtual void Update() = 0;
	//=========================================================================
	// 描画処理
	//=========================================================================
	virtual void Draw() = 0;

	//=========================================================================
	// 解放処理
	//=========================================================================
	void Release();

	//=========================================================================
	// 全オブジェクトの更新処理
	//=========================================================================
	static void UpdateAll();
	//=========================================================================
	// 全オブジェクトの描画処理
	//=========================================================================
	static void DrawAll();
	//=========================================================================
	// 全オブジェクトの解放処理
	//=========================================================================
	static void ReleaseAll();

	//=========================================================================
	// リストに追加する処理
	//=========================================================================
	void LinkList();
	//=========================================================================
	// リストから削除する処理
	//=========================================================================
	void UnlinkList();

	//=========================================================================
	// リストの先頭アドレスへのアクセサ
	//=========================================================================
	static Scene *GetFirst(int priority) { return first_[priority]; };
	//=========================================================================
	// リストの終端アドレスへのアクセサ
	//=========================================================================
	Scene *GetLast(int priority) { return last_[priority]; };
	//=========================================================================
	// 次のアドレスへのアクセサ
	//=========================================================================
	Scene *GetNext() { return next_; };

	//=========================================================================
	// テクスチャの設定
	//=========================================================================
	void SetTexture(char *fileName);
	//=========================================================================
	// 座標の設定
	//=========================================================================
	void SetPosition(D3DXVECTOR3 pos) { position_ = pos; };
	//=========================================================================
	// 描画フラグの設定
	//=========================================================================
	void SetRenderFlag(bool flag) { renderFlag_ = flag; };
	//=========================================================================
	// 座標の取得
	//=========================================================================
	D3DXVECTOR3 GetPosition() { return position_; };
	//=========================================================================
	// 種類の取得
	//=========================================================================
	OBJECTTYPE GetType() { return type_; };


	//=========================================================================
	// 衝突判定関数群
	// 戻り値 : 衝突判定領域の削除
	//=========================================================================
	virtual bool Collision(Scene *object) { return false; };

	virtual bool Action(PlayerBird *playerBird) { return false; };
	virtual bool Action(Enemy *enemy) { return false; };
	virtual bool Action(ItemPlus *item) { return false; };


protected:
	LPDIRECT3DTEXTURE9	texture_;				// テクスチャへのポインタ
	D3DXVECTOR3			position_;				// 座標
	OBJECTTYPE			type_;					// オブジェクトの種類
	bool				renderFlag_;			// 描画フラグ

private:
	static Scene	*first_[PRIORITY_MAX];		// リストの先頭アドレス
	static Scene	*last_[PRIORITY_MAX];		// リストの終端アドレス
	Scene			*prev_;						// 前のインスタンスへのポインタ
	Scene			*next_;						// 次のインスタンスへのポインタ
	int				priority_;					// プライオリティ
	bool			deleteFlag_;				// 削除フラグ
};


#endif


// End of file