//=============================================================================
//
// ���[�g�}�l�[�W���N���X [RouteManager.cpp]
// Author : KEITA OHUCHI
//
//=============================================================================

#include "Main.h"
#include "RouteManager.h"
#include "Manager.h"
#include "Renderer.h"
#include "../resource.h"


//=========================================================================
// �R���X�g���N�^
//=========================================================================
RouteManager::RouteManager() :
pointListCursor_(0)
{
	pointList_.clear();
}

//=========================================================================
// �f�X�g���N�^
//=========================================================================
RouteManager::~RouteManager()
{
	for (auto itr = pointList_.begin(); itr != pointList_.end(); itr++)
		delete (*itr);

	pointList_.clear();
}

//=========================================================================
// ����������
//=========================================================================
HRESULT RouteManager::Init()
{
	return S_OK;
}

//=========================================================================
// �X�V����
//=========================================================================
void RouteManager::Update()
{
}

//=========================================================================
// �`�揈��
//=========================================================================
void RouteManager::Draw()
{
	int size = pointList_.size();

	if (size) {
		VERTEX_3D *vertex = new VERTEX_3D[size + 1];

		for (int i = 0; i < size; i++) {
			vertex[i].diffuse = D3DXCOLOR(0, 1, 0, 1);
			vertex[i].vtx = pointList_.at(i)->position;
		}
		vertex[size].vtx = pointList_.at(0)->position;


		LPDIRECT3DDEVICE9 device = Manager::GetInstance()->GetRenderer()->GetDevice();
		device->SetRenderState(D3DRS_LIGHTING, false);


		device->SetFVF(FVF_VERTEX_3D);		// ���_�t�H�[�}�b�g�̐ݒ�

		// ���[���h�}�g���b�N�X�̐ݒ�
		D3DXMATRIX worldMatrix;
		D3DXMatrixIdentity(&worldMatrix);
		device->SetTransform(D3DTS_WORLD, &worldMatrix);
		device->SetTexture(0, nullptr);
		device->DrawPrimitiveUP(D3DPT_LINESTRIP, size, vertex, sizeof(VERTEX_3D));


		device->SetRenderState(D3DRS_LIGHTING, true);


		delete[] vertex;
	}
}


//=========================================================================
// �f�[�^�̏o��
//=========================================================================
void RouteManager::OutputData(FILE *outputFile)
{
	int size = pointList_.size();

	float len = 0.0f;
	auto itr = pointList_.begin();
	for (int i = 0; i < size - 1; i++) {
		D3DXVECTOR3 vec = (*itr)->position - (*(itr + 1))->position;
		len += D3DXVec3Length(&vec);
		itr++;
	}
	D3DXVECTOR3 vec = (*itr)->position - (*pointList_.begin())->position;
	len += D3DXVec3Length(&vec);



	// �|�C���g�̐��o��
	fprintf(outputFile, "#NUM\n");
	fprintf(outputFile, "%d\n", size);

	// ���[�g�̑S���o��
	fprintf(outputFile, "#LEN\n");
	fprintf(outputFile, "%f\n", len);


	// �|�C���g�̏��o��
	fprintf(outputFile, "#POINT\n");

	int i = 0;

	for (auto itr = pointList_.begin(); itr != pointList_.end(); itr++) {
		D3DXVECTOR3 position = (*itr)->position;

		fprintf(outputFile, "%d ", i);
		fprintf(outputFile, "%f %f %f ", position.x, position.y, position.z);
		fprintf(outputFile, "\n");

		i++;
	}

}

//=========================================================================
// �f�[�^�̓���
//=========================================================================
void RouteManager::InputData(FILE *inputFile)
{
	int num = 0;

	fseek(inputFile, 0, SEEK_SET);


	// ���������I�u�W�F�N�g���擾
	while (true) {
		char str[4096] = {};
		if (EOF == fscanf(inputFile, "%s", str))
			break;

		if (!strcmp(str, "#NUM")) {
			fscanf(inputFile, "%d", &num);
		}
	}

	fseek(inputFile, 0, SEEK_SET);

	// �C���|�[�g�t�@�C���p�X�ǂݍ���
	while (true) {
		char str[4096] = {};
		if (EOF == fscanf(inputFile, "%s", str))
			break;

		if (!strcmp(str, "#POINT")) {
			for (int i = 0; i < num; i++) {
				int ID;
				D3DXVECTOR3 position;
				fscanf(inputFile, "%d %f %f %f",
					&ID,
					&position.x, &position.y, &position.z
					);

				RoutePoint *p = new RoutePoint();
				p->position = position;

				pointList_.push_back(p);

				char str[4096] = {};
				sprintf(str, "%d", i + 1);

				HWND hCombo = GetDlgItem(GetRouteDialogHandle(), IDC_COMBO1);

				SendMessage(
					(HWND)hCombo,				// �R���{�{�b�N�X�̃n���h��
					(UINT)CB_ADDSTRING,			// ���ڂ̒ǉ�
					0,							// �O�Œ�
					(LPARAM)str					// �ǉ����鍀�ڂ̕�����
					);
			}
		}
	}

}

