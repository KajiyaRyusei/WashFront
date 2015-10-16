//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// アプリケーション
// 
// Created by Ryusei Kajiya on 20151009
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
template<class t>class ResourceBox;
class EffectHandleManager;
class CommandBuffer;
class CommandProcessor;
class MeshBuffer;
class Fade;

//*****************************************************************************
// クラス設計
class Application
{
public:
	Application(Window *window, RendererDevice *renderer_device): 
		_window(window),
		_renderer_device(renderer_device),
		_input_manager(nullptr),
		_scene_manager(nullptr),
		_camera_manager(nullptr),
		_develop_manager(nullptr),
		_texture_box(nullptr),
		_effect_handle_manager(nullptr),
		_command_buffer(nullptr),
		_command_processor(nullptr),
		_fade(nullptr)
	{
		Initalize(window, renderer_device);
	}
	virtual ~Application(){ Finalize(); }
	// 初期化
	void Initalize(Window *window, RendererDevice *renderer_device);
	// 終了
	void Finalize();
	// 更新
	void Update();
	// 描画
	void Draw();

	// 取得
	Window* GetWindow()const { return _window; }
	RendererDevice* GetRendererDevice()const { return _renderer_device; }
	InputManager* GetInputManager()const { return _input_manager; }
	SceneManager* GetSceneManager()const { return _scene_manager; }
	CameraManager* GetCameraManager()const { return _camera_manager; }
	DevelopToolManager* GetDevelopToolManager()const{ return _develop_manager; }
	ResourceBox<LPDIRECT3DTEXTURE9>* GetTextureBox() const{ return _texture_box; }
	ResourceBox<MeshBuffer>* GetMeshBox() const{ return _mesh_box; }

private:

	Window *_window;
	RendererDevice *_renderer_device;
	InputManager* _input_manager;
	SceneManager* _scene_manager;
	CameraManager* _camera_manager;
	DevelopToolManager* _develop_manager;
	ResourceBox<LPDIRECT3DTEXTURE9>* _texture_box;
	ResourceBox<MeshBuffer>* _mesh_box;
	EffectHandleManager* _effect_handle_manager;
	CommandBuffer* _command_buffer;
	CommandProcessor* _command_processor;
	Fade* _fade;
};