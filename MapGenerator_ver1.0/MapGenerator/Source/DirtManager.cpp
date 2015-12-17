//=============================================================================
//
// ����̊Ǘ� [DirtManager.cpp]
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
// �R���X�g���N�^
//=========================================================================
DirtManager::DirtManager() :
dirtListCursor_(0)
{
	dirtList_.clear();
}

//=========================================================================
// �f�X�g���N�^
//=========================================================================
DirtManager::~DirtManager()
{
	for (auto itr = dirtList_.begin(); itr != dirtList_.end(); itr++)
		delete (*itr);

	dirtList_.clear();
}

//=========================================================================
// ����������
//=========================================================================
HRESULT DirtManager::Init()
{
	return S_OK;
}

//=========================================================================
// �X�V����
//=========================================================================
void DirtManager::Update()
{
}

//=========================================================================
// �`�揈��
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
// �f�[�^�̏o��
//=========================================================================
void DirtManager::OutputData(FILE *outputFile)
{

	int size = dirtList_.size();


	// ����̐��o��
	fprintf(outputFile, "#NUM\n");
	fprintf(outputFile, "%d\n", size);


	// ����̏��o��
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
// �f�[�^�̓���
//=========================================================================
void DirtManager::InputData(FILE *inputFile)
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
void DirtManager::AllDeleteDirt()
{
	for (auto itr = dirtList_.begin(); itr != dirtList_.end(); itr++) {
		SafeDelete(*itr);
	}

	dirtList_.clear();
}

//=========================================================================
// �_�̒ǉ�
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
		(HWND)hCombo,				// �R���{�{�b�N�X�̃n���h��
		(UINT)CB_ADDSTRING,			// ���ڂ̒ǉ�
		0,							// �O�Œ�
		(LPARAM)str					// �ǉ����鍀�ڂ̕�����
		);

}


//=========================================================================
// �_�̍폜
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
		(HWND)hCombo,				// �R���{�{�b�N�X�̃n���h��
		(UINT)CB_DELETESTRING,		// ���ڂ̒ǉ�
		(WPARAM)n,					// �폜���鍀�ڂ̃C���f�b�N�X
		(LPARAM)0
		);
}

//=========================================================================
// ���W�̐ݒ�
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
// ���W�̎擾
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
// ���a�̎擾
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