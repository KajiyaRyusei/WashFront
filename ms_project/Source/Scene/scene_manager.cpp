//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// シーンマネージャー
//
// Created by Ryusei Kajiya on 20151006
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//*****************************************************************************
// インクルード
#include "scene_manager.h"
#include "scene_spawner.h"
#include "Scene/scene.h"
#include "Scene/scene_game.h"
#include "Scene/scene_title.h"

#include "Fade/fade.h"

//=============================================================================
// コンストラクタ
SceneManager::SceneManager(Application *application, Fade* fade) :
	_scene_current{ nullptr },
	_scene_spawner_next{nullptr},
	_application{ application },
	_fade(fade)
{
	Initialize(application);
}

//=============================================================================
// 初期化
void SceneManager::Initialize(Application *application)
{
	SpawnerScene* spawner = new SpawnerForScene<SceneTitle>();
	_scene_current = spawner->Spawner(_application);
	ASSERT(_scene_current != nullptr,"シーンが生成されてません");
	SafeDelete(spawner);

	UNREFERENCED_PARAMETER(application);
}
//=============================================================================
// 終了
void SceneManager::Finalize()
{
	SafeDelete(_scene_current);
	SafeDelete(_scene_spawner_next);
}
//=============================================================================
// 更新
void SceneManager::Update()
{
	if( _scene_spawner_next != nullptr )
	{// 次のシーンのファクトリが存在するなら

		if( _fade->IsFadeTop() == true )
		{
			SafeDelete(_scene_current);

			// シーンの生成と初期化
			_scene_current = _scene_spawner_next->Spawner(_application);

			// ファクトリの削除
			SafeDelete(_scene_spawner_next);
		}
	}

	if (_scene_current == nullptr)
	{// シーンが存在しなければ
		OutputDebugStringA("シーンが存在しません\n");
		return;
	}

	_fade->Update();

	_scene_current->Update();
}

//=============================================================================
// 描画
void SceneManager::Draw()
{
	if (_scene_current == nullptr)
	{// シーンが存在しなければ
		OutputDebugStringA("シーンが存在しません\n");
		return;
	}
	_scene_current->Draw();
}
//=============================================================================
// 次のシーンを割り当てる
void SceneManager::SetNextScene(
	SpawnerScene *next_scene)
{
	if( _fade ->IsFadeNow() == false)
	{
		SafeDelete(_scene_spawner_next);
		_scene_spawner_next = next_scene;

		// fadeIn
		_fade->FadeIn();
	}
	else
	{
		SafeDelete(next_scene);
	}
	
}
