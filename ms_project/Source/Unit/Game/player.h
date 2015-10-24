//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// プレイヤー
// 
// Created by Ryusei Kajiya on 20151022
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//*****************************************************************************
// 多重インクルード防止
#pragma once

//*****************************************************************************
// include
#include "Unit/unit.h"
#include "Data/data_oaf.h"

//*****************************************************************************
// 前方宣言
class ShaderPBLAnimation;
class MeshBuffer;
class AnimationSystem;

//*****************************************************************************
// クラス設計
class PlayerUnit : public Unit
{
public:

	PlayerUnit(Application* application, SpaceGrid* grid) : Unit(application, grid)
	{
		Initialize();
	}
	virtual ~PlayerUnit(){ Finalize(); }

	virtual void Initialize() override;
	virtual void Finalize() override;
	virtual void Update() override;
	virtual void Draw() override;

private:

	// シェーダー
	ShaderPBLAnimation* _shader;
	// メッシュ
	std::vector<MeshBuffer*> _mesh_list;
	// アニメーション
	data::ObjectAnimationFile _animation;
	// アニメーションシステム
	AnimationSystem* _animation_system;

	// シェーダパラメーターの設定
	void SettingShaderParameter();

};