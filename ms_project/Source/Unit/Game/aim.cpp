//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// AIM
// 
// Created by Ryusei Kajiya on 20151029
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//*****************************************************************************
// include
#include "Unit/Game/aim.h"
#include "Unit/Game/aim_draw.h"
#include "Unit/Game/aim_line.h"

//=============================================================================
// 初期化
void AimUnit::Initialize()
{
	// 描画用AIMの作成
	_aim_draw = new AimDrawUnit(_application,_game_world);
	_aim_line = new AimLineUnit(_application, _game_world);
}

//=============================================================================
// 終了
void AimUnit::Finalize()
{
	SafeDelete(_aim_line);
	SafeDelete(_aim_draw);
}

//=============================================================================
// 更新
void AimUnit::Update()
{
	_aim_line->Update();
	_aim_draw->Update();
}

//=============================================================================
// 更新
void AimUnit::CollisionUpdate()
{
	_aim_line->CollisionUpdate();
}

//=============================================================================
// 描画
void AimUnit::Draw()
{
	_aim_line->Draw();
	_aim_draw->Draw();
}

//=============================================================================
// ラインの始点設定
void AimUnit::SetStartPosition(const D3DXVECTOR3& position)
{
	_aim_line->SetStartPosition(position);
}

//=============================================================================
// ラインの終点設定
void AimUnit::SetEndPosition(const D3DXVECTOR3& position)
{
	_aim_line->SetEndPosition(position);
}

//=============================================================================
// ラインの始点を取得
D3DXVECTOR3& AimUnit::GetStartPosition()
{
	return _aim_line->GetStartPosition();
}

//=============================================================================
// ラインの終点を取得
D3DXVECTOR3& AimUnit::GetEndPosition()
{
	return _aim_line->GetEndPosition();
}
