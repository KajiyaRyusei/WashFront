//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// アプリケーション
// 
// Created by Ryusei Kajiya on 20151130
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//*****************************************************************************
// include
#include "application.h"
#include "Windows/window.h"
#include "Renderer/directx9.h"

// マネージャー群
#include "Scene/scene_manager.h"
#include "Input/input_manager.h"
#include "Camera/camera_manager.h"
#include "DevelopTool/develop_tool_manager.h"
#include "Shader/effect_handle_manager.h"
#include "Sound/sound.h"

// リソースボックス
#include "Resource/resource_box.h"

// 描画
#include "DrawCommand/command_processor.h"
#include "DrawCommand/command_buffer.h"
#include "DrawCommand/command_buffer_holder.h"

// fade
#include "Fade/fade.h"

//*****************************************************************************
// 定数
namespace
{
	static const u8 kClearColors[4] = {0,0,0,0};
}

//=============================================================================
// 初期化
void Application::Initalize(Window *window, RendererDevice *renderer_device)
{
	UNREFERENCED_PARAMETER(renderer_device);

	// ドローコマンド
	_command_buffer = new CommandBuffer();
	_command_processor = new CommandProcessor(*_command_buffer);
	CommandBufferHolder::S_SetCommandBuffer(_command_buffer);

	//------------------------------------
	// マネージャーの作成
	//------------------------------------
	// インプットマネージャーの作成
	_input_manager = new InputManager(window->GetHandleWindow(), window->GetHandleInstance());
	Reference::GetInstance().SetInputManager(_input_manager);

	// エフェクトハンドルマネージャーの作成
	_effect_handle_manager = new EffectHandleManager(renderer_device);
	Reference::GetInstance().SetEffectHandleManager(_effect_handle_manager);

	// フェードの作成
	_fade = new Fade(this);

	// soundの作成
	_sound = new CSound();
	_sound->Init(window->GetHandleWindow());

	// カメラマネージャーの作成
	_camera_manager = new CameraManager(this);
	Reference::GetInstance().SetCameraManager(_camera_manager);

	// シーンマネージャーの作成
	_scene_manager = new SceneManager(this,_fade);
	Reference::GetInstance().SetSceneManager(_scene_manager);


	// デベロップツールマネージャーの作成
	_develop_manager = new DevelopToolManager();
	Reference::GetInstance().SetDevelopToolManager(_develop_manager);

	
}
//=============================================================================
// 終了
void Application::Finalize()
{
	
	SafeDelete(_fade);
	SafeDelete(_camera_manager);
	SafeDelete(_develop_manager);
	SafeDelete(_scene_manager);
	SafeDelete(_effect_handle_manager);
	SafeDelete(_input_manager);

	if (_sound != nullptr)
	{
		_sound->Uninit();
	}
	SafeDelete(_sound);

	SafeDelete(_command_buffer);
	SafeDelete(_command_processor);

}
//=============================================================================
// 更新
void Application::Update(u64 fps)
{
	_develop_manager->GetDebugPrint().Print("FPS : %d\n", fps);
	_input_manager->Update();
	_scene_manager->Update();
	_camera_manager->Update();
	_develop_manager->Update();
}
//=============================================================================
// 描画
void Application::Draw()
{
	// バックバッファ＆Ｚバッファのクリア
	_renderer_device->Clear((D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL), kClearColors);

	// 描画の開始
	_renderer_device->Begin();

	// 各シーン描画
	_scene_manager->Draw();

	// fadeの描画
	_fade->Draw();

	// デバッグ情報の描画
	//_develop_manager->Draw();

	// 描画の終了
	_renderer_device->End();

	// バックバッファとフロントバッファの入れ替え
	_renderer_device->Swap();
}
