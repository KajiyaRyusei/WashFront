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
#include "Scene3D.h"
#include <commctrl.h>


//=========================================================================
// コンストラクタ
//=========================================================================
RouteManager::RouteManager() :
point_(nullptr),
cameraAllow_(nullptr),
playerAllow_(nullptr),
routeMode_(0)
{
	for (int i = 0; i < 2; i++) {
		pointList_[i].clear();
		pointListCursor_[i] = 0;
	}
}

//=========================================================================
// デストラクタ
//=========================================================================
RouteManager::~RouteManager()
{
	for (int i = 0; i < 2; i++) {
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

	cameraAllow_ = new Scene3D();
	cameraAllow_->Init(D3DXVECTOR3(0.f, 0.f, 0.f), D3DXVECTOR2(1.f, 2.f),
		"./Resource/Texture/Game/Allow001.png");
	cameraAllow_->SetRenderFlag(false);

	playerAllow_ = new Scene3D();
	playerAllow_->Init(D3DXVECTOR3(0.f, 0.f, 0.f), D3DXVECTOR2(1.f, 2.f),
		"./Resource/Texture/Game/Allow002.png");
	playerAllow_->SetRenderFlag(false);


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

	D3DXCOLOR color[2] = {
		D3DXCOLOR(0, 1, 0, 1), D3DXCOLOR(1, 0, 0, 1)
	};


	LPDIRECT3DDEVICE9 device = Manager::GetInstance()->GetRenderer()->GetDevice();
	device->SetRenderState(D3DRS_LIGHTING, false);


	for (int i = 0; i < 2; i++) {
		int size = pointList_[i].size();

		if (size) {
			VERTEX_3D *vertex = new VERTEX_3D[size + 1];

			for (int j = 0; j < size; j++) {
				vertex[j].diffuse = color[i];
				vertex[j].vtx = pointList_[i].at(j)->position;
			}
			vertex[size].vtx = pointList_[i].at(0)->position;

			// 描画
			device->SetFVF(FVF_VERTEX_3D);
			D3DXMATRIX worldMatrix;
			D3DXMatrixIdentity(&worldMatrix);
			device->SetTransform(D3DTS_WORLD, &worldMatrix);
			device->SetTexture(0, nullptr);
			device->DrawPrimitiveUP(D3DPT_LINESTRIP, size, vertex, sizeof(VERTEX_3D));
			delete[] vertex;


			if (GetMode() == MODE_ROUTE
				&& i == routeMode_)
				point_->Draw();
		}


		device->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
		
		// 矢印
		for (int j = 0; j < size; j++) {
			D3DXVECTOR3 v(0, 0, 1);
			D3DXVECTOR3 r = pointList_[i].at(j)->rotation;
			D3DXVECTOR3 d = pointList_[i].at(j)->playerDirection;
			D3DXVECTOR3 p = pointList_[i].at(j)->position;
			D3DXMATRIX m;
			D3DXMatrixIdentity(&m);
			D3DXMatrixRotationYawPitchRoll(&m, r.y, r.x, r.z);
			D3DXVec3TransformCoord(&v, &v, &m);
			cameraAllow_->SetRotation(r);
			cameraAllow_->SetPosition(p + v);
			cameraAllow_->Draw();

			v = D3DXVECTOR3(0, 0, 1);
			D3DXMatrixIdentity(&m);
			D3DXMatrixRotationYawPitchRoll(&m, d.y + r.y, d.x + r.x, d.z + r.z);
			D3DXVec3TransformCoord(&v, &v, &m);
			playerAllow_->SetRotation(r + d);
			playerAllow_->SetPosition(p + v);
			playerAllow_->Draw();
		}
		device->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	}

	device->SetRenderState(D3DRS_LIGHTING, true);

}


//=========================================================================
// データの出力
//=========================================================================
void RouteManager::OutputData(FILE *outputFile)
{
	
	for (int i = 0; i < 2; i++) {
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
			D3DXVECTOR3 rotation = (*itr)->rotation;
			D3DXVECTOR3 playerDirection = (*itr)->playerDirection;
			float speed = (*itr)->speed;
			int state = (*itr)->state;
			D3DXQUATERNION rotationQuaternion, directionQuaternion;
			D3DXMATRIX rotationMatrix, directionMatrix;
			D3DXMatrixIdentity(&rotationMatrix);
			D3DXMatrixRotationYawPitchRoll(&rotationMatrix, rotation.y, rotation.x, rotation.z);
			D3DXQuaternionRotationMatrix(&rotationQuaternion, &rotationMatrix);
			D3DXMatrixIdentity(&directionMatrix);
			D3DXMatrixRotationYawPitchRoll(&directionMatrix, rotation.y, rotation.x, rotation.z);
			D3DXQuaternionRotationMatrix(&directionQuaternion, &directionMatrix);


			fprintf(outputFile, "%d ", n);
			fprintf(outputFile, "%f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %d",
				position.x, position.y, position.z,
				rotation.x, rotation.y, rotation.z,
				rotationQuaternion.x, rotationQuaternion.y, rotationQuaternion.z, rotationQuaternion.w,
				playerDirection.x, playerDirection.y, playerDirection.z,
				directionQuaternion.x, directionQuaternion.y, directionQuaternion.z, directionQuaternion.w,
				speed, state);
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


	for (int i = 0; i < 2; i++) {
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
					D3DXVECTOR3 playerDirection;
					float speed;
					int state;
					D3DXQUATERNION q1, q2;
					D3DXVECTOR3 rotation;


					fscanf(inputFile, "%d %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %d",
						&ID,
						&position.x, &position.y, &position.z,
						&rotation.x, &rotation.y, &rotation.z,
						&q1.x, &q1.y, &q1.z, &q1.w,
						&playerDirection.x, &playerDirection.y, &playerDirection.z,
						&q2.x, &q2.y, &q2.z, &q2.w,
						&speed, &state);


					RoutePoint *p = new RoutePoint();
					p->position = position;
					p->rotation = rotation;
					p->playerDirection = playerDirection;
					p->speed = speed;
					p->state = state;

					pointList_[i].push_back(p);

					char str[4096] = {};
					sprintf(str, "%d", j + 1);


					HWND hCombo = 0;
					if (i == ROUTE_MODE_1P_CAMERA)
						hCombo = GetDlgItem(GetRouteDialogHandle(), IDC_COMBO4);
					if (i == ROUTE_MODE_2P_CAMERA)
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
	for (int i = 0; i < 2; i++) {
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
	p->rotation = D3DXVECTOR3(0, 0, 0);
	p->playerDirection = D3DXVECTOR3(0, 0, 0);
	p->speed = 0.f;
	p->state = 0;

	pointList_[routeMode_].push_back(p);


	int size = pointList_[routeMode_].size();
	char str[4096] = {};
	sprintf(str, "%d", size);
	
	HWND hCombo = 0;
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
	p->rotation = D3DXVECTOR3(0, 0, 0);
	p->playerDirection = D3DXVECTOR3(0, 0, 0);
	p->speed = 0.f;
	p->state = 0;

	pointList_[routeMode_].push_back(p);


	int size = pointList_[routeMode_].size();
	char str[4096] = {};
	sprintf(str, "%d", size);

	HWND hCombo = 0;
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
	p->rotation = D3DXVECTOR3(0, 0, 0);
	p->playerDirection = D3DXVECTOR3(0, 0, 0);
	p->speed = 0.f;
	p->state = 0;

	auto itr = pointList_[routeMode_].begin();
	for (int i = 0; i < pointListCursor_[routeMode_]; i++)
		itr++;

	pointList_[routeMode_].insert(itr, p);


	int size = pointList_[routeMode_].size();
	char str[4096] = {};
	sprintf(str, "%d", size);

	HWND hCombo = 0;
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


void RouteManager::InsertPoint(D3DXVECTOR3 position)
{
	RoutePoint *p = new RoutePoint();
	p->position = position;
	p->rotation = D3DXVECTOR3(0, 0, 0);
	p->playerDirection = D3DXVECTOR3(0, 0, 0);
	p->speed = 0.f;
	p->state = 0;

	auto itr = pointList_[routeMode_].begin();
	for (int i = 0; i < pointListCursor_[routeMode_]; i++)
		itr++;

	pointList_[routeMode_].insert(itr, p);


	int size = pointList_[routeMode_].size();
	char str[4096] = {};
	sprintf(str, "%d", size);

	HWND hCombo = 0;
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


	D3DXVECTOR3 position = GetPosition();
	D3DXVECTOR3 rotation = GetRotation();
	D3DXVECTOR3 playerDirection = GetPlayerDirection();
	float speed = GetSpeed();
	int state = GetState();


	// 座標エディットボックス
	char str[4096] = {};
	sprintf(str, "%.3f", position.x);
	SetWindowText((HWND)GetDlgItem(GetRouteDialogHandle(), IDC_EDIT2), str);

	sprintf(str, "%.3f", position.y);
	SetWindowText((HWND)GetDlgItem(GetRouteDialogHandle(), IDC_EDIT3), str);

	sprintf(str, "%.3f", position.z);
	SetWindowText((HWND)GetDlgItem(GetRouteDialogHandle(), IDC_EDIT4), str);

	sprintf(str, "%.3f", speed);
	SetWindowText((HWND)GetDlgItem(GetRouteDialogHandle(), IDC_EDIT11), str);

	SendMessage(
		(HWND)GetDlgItem(GetRouteDialogHandle(), IDC_SLIDER1),
		(UINT)TBM_SETPOS,
		(WPARAM)TRUE,
		(LPARAM)((rotation.x + D3DX_PI) / (D3DX_PI * 2) * 100));
	SendMessage(
		(HWND)GetDlgItem(GetRouteDialogHandle(), IDC_SLIDER2),
		(UINT)TBM_SETPOS,
		(WPARAM)TRUE,
		(LPARAM)((rotation.y + D3DX_PI) / (D3DX_PI * 2) * 100));
	SendMessage(
		(HWND)GetDlgItem(GetRouteDialogHandle(), IDC_SLIDER3),
		(UINT)TBM_SETPOS,
		(WPARAM)TRUE,
		(LPARAM)((rotation.z + D3DX_PI) / (D3DX_PI * 2) * 100));

	SendMessage(
		(HWND)GetDlgItem(GetRouteDialogHandle(), IDC_SLIDER4),
		(UINT)TBM_SETPOS,
		(WPARAM)TRUE,
		(LPARAM)((playerDirection.x + D3DX_PI) / (D3DX_PI * 2) * 100));
	SendMessage(
		(HWND)GetDlgItem(GetRouteDialogHandle(), IDC_SLIDER8),
		(UINT)TBM_SETPOS,
		(WPARAM)TRUE,
		(LPARAM)((playerDirection.y + D3DX_PI) / (D3DX_PI * 2) * 100));
	SendMessage(
		(HWND)GetDlgItem(GetRouteDialogHandle(), IDC_SLIDER9),
		(UINT)TBM_SETPOS,
		(WPARAM)TRUE,
		(LPARAM)((playerDirection.z + D3DX_PI) / (D3DX_PI * 2) * 100));


	SendMessage(
		(HWND)GetDlgItem(GetRouteDialogHandle(), IDC_COMBO1),
		(UINT)CB_SETCURSEL,
		(WPARAM)state,
		0);

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

void RouteManager::SetRotationX(float rotationX)
{
	RoutePoint *p = nullptr;
	try {
		p = pointList_[routeMode_].at(pointListCursor_[routeMode_]);
	}
	catch (const out_of_range& oor) {
		return;
	}
	p->rotation.x = rotationX;
}
void RouteManager::SetRotationY(float rotationY)
{
	RoutePoint *p = nullptr;
	try {
		p = pointList_[routeMode_].at(pointListCursor_[routeMode_]);
	}
	catch (const out_of_range& oor) {
		return;
	}
	p->rotation.y = rotationY;
}
void RouteManager::SetRotationZ(float rotationZ)
{
	RoutePoint *p = nullptr;
	try {
		p = pointList_[routeMode_].at(pointListCursor_[routeMode_]);
	}
	catch (const out_of_range& oor) {
		return;
	}
	p->rotation.z = rotationZ;
}

void RouteManager::SetPlayerDirectionX(float playerDirectionX)
{
	RoutePoint *p = nullptr;
	try {
		p = pointList_[routeMode_].at(pointListCursor_[routeMode_]);
	}
	catch (const out_of_range& oor) {
		return;
	}
	p->playerDirection.x = playerDirectionX;
}
void RouteManager::SetPlayerDirectionY(float playerDirectionY)
{
	RoutePoint *p = nullptr;
	try {
		p = pointList_[routeMode_].at(pointListCursor_[routeMode_]);
	}
	catch (const out_of_range& oor) {
		return;
	}
	p->playerDirection.y = playerDirectionY;
}
void RouteManager::SetPlayerDirectionZ(float playerDirectionZ)
{
	RoutePoint *p = nullptr;
	try {
		p = pointList_[routeMode_].at(pointListCursor_[routeMode_]);
	}
	catch (const out_of_range& oor) {
		return;
	}
	p->playerDirection.z = playerDirectionZ;
}

void RouteManager::SetSpeed(float speed)
{
	RoutePoint *p = nullptr;
	try {
		p = pointList_[routeMode_].at(pointListCursor_[routeMode_]);
	}
	catch (const out_of_range& oor) {
		return;
	}
	p->speed = speed;
}
void RouteManager::SetState(int state)
{
	RoutePoint *p = nullptr;
	try {
		p = pointList_[routeMode_].at(pointListCursor_[routeMode_]);
	}
	catch (const out_of_range& oor) {
		return;
	}
	p->state = state;
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
D3DXVECTOR3 RouteManager::GetRotation()
{
	RoutePoint *p = nullptr;
	try {
		p = pointList_[routeMode_].at(pointListCursor_[routeMode_]);
	}
	catch (const out_of_range& oor) {
		return D3DXVECTOR3(0, 0, 0);
	}

	return p->rotation;
}
D3DXVECTOR3 RouteManager::GetPlayerDirection()
{
	RoutePoint *p = nullptr;
	try {
		p = pointList_[routeMode_].at(pointListCursor_[routeMode_]);
	}
	catch (const out_of_range& oor) {
		return D3DXVECTOR3(0, 0, 0);
	}

	return p->playerDirection;
}
float RouteManager::GetSpeed()
{
	RoutePoint *p = nullptr;
	try {
		p = pointList_[routeMode_].at(pointListCursor_[routeMode_]);
	}
	catch (const out_of_range& oor) {
		return 0.f;
	}

	return p->speed;
}
int RouteManager::GetState()
{
	RoutePoint *p = nullptr;
	try {
		p = pointList_[routeMode_].at(pointListCursor_[routeMode_]);
	}
	catch (const out_of_range& oor) {
		return 0.f;
	}

	return p->state;
}



RoutePoint *RouteManager::GetRoutePoint(int index, int cursor)
{
	RoutePoint *p = nullptr;

	if (0 <= index && index <= 1) {
		int size = pointList_[index].size();
		p = pointList_[index].at(cursor % size);
	}

	return p;
}


// End of file