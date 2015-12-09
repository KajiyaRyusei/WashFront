//=============================================================================
//
// オブジェクトマネージャクラス [ObjectManager.cpp]
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
// コンストラクタ
//=========================================================================
ObjectManager::ObjectManager() : buildingListCursor_(0)
{
	// メンバ変数のクリア
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
// デストラクタ
//=========================================================================
ObjectManager::~ObjectManager()
{

	// 衝突判定マネージャの解放
	SafeDelete(collisionManager_);

	// フィールドの解放
	SafeDelete(field_);

	// プレイヤーの解放
	SafeDelete(player_);

	// ライトの解放
	for (int count = 0; count < LIGHT_NUM; ++count) {
		SafeDelete(light_[count]);
	}

	// 水の解放
	SafeDelete(water_);
	// 山の解放
	SafeDelete(mountain_);
	// 空の解放
	SafeDelete(sky_);


	// ビルの解放
	for (auto itr = buildingList_.begin(); itr != buildingList_.end(); itr++) {
		SafeDelete(*itr);
	}
	buildingList_.clear();


	SafeDelete(cursor_);

	// 全オブジェクトの解放
	Scene::ReleaseAll();

}

//=========================================================================
// 初期化処理
//=========================================================================
HRESULT ObjectManager::Init()
{
	// 衝突判定マネージャの生成
	collisionManager_ = new CollisionManager();
	collisionManager_->Init();

	// ライトの生成
	light_[0] = Light::Create(D3DXVECTOR3(0.2f, -0.9f, -0.2f));
	light_[1] = Light::Create(D3DXVECTOR3(-0.3f, -0.2f, 0.5f));


	// 水の生成
//	water_ = new Scene3D(PRIORITY_WATER);
//	water_->Init(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	// スカイドームの生成
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
// 更新処理
//=========================================================================
void ObjectManager::Update()
{
	Keyboard *key = Manager::GetInstance()->GetKeyboard();
	Mouse *mouse = Manager::GetInstance()->GetMouse();

#ifdef _DEBUG
	// 更新中断処理
	if (key->GetTriggerKey(DIK_F3)) {
		updateFlag_ = updateFlag_ ^ true;
	}
#endif




	// 更新処理
	{
#ifdef _DEBUG
		if (updateFlag_)
#endif
		{	// シーンインスタンスの更新処理
			Scene::UpdateAll();
		}
		
		
		CollisionMouseAndObject();


		// 衝突判定の更新
		collisionManager_->Update();
	}

}

//=========================================================================
// 描画処理
//=========================================================================
void ObjectManager::Draw()
{
	// 衝突判定領域の描画
	collisionManager_->Draw();
}


//=========================================================================
// ビルの生成
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
// インスタンスの全削除
//=========================================================================
void ObjectManager::AllDeleteBuilding()
{
	// ビルの解放
	for (auto itr = buildingList_.begin(); itr != buildingList_.end(); itr++) {
		SafeDelete(*itr);
	}
	buildingList_.clear();
}

//=========================================================================
// マウスとオブジェクトの衝突判定
//=========================================================================
void ObjectManager::CheckCollisionMouseAndObject()
{
	Camera *camera = Manager::GetInstance()->GetCameraManager()->GetCamera();

	// ウィンドウ情報取得
	HWND hWnd = GetWindowHandle();
	RECT rectWindow, rectClient;
	GetWindowRect(hWnd, &rectWindow);
	GetClientRect(hWnd, &rectClient);

	// マウスのスクリーン座標
	POINT screenPosition;
	GetCursorPos(&screenPosition);
	ScreenToClient(hWnd, &screenPosition);


	// マウスのレイ
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

	// 全オブジェクト探査
	for (auto itr = buildingList_.begin(); itr != buildingList_.end(); itr++) {
		D3DXVECTOR3 objectPosition = (*itr)->GetPosition();
		D3DXVECTOR3 vec = objectPosition - nearPosition;
		D3DXVECTOR3 cross;

		// レイと球の距離
		D3DXVec3Cross(&cross, &vec, &ray);
		float length = D3DXVec3Length(&cross);

		// 球との衝突判定
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

	// ウィンドウ情報取得
	HWND hWnd = GetWindowHandle();
	RECT rectWindow, rectClient;
	GetWindowRect(hWnd, &rectWindow);
	GetClientRect(hWnd, &rectClient);

	// マウスのスクリーン座標
	POINT screenPosition;
	GetCursorPos(&screenPosition);
	ScreenToClient(hWnd, &screenPosition);


	// マウスのレイ
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

	// 全オブジェクト探査
	for (auto itr = buildingList_.begin(); itr != buildingList_.end(); itr++) {
		D3DXVECTOR3 objectPosition = (*itr)->GetPosition();
		D3DXVECTOR3 vec = objectPosition - nearPosition;
		D3DXVECTOR3 cross;

		// レイと球の距離
		D3DXVec3Cross(&cross, &vec, &ray);
		float length = D3DXVec3Length(&cross);

		// 球との衝突判定
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
// 生成したオブジェクト情報を外部出力
//=========================================================================
void ObjectManager::SaveBuildingData(FILE *outputFile)
{
	int objNum = buildingList_.size();

	// オブジェクトの数出力
	fprintf(outputFile, "#OBJNUM\n");
	fprintf(outputFile, "%d\n", objNum);

	// オブジェクトの情報出力
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
// 生成するオブジェクト情報を外部入力
//=========================================================================
void ObjectManager::ReadBuildingData(FILE *inputFile)
{
	int num = 0;

	fseek(inputFile, 0, SEEK_SET);


	// 生成したオブジェクト数取得
	while (true) {
		char str[4096] = {};
		if (EOF == fscanf(inputFile, "%s", str))
			break;

		if (!strcmp(str, "#OBJNUM")) {
			fscanf(inputFile, "%d", &num);
		}
	}

	fseek(inputFile, 0, SEEK_SET);

	// インポートファイルパス読み込み
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