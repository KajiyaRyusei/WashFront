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
	water_ = new Scene3D(PRIORITY_WATER);
	water_->Init(D3DXVECTOR3(0.0f, -0.2f, 0.0f));

	// スカイドームの生成
	sky_ = MeshDome::Create(
		D3DXVECTOR3(0.0f, 0.0f, 0.0f), 50, 50, 100.0f);


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
	RECT rect;
	GetWindowRect(hWnd, &rect);

	// マウスのスクリーン座標
	POINT screenPosition;
	GetCursorPos(&screenPosition);
	screenPosition.x -= rect.left;
	screenPosition.y -= rect.top;


	// マウスのレイ
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
				buildingListCursor_ = i;
				minDistance = distance;
			}
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