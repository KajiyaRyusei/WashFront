//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// �V�[���}�l�[�W���[
// 
// Created by Ryusei Kajiya on 20151006
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//*****************************************************************************
// ���d�C���N���[�h�h�~
#pragma once

//*****************************************************************************
// �O���錾
class Scene;
class SpawnerScene;
class Application;
class Fade;

//*****************************************************************************
// �N���X��`
class SceneManager
{
public:

	explicit SceneManager(Application* application,Fade* fade);

	virtual ~SceneManager(){ Finalize(); }

	// ������
	void Initialize(Application* application);

	// �I��
	void Finalize();

	// �X�V
	void Update();

	// �`��
	void Draw();

	// ���̃V�[�������蓖�Ă�
	void SetNextScene(
		SpawnerScene *next_scene);


private:

	// ���݂̃V�[��
	Scene* _scene_current;

	// ���̃V�[���̐���
	SpawnerScene* _scene_spawner_next;

	// �A�v���P�[�V����
	Application* _application;

	// �t�F�[�h
	Fade* _fade;
};