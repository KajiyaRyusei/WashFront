//=============================================================================
//
// 汚れの管理 [DirtManager.cpp]
// Author : KEITA OHUCHI
//
//=============================================================================

#include "Main.h"
#include "DirtManager.h"
#include "Manager.h"
#include "Renderer.h"
#include "../resource.h"
#include "Dirt.h"


//=========================================================================
// コンストラクタ
//=========================================================================
DirtManager::DirtManager() :
dirtListCursor_(0)
{
	dirtList_.clear();
}

//=========================================================================
// デストラクタ
//=========================================================================
DirtManager::~DirtManager()
{
	for (auto itr = dirtList_.begin(); itr != dirtList_.end(); itr++)
		delete (*itr);

	dirtList_.clear();
}

//=========================================================================
// 初期化処理
//=========================================================================
HRESULT DirtManager::Init()
{
	return S_OK;
}

//=========================================================================
// 更新処理
//=========================================================================
void DirtManager::Update()
{
}

//=========================================================================
// 描画処理
//=========================================================================
void DirtManager::Draw()
{
	int i = 0;
	bool flag = false;
	for (auto itr = dirtList_.begin(); itr != dirtList_.end(); itr++) {
		if (i == dirtListCursor_)
			flag = true;
		else
			flag = false;

		(*itr)->Draw(flag);
		i++;
	}
}


//=========================================================================
// データの出力
//=========================================================================
void DirtManager::OutputData(FILE *outputFile)
{

	int size = dirtList_.size();


	// 汚れの数出力
	fprintf(outputFile, "#NUM\n");
	fprintf(outputFile, "%d\n", size);


	// 汚れの情報出力
	fprintf(outputFile, "#DIRT\n");

	int i = 0;

	for (auto itr = dirtList_.begin(); itr != dirtList_.end(); itr++) {
		D3DXVECTOR3 position = (*itr)->GetPosition();
		float radius = (*itr)->GetRadius();
		int level = (*itr)->GetLevel();

		fprintf(outputFile, "%d ", i);
		fprintf(outputFile, "%f %f %f ", position.x, position.y, position.z);
		fprintf(outputFile, "%f ", radius);
		fprintf(outputFile, "%d", level);
		fprintf(outputFile, "\n");

		i++;
	}
	
}

//=========================================================================
// データの入力
//=========================================================================
void DirtManager::InputData(FILE *inputFile)
{
	
	int num = 0;

	fseek(inputFile, 0, SEEK_SET);


	// 生成したオブジェクト数取得
	while (true) {
		char str[4096] = {};
		if (EOF == fscanf(inputFile, "%s", str))
			break;

		if (!strcmp(str, "#NUM")) {
			fscanf(inputFile, "%d", &num);
		}
	}

	fseek(inputFile, 0, SEEK_SET);

	// インポートファイルパス読み込み
	while (true) {
		char str[4096] = {};
		if (EOF == fscanf(inputFile, "%s", str))
			break;

		if (!strcmp(str, "#DIRT")) {
			for (int i = 0; i < num; i++) {
				int ID;
				D3DXVECTOR3 position;
				float radius;
				int level;

				fscanf(inputFile, "%d %f %f %f %f %d",
					&ID,
					&position.x, &position.y, &position.z,
					&radius, &level
					);

				Dirt *d = new Dirt();
				d->SetPosition(position);
				d->SetRadius(radius);
				d->SetLevel(level);

				dirtList_.push_back(d);

				char str[4096] = {};
				sprintf(str, "%d", i + 1);

				HWND hCombo = GetDlgItem(GetDirtDialogHandle(), IDC_COMBO1);

				SendMessage(
					(HWND)hCombo,				// コンボボックスのハンドル
					(UINT)CB_ADDSTRING,			// 項目の追加
					0,							// ０固定
					(LPARAM)str					// 追加する項目の文字列
					);
			}
		}
	}
	
}

