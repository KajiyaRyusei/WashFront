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
// ������
void AimUnit::Initialize()
{
	// �`��pAIM�̍쐬
	_aim_draw = new AimDrawUnit(_application,_game_world);
	_aim_line = new AimLineUnit(_application, _game_world);
}

//=============================================================================
// �I��
void AimUnit::Finalize()
{
	SafeDelete(_aim_line);
	SafeDelete(_aim_draw);
}

//=============================================================================
// �X�V
void AimUnit::Update()
{
	_aim_line->Update();
	_aim_draw->Update();
}

//=============================================================================
// �X�V
void AimUnit::CollisionUpdate()
{
	_aim_line->CollisionUpdate();
}

//=============================================================================
// �`��
void AimUnit::Draw()
{
	_aim_line->Draw();
	_aim_draw->Draw();
}

//=============================================================================
// ���C���̎n�_�ݒ�
void AimUnit::SetStartPosition(const D3DXVECTOR3& position)
{
	_aim_line->SetStartPosition(position);
}

//=============================================================================
// ���C���̏I�_�ݒ�
void AimUnit::SetEndPosition(const D3DXVECTOR3& position)
{
	_aim_line->SetEndPosition(position);
}

//=============================================================================
// ���C���̎n�_���擾
D3DXVECTOR3& AimUnit::GetStartPosition()
{
	return _aim_line->GetStartPosition();
}

//=============================================================================
// ���C���̏I�_���擾
D3DXVECTOR3& AimUnit::GetEndPosition()
{
	return _aim_line->GetEndPosition();
}
