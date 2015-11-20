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
	water_ = new Scene3D(PRIORITY_WATER);
	water_->Init(D3DXVECTOR3(0.0f, -0.2f, 0.0f));

	// �X�J�C�h�[���̐���
	sky_ = MeshDome::Create(
		D3DXVECTOR3(0.0f, 0.0f, 0.0f), 50, 50, 100.0f);


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
Building *ObjectManager::CreateBuilding(const char *fileName)
{
	Building *building = new Building();
	building->Init(fileName);

	buildingList_.push_back(building);

	return building;
}
Building *ObjectManager::CreateBuilding(const char *fileName, D3DXVECTOR3 position, D3DXVECTOR3 rotation, D3DXVECTOR3 scale)
{
	Building *building = new Building();
	building->Init(fileName, position, rotation, scale);

	buildingList_.push_back(building);

	return building;
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
	RECT rect;
	GetWindowRect(hWnd, &rect);

	// �}�E�X�̃X�N���[�����W
	POINT screenPosition;
	GetCursorPos(&screenPosition);
	screenPosition.x -= rect.left;
	screenPosition.y -= rect.top;


	// �}�E�X�̃��C
	D3DXVECTOR3 nearPosition;
	D3DXVECTOR3 farPosition;
	D3DXVECTOR3 ray;
	nearPosition = camera->CalcScreenToWorld(D3DXVECTOR3((float)screenPosition.x, (float)screenPosition.y, 0.0f),
		D3DXVECTOR2(rect.right - rect.left, rect.bottom - rect.top));
	farPosition = camera->CalcScreenToWorld(D3DXVECTOR3((float)screenPosition.x, (float)screenPosition.y, 1.0f),
		D3DXVECTOR2(rect.right - rect.left, rect.bottom - rect.top));
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
				buildingListCursor_ = i;
				minDistance = distance;
			}
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
		char *filePath = (*itr)->GetFilePath();
		int fileID = ifm->GetFilePathID(filePath);

		fprintf(outputFile, "%d ", fileID);
		fprintf(outputFile, "%f %f %f ", position.x, position.y, position.z);
		fprintf(outputFile, "%f %f %f ", rotation.x, rotation.y, rotation.z);
		fprintf(outputFile, "%f %f %f", scale.x, scale.y, scale.z);
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
				int id;
				D3DXVECTOR3 position;
				D3DXVECTOR3 rotation;
				D3DXVECTOR3 scale;
				fscanf(inputFile, "%d %f %f %f %f %f %f %f %f %f", &id,
					&position.x, &position.y, &position.z,
					&rotation.x, &rotation.y, &rotation.z,
					&scale.x, &scale.y, &scale.z
					);

				CreateBuilding(Manager::GetInstance()->GetImportFileManager()->GetFilePath(id),
					position, rotation, scale);
			}
		}
	}

}


// End of file