//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// シーンマネージャー
// 
// Created by Ryusei Kajiya on 20151006
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//*****************************************************************************
// 多重インクルード防止
#pragma once

//*****************************************************************************
// 前方宣言
class Scene;
class SpawnerScene;
class Application;
class Fade;

//*****************************************************************************
// クラス定義
class SceneManager
{
public:

	explicit SceneManager(Application* application,Fade* fade);

	virtual ~SceneManager(){ Finalize(); }

	// 初期化
	void Initialize(Application* application);

	// 終了
	void Finalize();

	// 更新
	void Update();

	// 描画
	void Draw();

	// 次のシーンを割り当てる
	void SetNextScene(
		SpawnerScene *next_scene);


private:

	// 現在のシーン
	Scene* _scene_current;

	// 次のシーンの生成
	SpawnerScene* _scene_spawner_next;

	// アプリケーション
	Application* _application;

	// フェード
	Fade* _fade;
};