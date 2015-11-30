//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// �V�[���}�l�[�W���[
//
// Created by Ryusei Kajiya on 20151006
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//*****************************************************************************
// �C���N���[�h
#include "scene_manager.h"
#include "scene_spawner.h"
#include "Scene/scene.h"
#include "Scene/scene_game.h"
#include "Scene/scene_title.h"

#include "Fade/fade.h"

//=============================================================================
// �R���X�g���N�^
SceneManager::SceneManager(Application *application, Fade* fade) :
	_scene_current{ nullptr },
	_scene_spawner_next{nullptr},
	_application{ application },
	_fade(fade)
{
	Initialize(application);
}

//=============================================================================
// ������
void SceneManager::Initialize(Application *application)
{
	SpawnerScene* spawner = new SpawnerForScene<SceneTitle>();
	_scene_current = spawner->Spawner(_application);
	ASSERT(_scene_current != nullptr,"�V�[������������Ă܂���");
	SafeDelete(spawner);

	UNREFERENCED_PARAMETER(application);
}
//=============================================================================
// �I��
void SceneManager::Finalize()
{
	SafeDelete(_scene_current);
	SafeDelete(_scene_spawner_next);
}
//=============================================================================
// �X�V
void SceneManager::Update()
{
	if( _scene_spawner_next != nullptr )
	{// ���̃V�[���̃t�@�N�g�������݂���Ȃ�

		if( _fade->IsFadeTop() == true )
		{
			SafeDelete(_scene_current);

			// �V�[���̐����Ə�����
			_scene_current = _scene_spawner_next->Spawner(_application);

			// �t�@�N�g���̍폜
			SafeDelete(_scene_spawner_next);
		}
	}

	if (_scene_current == nullptr)
	{// �V�[�������݂��Ȃ����
		OutputDebugStringA("�V�[�������݂��܂���\n");
		return;
	}

	_fade->Update();

	_scene_current->Update();
}

//=============================================================================
// �`��
void SceneManager::Draw()
{
	if (_scene_current == nullptr)
	{// �V�[�������݂��Ȃ����
		OutputDebugStringA("�V�[�������݂��܂���\n");
		return;
	}
	_scene_current->Draw();
}
//=============================================================================
// ���̃V�[�������蓖�Ă�
void SceneManager::SetNextScene(
	SpawnerScene *next_scene)
{
	if( _fade ->IsFadeNow() == false)
	{
		SafeDelete(_scene_spawner_next);
		_scene_spawner_next = next_scene;

		// fadeIn
		_fade->FadeIn();
	}
	else
	{
		SafeDelete(next_scene);
	}
	
}
