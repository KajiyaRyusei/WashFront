//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// 参照群
//
// Created by Ryusei Kajiya on 20151006
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//*****************************************************************************
// 多重インクルード防止
#pragma once

//*****************************************************************************
// 前方宣言
class Window;
class RendererDevice;
class InputManager;
class SceneManager;
class CameraManager;
class DevelopToolManager;
class EffectHandleManager;
class MeshBuffer;
template<class t>class ResourceBox;

//*****************************************************************************
// クラス設計
class Reference
{
public:

	Reference(){}

	static Reference& GetInstance()
	{
		static Reference instance;
		return instance;
	}

	// 画面サイズ
	const u32 GetSizeScreenWidth()const{ return _size_screen_width; }
	void SetSizeScreenWidth(const u32 width){ _size_screen_width = width; }
	const u32 GetSizeScreenHeight()const{ return _size_screen_height; }
	void SetSizeScreenHeight(const u32 height){ _size_screen_height = height; }

	// ウィンドウハンドル
	HWND GetHandleWindow()const{ return _handle_window; }
	void SetHandleWindow(HWND handle){ _handle_window = handle; }

	// インスタンスハンドル
	HINSTANCE GetHandleInstance()const{ return _handle_instance; }
	void SetHandleInstance(HINSTANCE handle){ _handle_instance = handle; }

	// 描画デバイス
	RendererDevice* GetRenderer() const { return _renderer; }
	void SetRenderer(RendererDevice* renderer){ _renderer = renderer; }

	// 入力管理
	InputManager* GetInputManager() const{ return _input_manager; }
	void SetInputManager(InputManager* manager){ _input_manager = manager; }

	// シーン管理
	SceneManager* GetSceneManager() const{ return _scene_manager; }
	void SetSceneManager(SceneManager* manager){ _scene_manager = manager; }

	// カメラ管理
	CameraManager* GetCameraManager() const { return _camera_manager; }
	void SetCameraManager(CameraManager* manager){ _camera_manager = manager; }

	// デベロップツール管理
	DevelopToolManager* GetDevelopToolManager() const { return _develop_tool_manager; }
	void SetDevelopToolManager(DevelopToolManager* develop_tool_manager) { _develop_tool_manager =  develop_tool_manager; }

	// エフェクトハンドル管理
	EffectHandleManager* GetEffectHandleManager() const{ return _effect_handle_manager; }
	void SetEffectHandleManager(EffectHandleManager* effect_handle_manager){ _effect_handle_manager = effect_handle_manager; }

	// テクスチャボックス
	ResourceBox<LPDIRECT3DTEXTURE9>* GetTextureBox() const{ return _texture_box; }
	void SetTextureBox(ResourceBox<LPDIRECT3DTEXTURE9>* texture_box){ _texture_box  = texture_box; }

	// メッシュボックス
	ResourceBox<MeshBuffer>* GetMeshBox() const{ return _mesh_box; }
	void SetMeshBox(ResourceBox<MeshBuffer>* mesh_box){ _mesh_box = mesh_box; }

	// キューブテクスチャボックス
	ResourceBox<LPDIRECT3DCUBETEXTURE9>* GetCubeTextureBox() const{ return _cube_texture_box; }
	void SetCubeTextureBox(ResourceBox<LPDIRECT3DCUBETEXTURE9>* cube_texture_box){ _cube_texture_box = cube_texture_box; }

private:

	u32 _size_screen_width,
		_size_screen_height;

	HWND _handle_window;
	HINSTANCE _handle_instance;
	RendererDevice* _renderer;
	InputManager* _input_manager;
	SceneManager* _scene_manager;
	CameraManager* _camera_manager;
	DevelopToolManager* _develop_tool_manager;
	EffectHandleManager* _effect_handle_manager;
	ResourceBox<LPDIRECT3DTEXTURE9>* _texture_box;
	ResourceBox<MeshBuffer>* _mesh_box;
	ResourceBox<LPDIRECT3DCUBETEXTURE9>* _cube_texture_box;

};
