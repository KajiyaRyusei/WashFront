//=============================================================================
//
// ルートマネージャクラス [RouteManager.cpp]
// Author : KEITA OHUCHI
//
//=============================================================================

#include "Main.h"
#include "RouteManager.h"
#include "Manager.h"
#include "Renderer.h"
#include "../resource.h"
#include "SceneBillboard.h"


//=========================================================================
// コンストラクタ
//=========================================================================
RouteManager::RouteManager() :
point_(nullptr),
routeMode_(0)
{
	for (int i = 0; i < 4; i++) {
		pointList_[i].clear();
		pointListCursor_[i] = 0;
	}
}

//=========================================================================
// デストラクタ
//=========================================================================
RouteManager::~RouteManager()
{
	for (int i = 0; i < 4; i++) {
		for (auto itr = pointList_[i].begin(); itr != pointList_[i].end(); itr++)
			delete (*itr);

		pointList_[i].clear();
	}

	SafeDelete(point_);
}

//=========================================================================
// 初期化処理
//=========================================================================
HRESULT RouteManager::Init()
{
	point_ = new SceneBillboard();
	point_->Init(D3DXVECTOR2(1.0f, 1.0f), D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f));
	point_->SetTexture("./Resource/Texture/Game/texture000.png");
	point_->SetRenderFlag(false);

	return S_OK;
}

//=========================================================================
// 更新処理
//=========================================================================
void RouteManager::Update()
{
	RoutePoint *p = nullptr;
	try {
		p = pointList_[routeMode_].at(pointListCursor_[routeMode_]);
	}
	catch (const out_of_range& oor) {
		return;
	}

	if (p) {
		point_->SetPosition(p->position);
	}
}

//=========================================================================
// 描画処理
//=========================================================================
void RouteManager::Draw()
{

	D3DXCOLOR color[4] = {
		D3DXCOLOR(0, 1, 0, 1), D3DXCOLOR(1, 0, 0, 1), D3DXCOLOR(1, 1, 0, 1), D3DXCOLOR(1, 0, 1, 1)
	};

	for (int i = 0; i < 4; i++) {
		int size = pointList_[i].size();

		if (size) {
			VERTEX_3D *vertex = new VERTEX_3D[size + 1];

			for (int j = 0; j < size; j++) {
				vertex[j].diffuse = color[i];
				vertex[j].vtx = pointList_[i].at(j)->position;
			}
			vertex[size].vtx = pointList_[i].at(0)->position;


			LPDIRECT3DDEVICE9 device = Manager::GetInstance()->GetRenderer()->GetDevice();
			device->SetRenderState(D3DRS_LIGHTING, false);


			device->SetFVF(FVF_VERTEX_3D);		// 頂点フォーマットの設定

			// ワールドマトリックスの設定
			D3DXMATRIX worldMatrix;
			D3DXMatrixIdentity(&worldMatrix);
			device->SetTransform(D3DTS_WORLD, &worldMatrix);
			device->SetTexture(0, nullptr);
			device->DrawPrimitiveUP(D3DPT_LINESTRIP, size, vertex, sizeof(VERTEX_3D));


			device->SetRenderState(D3DRS_LIGHTING, true);


			delete[] vertex;


			if (GetMode() == MODE_ROUTE
				&& i == routeMode_)
				point_->Draw();
		}

	}
}


//=========================================================================
// データの出力
//=========================================================================
void RouteManager::OutputData(FILE *outputFile)
{
	
	for (int i = 0; i < 4; i++) {
		int size = pointList_[i].size();

		float len = 0.0f;
		auto itr = pointList_[i].begin();
		for (int j = 0; j < size - 1; j++) {
			D3DXVECTOR3 vec = (*itr)->position - (*(itr + 1))->position;
			len += D3DXVec3Length(&vec);
			itr++;
		}
		D3DXVECTOR3 vec = (*itr)->position - (*pointList_[i].begin())->position;
		len += D3DXVec3Length(&vec);



		// ポイントの数出力
		fprintf(outputFile, "#NUM\n");
		fprintf(outputFile, "%d\n", size);

		// ルートの全長出力
		fprintf(outputFile, "#LEN\n");
		fprintf(outputFile, "%f\n", len);


		// ポイントの情報出力
		fprintf(outputFile, "#POINT\n");

		int n = 0;

		for (auto itr = pointList_[i].begin(); itr != pointList_[i].end(); itr++) {
			D3DXVECTOR3 position = (*itr)->position;

			fprintf(outputFile, "%d ", n);
			fprintf(outputFile, "%f %f %f ", position.x, position.y, position.z);
			fprintf(outputFile, "\n");

			n++;
		}

		fprintf(outputFile, "\n");
	}
}

