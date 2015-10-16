//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// 
// �J�����Ǘ�
// 
// Created by Ryusei Kajiya on 20151006
// 
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//*****************************************************************************
// �C���N���[�h
#include "camera_manager.h"

// �J�����ǂ�
#include "Camera/camera_game_main.h"
#include "Camera/camera_2d.h"

//=============================================================================
// ������
void CameraManager::Initialize()
{
	_cameras[CAMERA_TYPE_GAME_MAIN] = new CameraGameMain();
	_cameras[CAMERA_TYPE_2D] = new Camera2D();
}
//=============================================================================
// �I��
void CameraManager::Finalize()
{
	for( s32 i = 0; i < CAMERA_TYPE_MAX; ++i )
	{
		SafeDelete(_cameras[i]);
	}
}
//=============================================================================
// �X�V
void CameraManager::Update()
{
	for( s32 i = 0; i < CAMERA_TYPE_MAX; ++i )
	{
		_cameras[i]->CreateMatrix();
	}
}
