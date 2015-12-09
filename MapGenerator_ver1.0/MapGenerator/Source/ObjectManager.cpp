//=============================================================================
//
// �I�u�W�F�N�g�}�l�[�W���N���X [ObjectManager.cpp]
// Author : KEITA OHUCHI
//
//=============================================================================

#include "ObjectManager.h"
#include "Manager.h"
#include "Keyboard.h"
#include "Mouse.h"
#include "Camera.h"
#include "Light.h"
#include "MeshField.h"
#include "MeshDome.h"
#include "MeshCylinder.h"
#include "Player.h"
#include "Debug.h"
#include "CollisionManager.h"
#include "Building.h"
#include "CameraManager.h"
#include "ImportFileManager.h"
#include "Cursor.h"


//=========================================================================
// �R���X�g���N�^
//=========================================================================
ObjectManager::ObjectManager() : buildingListCursor_(0)
{
	// �����o�ϐ��̃N���A
	field_ = nullptr;
	player_ = nullptr;
	memset(light_, 0, sizeof(Light *) * LIGHT_NUM);
	water_ = nullptr;
	mountain_ = nullptr;
	sky_ = nullptr;
	collisionManager_ = nullptr;
	buildingList_.clear();
	cursor_ = nullptr;


#ifdef _DEBUG
	updateFlag_ = true;
#endif

}

//=========================================================================
// �f�X�g���N�^
//=========================================================================
ObjectManager::~ObjectManager()
{

	// �Փ˔���}�l�[�W���̉��
	SafeDelete(collisionManager_);

	// �t�B�[���h�̉��
	SafeDelete(field_);

	// �v���C���[�̉��
	SafeDelete(player_);

	// ���C�g�̉��
	for (int count = 0; count < LIGHT_NUM; ++count) {
		SafeDelete(light_[count]);
	}

	// ���̉��
	SafeDelete(water_);
	// �R�̉��
	SafeDelete(mountain_);
	// ��̉��
	SafeDelete(sky_);


	// �r���̉��
	for (auto itr = buildingList_.begin(); itr != buildingList_.end(); itr++) {
		SafeDelete(*itr);
	}
	buildingList_.clear();


	SafeDelete(cursor_);

	// �S�I�u�W�F�N�g�̉��
	Scene::ReleaseAll();

}

//=========================================================================
// ����������
//=========================================================================
HRESULT ObjectManager::Init()
{
	// �Փ˔���}�l�[�W���̐���
	collisionManager_ = new CollisionManager();
	collisionManager_->Init();

	// ���C�g�̐���
	light_[0] = Light::Create(D3DXVECTOR3(0.2f, -0.9f, -0.2f));
	light_[1] = Light::Create(D3DXVECTOR3(-0.3f, -0.2f, 0.5f));


	// ���̐���
//	water_ = new Scene3D(PRIORITY_WATER);
//	water_->Init(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	// �X�J�C�h�[���̐���
	//sky_ = MeshDome::Create(
	//	D3DXVECTOR3(0.0f, 0.0f, 0.0f), 50, 50, 100.0f);

	field_ = MeshField::Create(
		1, 1, 500.f, 500.f,
		D3DXVECTOR3(250.f, 0.f, 250.f), D3DXVECTOR3(0.f, 0.f, 0.f));
	field_->SetTexture("./Resource/Texture/Game/Grid.png");

	cursor_ = new Cursor();
	cursor_->Init();


	return S_OK;
}

//=========================================================================
// �X�V����
//=========================================================================
void ObjectManager::Update()
{
	Keyboard *key = Manager::GetInstance()->GetKeyboard();
	Mouse *mouse = Manager::GetInstance()->GetMouse();

#ifdef _DEBUG
	// �X�V���f����
	if (key->GetTriggerKey(DIK_F3)) {
		updateFlag_ = updateFlag_ ^ true;
	}
#endif




	// �X�V����
	{
#ifdef _DEBUG
		if (updateFlag_)
#endif
		{	// �V�[���C���X�^���X�̍X�V����
			Scene::UpdateAll();
		}
		
		
		CollisionMouseAndObject();


		// �Փ˔���̍X�V
		collisionManager_->Update();
	}

}

//=========================================================================
// �`�揈��
//=========================================================================
void ObjectManager::Draw()
{
	// �Փ˔���̈�̕`��
	collisionManager_->Draw();
}


//=========================================================================
// �r���̐���
//=========================================================================
Building *ObjectManager::CreateBuilding(const char *fileName, const char *textureFilePath)
{
	Building *building = new Building();
	building->Init(fileName, textureFilePath);

	buildingList_.push_back(building);

	return building;
}
Building *ObjectManager::CreateBuilding(const char *fileName, const char *textureFilePath,
	D3DXVECTOR3 position, D3DXVECTOR3 rotation, D3DXVECTOR3 scale, bool collision)
{
	Building *building = new Building();
	building->Init(fileName, textureFilePath, position, rotation, scale, collision);

	buildingList_.push_back(building);

	return building;
}