//=========================================================================
// データの入力
//=========================================================================
void RouteManager::InputData(FILE *inputFile)
{
	
	int num = 0;

	fseek(inputFile, 0, SEEK_SET);


	for (int i = 0; i < 4; i++) {
		// 生成したオブジェクト数取得
		while (true) {
			char str[4096] = {};
			if (EOF == fscanf(inputFile, "%s", str))
				break;

			if (!strcmp(str, "#NUM")) {
				fscanf(inputFile, "%d", &num);
				break;
			}
		}

		// インポートファイルパス読み込み
		while (true) {
			char str[4096] = {};
			if (EOF == fscanf(inputFile, "%s", str))
				break;

			if (!strcmp(str, "#POINT")) {
				for (int j = 0; j < num; j++) {
					int ID;
					D3DXVECTOR3 position;
					fscanf(inputFile, "%d %f %f %f",
						&ID,
						&position.x, &position.y, &position.z
						);

					RoutePoint *p = new RoutePoint();
					p->position = position;

					pointList_[i].push_back(p);

					char str[4096] = {};
					sprintf(str, "%d", j + 1);


					HWND hCombo = 0;
					if (i == 0)
						hCombo = GetDlgItem(GetRouteDialogHandle(), IDC_COMBO1);
					if (i == 1)
						hCombo = GetDlgItem(GetRouteDialogHandle(), IDC_COMBO3);
					if (i == 2)
						hCombo = GetDlgItem(GetRouteDialogHandle(), IDC_COMBO4);
					if (i == 3)
						hCombo = GetDlgItem(GetRouteDialogHandle(), IDC_COMBO2);

					SendMessage(
						(HWND)hCombo,				// コンボボックスのハンドル
						(UINT)CB_ADDSTRING,			// 項目の追加
						0,							// ０固定
						(LPARAM)str					// 追加する項目の文字列
						);
				}
				break;
			}
		}
	}
}

//=========================================================================
// 点の削除
//=========================================================================
void RouteManager::AllDeletePoint()
{
	for (int i = 0; i < 4; i++) {
		for (auto itr = pointList_[i].begin(); itr != pointList_[i].end(); itr++) {
			delete (*itr);
		}

		pointList_[i].clear();
	}
}

//=========================================================================
// 点の追加
//=========================================================================
void RouteManager::CreatePoint()
{
	RoutePoint *p = new RoutePoint();
	p->position = D3DXVECTOR3(0, 0, 0);

	pointList_[routeMode_].push_back(p);


	int size = pointList_[routeMode_].size();
	char str[4096] = {};
	sprintf(str, "%d", size);
	
	HWND hCombo = 0;
	if (routeMode_ == ROUTE_MODE_1P)
		hCombo = GetDlgItem(GetRouteDialogHandle(), IDC_COMBO1);
	if (routeMode_ == ROUTE_MODE_2P)
		hCombo = GetDlgItem(GetRouteDialogHandle(), IDC_COMBO3);
	if (routeMode_ == ROUTE_MODE_1P_CAMERA)
		hCombo = GetDlgItem(GetRouteDialogHandle(), IDC_COMBO4);
	if (routeMode_ == ROUTE_MODE_2P_CAMERA)
		hCombo = GetDlgItem(GetRouteDialogHandle(), IDC_COMBO2);


	SendMessage(
		(HWND)hCombo,				// コンボボックスのハンドル
		(UINT)CB_ADDSTRING,			// 項目の追加
		0,							// ０固定
		(LPARAM)str					// 追加する項目の文字列
		);

}
//=========================================================================
// 点の追加
//=========================================================================
void RouteManager::CreatePoint(D3DXVECTOR3 position)
{
	RoutePoint *p = new RoutePoint();
	p->position = position;

	pointList_[routeMode_].push_back(p);


	int size = pointList_[routeMode_].size();
	char str[4096] = {};
	sprintf(str, "%d", size);

	HWND hCombo = 0;
	if (routeMode_ == ROUTE_MODE_1P)
		hCombo = GetDlgItem(GetRouteDialogHandle(), IDC_COMBO1);
	if (routeMode_ == ROUTE_MODE_2P)
		hCombo = GetDlgItem(GetRouteDialogHandle(), IDC_COMBO3);
	if (routeMode_ == ROUTE_MODE_1P_CAMERA)
		hCombo = GetDlgItem(GetRouteDialogHandle(), IDC_COMBO4);
	if (routeMode_ == ROUTE_MODE_2P_CAMERA)
		hCombo = GetDlgItem(GetRouteDialogHandle(), IDC_COMBO2);

	SendMessage(
		(HWND)hCombo,				// コンボボックスのハンドル
		(UINT)CB_ADDSTRING,			// 項目の追加
		0,							// ０固定
		(LPARAM)str					// 追加する項目の文字列
		);

}

