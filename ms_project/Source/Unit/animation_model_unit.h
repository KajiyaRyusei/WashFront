//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// アニメーションモデル
// 
// Created by Ryusei Kajiya on 20151014
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//*****************************************************************************
// 多重インクルード防止
#pragma once

//*****************************************************************************
// include
#include "unit.h"
#include "Data/data_oaf.h"

//*****************************************************************************
// 前方宣言
class ShaderAnimation;
class MeshBuffer;
class AnimationSystem;

//*****************************************************************************
// クラス設計
class AnimationModelUnit : public Unit
{
public:

	AnimationModelUnit(Application* application, SpaceGrid* grid) : Unit(application, grid)
	{
		Initialize();
	}
	virtual ~AnimationModelUnit(){ Finalize(); }

	virtual void Initialize() override;
	virtual void Finalize() override;
	virtual void Update() override;
	virtual void Draw() override;

private:

	// シェーダー
	ShaderAnimation* _shader;
	// メッシュ
	std::vector<MeshBuffer*> _mesh_list;
	// アニメーション
	data::ObjectAnimationFile _animation;
	// アニメーションシステム
	AnimationSystem* _animation_system;

};