//=========================================================================
// �_�̍폜
//=========================================================================
void RouteManager::AllDeletePoint()
{
	for (auto itr = pointList_.begin(); itr != pointList_.end(); itr++) {
		delete (*itr);
	}

	pointList_.clear();
}

//=========================================================================
// �_�̒ǉ�
//=========================================================================
void RouteManager::CreatePoint()
{
	RoutePoint *p = new RoutePoint();
	p->position = D3DXVECTOR3(0, 0, 0);

	pointList_.push_back(p);


	int size = pointList_.size();
	char str[4096] = {};
	sprintf(str, "%d", size);

	HWND hCombo = GetDlgItem(GetRouteDialogHandle(), IDC_COMBO1);

	SendMessage(
		(HWND)hCombo,				// �R���{�{�b�N�X�̃n���h��
		(UINT)CB_ADDSTRING,			// ���ڂ̒ǉ�
		0,							// �O�Œ�
		(LPARAM)str					// �ǉ����鍀�ڂ̕�����
		);

}

//=========================================================================
// �_�̑}��
//=========================================================================
void RouteManager::InsertPoint()
{
	RoutePoint *p = new RoutePoint();
	p->position = D3DXVECTOR3(0, 0, 0);

	auto itr = pointList_.begin();
	for (int i = 0; i < pointListCursor_; i++)
		itr++;

	pointList_.insert(itr, p);


	int size = pointList_.size();
	char str[4096] = {};
	sprintf(str, "%d", size);

	HWND hCombo = GetDlgItem(GetRouteDialogHandle(), IDC_COMBO1);

	SendMessage(
		(HWND)hCombo,				// �R���{�{�b�N�X�̃n���h��
		(UINT)CB_ADDSTRING,			// ���ڂ̒ǉ�
		0,							// �O�Œ�
		(LPARAM)str					// �ǉ����鍀�ڂ̕�����
		);

}

//=========================================================================
// �_�̍폜
//=========================================================================
void RouteManager::DeletePoint()
{

	RoutePoint *p = nullptr;
	try {
		p = pointList_.at(pointListCursor_);
	}
	catch (const out_of_range& oor) {
		return;
	}

	int n = pointList_.size() - 1;

	auto itr = pointList_.begin();
	for (int i = 0; i < pointListCursor_; i++)
		itr++;

	delete p;
	pointList_.erase(itr);


	HWND hCombo = GetDlgItem(GetRouteDialogHandle(), IDC_COMBO1);

	SendMessage(
		(HWND)hCombo,				// �R���{�{�b�N�X�̃n���h��
		(UINT)CB_DELETESTRING,		// ���ڂ̒ǉ�
		(WPARAM)n,					// �폜���鍀�ڂ̃C���f�b�N�X
		(LPARAM)0
		);
}

//=========================================================================
// ���W�̐ݒ�
//=========================================================================
void RouteManager::SetPositionX(float positionX)
{
	RoutePoint *p = nullptr;
	try {
		p = pointList_.at(pointListCursor_);
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
		p = pointList_.at(pointListCursor_);
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
		p = pointList_.at(pointListCursor_);
	}
	catch (const out_of_range& oor) {
		return;
	}
	p->position.z = positionZ;
}


//=========================================================================
// ���W�̎擾
//=========================================================================
D3DXVECTOR3 RouteManager::GetPosition()
{
	RoutePoint *p = nullptr;
	try {
		p = pointList_.at(pointListCursor_);
	}
	catch (const out_of_range& oor) {
		return D3DXVECTOR3(0, 0, 0);
	}

	return p->position;
}


// End of file