//=========================================================================
// 点の挿入
//=========================================================================
void RouteManager::InsertPoint()
{
	RoutePoint *p = new RoutePoint();
	p->position = D3DXVECTOR3(0, 0, 0);

	auto itr = pointList_[routeMode_].begin();
	for (int i = 0; i < pointListCursor_[routeMode_]; i++)
		itr++;

	pointList_[routeMode_].insert(itr, p);


	int size = pointList_[routeMode_].size();
	char str[4096] = {};
	sprintf(str, "%d", size);

	HWND hCombo = 0;
	if (routeMode_ == ROUTE_MODE_1P)
		hCombo = GetDlgItem(GetRouteDialogHandle(), IDC_COMBO1);
	if (routeMode_ == ROUTE_MODE_2P)
		hCombo = GetDlgItem(GetRouteDialogHandle(), IDC_COMBO3);
	if (routeMode_ == ROUTE_MODE_1P_CAMERA)
		hCombo = GetDlgItem(GetRouteDialogHandle(), IDC_COMBO4);
	if (routeMode_ == ROUTE_MODE_2P_CAMERA)
		hCombo = GetDlgItem(GetRouteDialogHandle(), IDC_COMBO2);

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
void RouteManager::DeletePoint()
{

	RoutePoint *p = nullptr;
	try {
		p = pointList_[routeMode_].at(pointListCursor_[routeMode_]);
	}
	catch (const out_of_range& oor) {
		return;
	}

	int n = pointList_[routeMode_].size() - 1;

	auto itr = pointList_[routeMode_].begin();
	for (int i = 0; i < pointListCursor_[routeMode_]; i++)
		itr++;

	delete p;
	pointList_[routeMode_].erase(itr);


	HWND hCombo = 0;
	if (routeMode_ == ROUTE_MODE_1P)
		hCombo = GetDlgItem(GetRouteDialogHandle(), IDC_COMBO1);
	if (routeMode_ == ROUTE_MODE_2P)
		hCombo = GetDlgItem(GetRouteDialogHandle(), IDC_COMBO3);
	if (routeMode_ == ROUTE_MODE_1P_CAMERA)
		hCombo = GetDlgItem(GetRouteDialogHandle(), IDC_COMBO4);
	if (routeMode_ == ROUTE_MODE_2P_CAMERA)
		hCombo = GetDlgItem(GetRouteDialogHandle(), IDC_COMBO2);

	SendMessage(
		(HWND)hCombo,				// コンボボックスのハンドル
		(UINT)CB_DELETESTRING,		// 項目の追加
		(WPARAM)n,					// 削除する項目のインデックス
		(LPARAM)0
		);
}

//=========================================================================
// 点の選択
//=========================================================================
void RouteManager::SelectPoint(int combo)
{
	HWND hCombo1 = GetDlgItem(GetRouteDialogHandle(), combo);
	int index = SendMessage(
		(HWND)hCombo1,			// コンボボックスのハンドル
		(UINT)CB_GETCURSEL,		// 選択中のインデックス取得
		0,						// ０固定
		0						// 追加する項目の文字列
		);

	// 選択中の点変更
	Manager::GetInstance()->GetRouteManager()->SetPointListCursor(index);


	D3DXVECTOR3 position = Manager::GetInstance()->GetRouteManager()->GetPosition();
	// 座標エディットボックス
	char str[4096] = {};
	sprintf(str, "%.3f", position.x);
	SetWindowText(
		(HWND)GetDlgItem(GetRouteDialogHandle(), IDC_EDIT2),		// スライダーのハンドル
		str		// 追加する項目の文字列
		);

	sprintf(str, "%.3f", position.y);
	SetWindowText(
		(HWND)GetDlgItem(GetRouteDialogHandle(), IDC_EDIT3),		// スライダーのハンドル
		str		// 追加する項目の文字列
		);

	sprintf(str, "%.3f", position.z);
	SetWindowText(
		(HWND)GetDlgItem(GetRouteDialogHandle(), IDC_EDIT4),		// スライダーのハンドル
		str		// 追加する項目の文字列
		);
}


//=========================================================================
// 座標の設定
//=========================================================================
void RouteManager::SetPositionX(float positionX)
{
	RoutePoint *p = nullptr;
	try {
		p = pointList_[routeMode_].at(pointListCursor_[routeMode_]);
	}
	catch (const out_of_range& oor) {
		return;
	}
	p->position.x = positionX;
}

void RouteManager::SetPositionY(float positionY)
{
	RoutePoint *p = nullptr;
	try {
		p = pointList_[routeMode_].at(pointListCursor_[routeMode_]);
	}
	catch (const out_of_range& oor) {
		return;
	}
	p->position.y = positionY;
}

void RouteManager::SetPositionZ(float positionZ)
{
	RoutePoint *p = nullptr;
	try {
		p = pointList_[routeMode_].at(pointListCursor_[routeMode_]);
	}
	catch (const out_of_range& oor) {
		return;
	}
	p->position.z = positionZ;
}


//=========================================================================
// 座標の取得
//=========================================================================
D3DXVECTOR3 RouteManager::GetPosition()
{
	RoutePoint *p = nullptr;
	try {
		p = pointList_[routeMode_].at(pointListCursor_[routeMode_]);
	}
	catch (const out_of_range& oor) {
		return D3DXVECTOR3(0, 0, 0);
	}

	return p->position;
}


// End of file