Building *ObjectManager::CopyBuilding()
{
	Building *b = nullptr;
	try {
		b = buildingList_.at(buildingListCursor_);
	}
	catch (const out_of_range& oor) {
		return nullptr;
	}

	const char *modelPath = b->GetModelFilePath();
	const char *texturePath = b->GetTextureFilePath();
	D3DXVECTOR3 position = b->GetPosition();
	D3DXVECTOR3 rotation = b->GetRotation();
	D3DXVECTOR3 scale = b->GetScale();
	bool collision = b->GetCollision();


	return CreateBuilding(modelPath, texturePath, position, rotation, scale, collision);
}


Building *ObjectManager::GetSelectBuilding()
{
	Building *building = nullptr;
	try {
		building = buildingList_.at(buildingListCursor_);
	} catch (const out_of_range& oor) {
		building = nullptr;
	}

	return building;
}

//=========================================================================
// �C���X�^���X�̑S�폜
//=========================================================================
void ObjectManager::AllDeleteBuilding()
{
	// �r���̉��
	for (auto itr = buildingList_.begin(); itr != buildingList_.end(); itr++) {
		SafeDelete(*itr);
	}
	buildingList_.clear();
}

//=========================================================================
// �}�E�X�ƃI�u�W�F�N�g�̏Փ˔���
//=========================================================================
void ObjectManager::CheckCollisionMouseAndObject()
{
	Camera *camera = Manager::GetInstance()->GetCameraManager()->GetCamera();

	// �E�B���h�E���擾
	HWND hWnd = GetWindowHandle();
	RECT rectWindow, rectClient;
	GetWindowRect(hWnd, &rectWindow);
	GetClientRect(hWnd, &rectClient);

	// �}�E�X�̃X�N���[�����W
	POINT screenPosition;
	GetCursorPos(&screenPosition);
	ScreenToClient(hWnd, &screenPosition);


	// �}�E�X�̃��C
	D3DXVECTOR3 nearPosition;
	D3DXVECTOR3 farPosition;
	D3DXVECTOR3 ray;
	nearPosition = camera->CalcScreenToWorld(D3DXVECTOR3((float)screenPosition.x, (float)screenPosition.y, 0.0f),
		D3DXVECTOR2((float)rectClient.right, (float)rectClient.bottom));
	farPosition = camera->CalcScreenToWorld(D3DXVECTOR3((float)screenPosition.x, (float)screenPosition.y, 1.0f),
		D3DXVECTOR2((float)rectClient.right, (float)rectClient.bottom));
	ray = farPosition - nearPosition;
	D3DXVec3Normalize(&ray, &ray);

	int i = 0;
	float minDistance = 10000;

	// �S�I�u�W�F�N�g�T��
	for (auto itr = buildingList_.begin(); itr != buildingList_.end(); itr++) {
		D3DXVECTOR3 objectPosition = (*itr)->GetPosition();
		D3DXVECTOR3 vec = objectPosition - nearPosition;
		D3DXVECTOR3 cross;

		// ���C�Ƌ��̋���
		D3DXVec3Cross(&cross, &vec, &ray);
		float length = D3DXVec3Length(&cross);

		// ���Ƃ̏Փ˔���
		if (length < BUILDING_RADIUS) {
			float distance = D3DXVec3Dot(&vec, &ray);
			if (distance < minDistance) {
				//buildingList_.at(buildingListCursor_)->SetState(SELECT_NONE);
				buildingListCursor_ = i;
				//buildingList_.at(buildingListCursor_)->SetState(SELECT_SELECT);
				minDistance = distance;
			}
		} else {
			//buildingList_.at(buildingListCursor_)->SetState(SELECT_NONE);
		}

		i++;
	}

}
void ObjectManager::CollisionMouseAndObject()
{
	Camera *camera = Manager::GetInstance()->GetCameraManager()->GetCamera();

	// �E�B���h�E���擾
	HWND hWnd = GetWindowHandle();
	RECT rectWindow, rectClient;
	GetWindowRect(hWnd, &rectWindow);
	GetClientRect(hWnd, &rectClient);

	// �}�E�X�̃X�N���[�����W
	POINT screenPosition;
	GetCursorPos(&screenPosition);
	ScreenToClient(hWnd, &screenPosition);


	// �}�E�X�̃��C
	D3DXVECTOR3 nearPosition;
	D3DXVECTOR3 farPosition;
	D3DXVECTOR3 ray;
	nearPosition = camera->CalcScreenToWorld(D3DXVECTOR3((float)screenPosition.x, (float)screenPosition.y, 0.0f),
		D3DXVECTOR2((float)rectClient.right, (float)rectClient.bottom));
	farPosition = camera->CalcScreenToWorld(D3DXVECTOR3((float)screenPosition.x, (float)screenPosition.y, 1.0f),
		D3DXVECTOR2((float)rectClient.right, (float)rectClient.bottom));
	ray = farPosition - nearPosition;
	D3DXVec3Normalize(&ray, &ray);

	int i = 0;
	float minDistance = 10000;

	// �S�I�u�W�F�N�g�T��
	for (auto itr = buildingList_.begin(); itr != buildingList_.end(); itr++) {
		D3DXVECTOR3 objectPosition = (*itr)->GetPosition();
		D3DXVECTOR3 vec = objectPosition - nearPosition;
		D3DXVECTOR3 cross;

		// ���C�Ƌ��̋���
		D3DXVec3Cross(&cross, &vec, &ray);
		float length = D3DXVec3Length(&cross);

		// ���Ƃ̏Փ˔���
		if (length < BUILDING_RADIUS) {
			float distance = D3DXVec3Dot(&vec, &ray);
			if (distance < minDistance) {
				if (buildingList_.at(i)->GetState() != SELECT_SELECT)
					buildingList_.at(i)->SetState(SELECT_HIT);
				minDistance = distance;
			}
		} else {
			if (buildingList_.at(i)->GetState() != SELECT_SELECT)
				buildingList_.at(i)->SetState(SELECT_NONE);
		}

		i++;
	}
}


