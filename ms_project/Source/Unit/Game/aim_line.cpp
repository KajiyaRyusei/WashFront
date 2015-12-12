//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// AIMの線
// 
// Created by Ryusei Kajiya on 20151029
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//*****************************************************************************
// include
#include "Unit/Game/aim_line.h"
#include "Shader/Shader/aim_shader.h"
#include "Resource/Mesh/Mesh/mesh_factory_sprite.h"
#include "Camera/camera_manager.h"
#include "Camera/Camera/camera_game_player.h"
#include "DevelopTool/develop_tool_manager.h"
#include "World/collision_grid.h"

//=============================================================================
// 初期化
void AimLineUnit::Initialize()
{
	CreateVolumeLine(D3DXVECTOR3(0.f, 0.f, 0.f), D3DXVECTOR3(0.f, 0.f, 1.f));
	_position.current = D3DXVECTOR3(0.f,0.f,0.f);
	_position.previous = _position.current;
	_game_world->GetCollisionGrid()->AddUnit(this, _position);
}

//=============================================================================
// 終了
void AimLineUnit::Finalize()
{

}

//=============================================================================
// 更新
void AimLineUnit::Update()
{
	_game_world->GetCollisionGrid()->MoveUnit(this, _position);
}

//=============================================================================
// 衝突更新
void AimLineUnit::CollisionUpdate()
{
	_is_hit = false;
	s32 cell_x = 0;
	s32 cell_z = 0;
	_game_world->GetCollisionGrid()->SelfCoordinatesCell(&cell_x, &cell_z, _position);
	_game_world->GetCollisionGrid()->HandleCell(cell_x, cell_z);
}
//=============================================================================
// 線とボックスが衝突していた時の処理
void AimLineUnit::CollisionLine(const D3DXVECTOR3& impact_point)
{
	_is_hit = true;
	_line->end_point = impact_point;
}

//=============================================================================
// 描画
void AimLineUnit::Draw()
{
	Reference::GetInstance().GetDevelopToolManager()->GetDebugLine().RegisteLine(_line->start_point, _line->end_point);
	Reference::GetInstance().GetDevelopToolManager()->GetDebugSphere().RegisteSphere(0.5f, _line->end_point);
}
