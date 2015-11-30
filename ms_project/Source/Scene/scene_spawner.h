//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// �V�[������
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
class Application;

//*****************************************************************************
// �N���X�݌v
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