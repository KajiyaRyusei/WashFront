//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// アプリケーション
// 
// Created by Ryusei Kajiya on 20151130
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
class CommandBuffer;
class CommandProcessor;
class Fade;
class XactManager;

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
	void Update(u64 fps);
	// 描画
	void Draw();

	// 取得
	Window* GetWindow()const { return _window; }
	RendererDevice* GetRendererDevice()const { return _renderer_device; }
	InputManager* GetInputManager()const { return _input_manager; }
	SceneManager* GetSceneManager()const { return _scene_manager; }
	CameraManager* GetCameraManager()const { return _camera_manager; }
	DevelopToolManager* GetDevelopToolManager()const{ return _develop_manager; }
	XactManager* GetXactManager() const{ return _xact_manager; }
	CommandBuffer* GetCommandBuffer() const { return _command_buffer; }
	CommandProcessor* GetCommandProcessor() const { return _command_processor; }

private:

	Window *_window;
	RendererDevice *_renderer_device;
	InputManager* _input_manager;
	SceneManager* _scene_manager;
	CameraManager* _camera_manager;
	DevelopToolManager* _develop_manager;
	EffectHandleManager* _effect_handle_manager;
	CommandBuffer* _command_buffer;
	CommandProcessor* _command_processor;
	Fade* _fade;
	XactManager* _xact_manager;
};