//=========================================================================
// ���������I�u�W�F�N�g�����O���o��
//=========================================================================
void ObjectManager::SaveBuildingData(FILE *outputFile)
{
	int objNum = buildingList_.size();

	// �I�u�W�F�N�g�̐��o��
	fprintf(outputFile, "#OBJNUM\n");
	fprintf(outputFile, "%d\n", objNum);

	// �I�u�W�F�N�g�̏��o��
	fprintf(outputFile, "#OBJ\n");

	int i = 0;
	ImportFileManager *ifm = Manager::GetInstance()->GetImportFileManager();

	for (auto itr = buildingList_.begin(); itr != buildingList_.end(); itr++) {
		D3DXVECTOR3 position = (*itr)->GetPosition();
		D3DXVECTOR3 rotation = (*itr)->GetRotation();
		D3DXVECTOR3 scale = (*itr)->GetScale();
		char *modelFilePath = (*itr)->GetModelFilePath();
		char *textureFilePath = (*itr)->GetTextureFilePath();
		int modelFileID = ifm->GetModelFilePathID(modelFilePath);
		int textureFileID = ifm->GetTextureFilePathID(textureFilePath);
		bool collision = (*itr)->GetCollision();

		fprintf(outputFile, "%d ", modelFileID);
		fprintf(outputFile, "%d ", textureFileID);
		fprintf(outputFile, "%f %f %f ", position.x, position.y, position.z);
		fprintf(outputFile, "%f %f %f ", rotation.x, rotation.y, rotation.z);
		fprintf(outputFile, "%f %f %f ", scale.x, scale.y, scale.z);
		fprintf(outputFile, "%d", collision);
		fprintf(outputFile, "\n");

		i++;
	}
}

//=========================================================================
// ��������I�u�W�F�N�g�����O������
//=========================================================================
void ObjectManager::ReadBuildingData(FILE *inputFile)
{
	int num = 0;

	fseek(inputFile, 0, SEEK_SET);


	// ���������I�u�W�F�N�g���擾
	while (true) {
		char str[4096] = {};
		if (EOF == fscanf(inputFile, "%s", str))
			break;

		if (!strcmp(str, "#OBJNUM")) {
			fscanf(inputFile, "%d", &num);
		}
	}

	fseek(inputFile, 0, SEEK_SET);

	// �C���|�[�g�t�@�C���p�X�ǂݍ���
	while (true) {
		char str[4096] = {};
		if (EOF == fscanf(inputFile, "%s", str))
			break;

		if (!strcmp(str, "#OBJ")) {
			for (int i = 0; i < num; i++) {
				int modelID;
				int textureID;
				D3DXVECTOR3 position;
				D3DXVECTOR3 rotation;
				D3DXVECTOR3 scale;
				int collision;
				fscanf(inputFile, "%d %d %f %f %f %f %f %f %f %f %f %d",
					&modelID, &textureID,
					&position.x, &position.y, &position.z,
					&rotation.x, &rotation.y, &rotation.z,
					&scale.x, &scale.y, &scale.z,
					&collision
					);

				CreateBuilding(
					Manager::GetInstance()->GetImportFileManager()->GetModelFilePath(modelID),
					Manager::GetInstance()->GetImportFileManager()->GetTextureFilePath(textureID),
					position, rotation, scale, (bool)collision);
			}
		}
	}

}


// End of file