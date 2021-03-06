//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// シーン：ゲーム
// 
// Created by Ryusei Kajiya on 20151130
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//*****************************************************************************
// 多重インクルード防止
#pragma once

//*****************************************************************************
// インクルード
#include "scene.h"
#include "Data/data_dirt.h"

//*****************************************************************************
// 前方宣言
class World;
class PlayerUnit;

//*****************************************************************************
// クラス設計
class SceneGame : public Scene
{
public:

	// コンストラクタ
	explicit SceneGame(Application* application);

	// デストラクタ
	virtual ~SceneGame(){ Finalize(); }

	// 初期化
	virtual void Initialize() override;

	// 終了
	virtual void Finalize() override;

	// 更新
	virtual void Update() override;

	// 描画
	virtual void Draw() override;

private:
	World* _world;

	void MapGeneration();
	void ResourceGeneration();
	void RouteRead();
	std::vector<data::Dirt> DirtyRead();
};

