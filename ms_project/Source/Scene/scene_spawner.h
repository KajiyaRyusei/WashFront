//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// シーン生成
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
class Application;

//*****************************************************************************
// クラス設計
class SpawnerScene
{
public:
	virtual ~SpawnerScene(){}
	virtual Scene* Spawner(Application* applicaion) = 0;
};

template <class T>
class SpawnerForScene : public SpawnerScene
{
public:
	Scene* Spawner(Application* applicaion){ return new T(applicaion); }
};