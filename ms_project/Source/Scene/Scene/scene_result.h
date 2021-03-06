//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// シーン：リザルト
// 
// Created by Ryusei Kajiya on 20151123
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//*****************************************************************************
// 多重インクルード防止
#pragma once

//*****************************************************************************
// インクルード
#include "scene.h"

//*****************************************************************************
// 前方宣言
class World;
class ScoreUnit;
class JudgeUnit;


//*****************************************************************************
// クラス設計
class SceneResult : public Scene
{
public:

	// コンストラクタ
	explicit SceneResult(Application* application);

	// デストラクタ
	virtual ~SceneResult(){ Finalize(); }

	// 初期化
	virtual void Initialize() override;

	// 終了
	virtual void Finalize() override;

	// 更新
	virtual void Update() override;

	// 描画
	virtual void Draw() override;

private:
	World*		_world;
	ScoreUnit*	_pScore[8];
	JudgeUnit*	_pJudge[2];
	float		_grade;

};

