//=============================================================================
//
// マネージャクラス [Manager.h]
// Author : KEITA OHUCHI
//
//=============================================================================
#ifndef _MANAGER_H_
#define _MANAGER_H_

#include <Windows.h>


//-----------------------------------------------------------------------------
// 前方宣言
//-----------------------------------------------------------------------------
// 共通クラス
class Renderer;
class Keyboard;
class Mouse;
class DebugProc;
class TextureFactory;
class ModelFactory;
class CameraManager;
class ObjectManager;
class ImportFileManager;
class RouteManager;


//-----------------------------------------------------------------------------
// クラス定義
//-----------------------------------------------------------------------------
class Manager {
private:
	//=========================================================================
	// コンストラクタ
	//=========================================================================
	Manager();
	
public:
	//=========================================================================
	// デストラクタ
	//=========================================================================
	~Manager();

	//=========================================================================
	// インスタンスの取得
	//=========================================================================
	static Manager *GetInstance();
	//=========================================================================
	// インスタンスの破棄
	//=========================================================================
	static void Destory();


	//=========================================================================
	// 初期化処理
	//=========================================================================
	HRESULT Init(HINSTANCE instance, HWND wnd, BOOL window);
	//=========================================================================
	// 更新処理
	//=========================================================================
	void Update();
	//=========================================================================
	// 描画処理
	//=========================================================================
	void Draw();


	//=========================================================================
	// 保持しているインスタンスの取得
	//=========================================================================
	Renderer *GetRenderer() { return renderer_; };
	Keyboard *GetKeyboard() { return keyboard_; };
	Mouse *GetMouse() { return mouse_; };
	TextureFactory *GetTextureFactory() { return textureFactory_; };
	ModelFactory *GetModelFactory() { return modelFactory_; };
	CameraManager *GetCameraManager() { return cameraManager_; };
	ImportFileManager *GetImportFileManager() { return importFileManager_; }
	ObjectManager *GetObjectManager() { return objectManager_; }
	RouteManager *GetRouteManager() { return routeManager_; }


private:
	static Manager		*instance_;				// マネージャインスタンス



	// 共通クラス
	Renderer			*renderer_;				// レンダラー
	Keyboard			*keyboard_;				// キーボード入力
	Mouse				*mouse_;				// マウス入力
	DebugProc			*debugProc_;			// デバッグプロシージャ
	// マネージャ
	CameraManager		*cameraManager_;		// カメラマネージャ
	ObjectManager		*objectManager_;		// オブジェクトマネージャ
	ImportFileManager	*importFileManager_;	// ファイルの読み込みマネージャ
	RouteManager		*routeManager_;			// ルート管理マネージャ
	// ファクトリ
	TextureFactory		*textureFactory_;		// テクスチャファクトリ
	ModelFactory		*modelFactory_;			// モデルファクトリ

};


#endif


// End of file