//=========================================================================
// 点の削除
//=========================================================================
void DirtManager::AllDeleteDirt()
{
	for (auto itr = dirtList_.begin(); itr != dirtList_.end(); itr++) {
		SafeDelete(*itr);
	}

	dirtList_.clear();
}

//=========================================================================
// 点の追加
//=========================================================================
void DirtManager::CreateDirt()
{
	Dirt *d = new Dirt();
	d->Init();

	dirtList_.push_back(d);


	int size = dirtList_.size();
	char str[4096] = {};
	sprintf(str, "%d", size);

	HWND hCombo = GetDlgItem(GetDirtDialogHandle(), IDC_COMBO1);

	SendMessage(
		(HWND)hCombo,				// コンボボックスのハンドル
		(UINT)CB_ADDSTRING,			// 項目の追加
		0,							// ０固定
		(LPARAM)str					// 追加する項目の文字列
		);

}


//=========================================================================
// 点の削除
//=========================================================================
void DirtManager::DeleteDirt()
{

	Dirt *d = nullptr;
	try {
		d = dirtList_.at(dirtListCursor_);
	}
	catch (const out_of_range& oor) {
		return;
	}

	int n = dirtList_.size() - 1;

	auto itr = dirtList_.begin();
	for (int i = 0; i < dirtListCursor_; i++)
		itr++;

	SafeDelete(d);
	dirtList_.erase(itr);


	HWND hCombo = GetDlgItem(GetDirtDialogHandle(), IDC_COMBO1);

	SendMessage(
		(HWND)hCombo,				// コンボボックスのハンドル
		(UINT)CB_DELETESTRING,		// 項目の追加
		(WPARAM)n,					// 削除する項目のインデックス
		(LPARAM)0
		);
}

//=========================================================================
// 座標の設定
//=========================================================================
void DirtManager::SetPositionX(float positionX)
{
	Dirt *d = nullptr;
	try {
		d = dirtList_.at(dirtListCursor_);
	}
	catch (const out_of_range& oor) {
		return;
	}
	d->SetPositionX(positionX);
}

void DirtManager::SetPositionY(float positionY)
{
	Dirt *d = nullptr;
	try {
		d = dirtList_.at(dirtListCursor_);
	}
	catch (const out_of_range& oor) {
		return;
	}
	d->SetPositionY(positionY);
}

void DirtManager::SetPositionZ(float positionZ)
{
	Dirt *d = nullptr;
	try {
		d = dirtList_.at(dirtListCursor_);
	}
	catch (const out_of_range& oor) {
		return;
	}
	d->SetPositionZ(positionZ);
}
void DirtManager::SetRadius(float radius)
{
	Dirt *d = nullptr;
	try {
		d = dirtList_.at(dirtListCursor_);
	}
	catch (const out_of_range& oor) {
		return;
	}
	d->SetRadius(radius);
}

void DirtManager::SetLevel(int level)
{
	Dirt *d = nullptr;
	try {
		d = dirtList_.at(dirtListCursor_);
	}
	catch (const out_of_range& oor) {
		return;
	}
	d->SetLevel(level);
}

//=========================================================================
// 座標の取得
//=========================================================================
D3DXVECTOR3 DirtManager::GetPosition()
{
	Dirt *d = nullptr;
	try {
		d = dirtList_.at(dirtListCursor_);
	}
	catch (const out_of_range& oor) {
		return D3DXVECTOR3(0, 0, 0);
	}

	return d->GetPosition();
}
//=========================================================================
// 半径の取得
//=========================================================================
float DirtManager::GetRadius()
{
	Dirt *d = nullptr;
	try {
		d = dirtList_.at(dirtListCursor_);
	}
	catch (const out_of_range& oor) {
		return 0.0f;
	}

	return d->GetRadius();
}


int DirtManager::GetLevel()
{
	Dirt *d = nullptr;
	try {
		d = dirtList_.at(dirtListCursor_);
	}
	catch (const out_of_range& oor) {
		return 0;
	}

	return d->GetLevel();
}


// End of file