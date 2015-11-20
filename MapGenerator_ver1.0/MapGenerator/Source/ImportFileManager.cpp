//=============================================================================
//
// �ǂݍ��񂾃t�@�C���̊Ǘ��N���X [ImportFileManager.cpp]
// Author : KEITA OHUCHI
//
//=============================================================================

#include "Main.h"
#include "ImportFileManager.h"
#include "Manager.h"
#include "ModelFactory.h"
#include "TextureFactory.h"
#include "../resource.h"


//=========================================================================
// �R���X�g���N�^
//=========================================================================
ImportFileManager::ImportFileManager()
{
	// �N���A
	fileNameMap_.clear();
	filePathMap_.clear();
}

//=========================================================================
// �f�X�g���N�^
//=========================================================================
ImportFileManager::~ImportFileManager()
{

}

//=========================================================================
// �t�@�C���̃C���|�[�g
//=========================================================================
int ImportFileManager::ImportFile(std::string filePath)
{

	// �g���q�̎���
	int filePathLength = filePath.length();
	char extension[10] = {};
	for (int i = filePathLength - 1; 0 <= i; i--) {
		if (filePath.at(i) == '.') {
			strcpy(extension, (filePath.c_str() + i + 1));
			break;
		}
	}


	int ret = 0;
	// �ǂݍ���
	if (!strcmp(extension, "x")) {
		ret = Manager::GetInstance()->GetModelFactory()->ImportModel(filePath);
	}
	if (!strcmp(extension, "jpg") ||
		!strcmp(extension, "png")) {
//		Manager::GetInstance()->GetModelFactory()->ImportTexture(filePath);
	}

	// �ǂݍ��݂̐������̂݃t�@�C�����ۑ�
	if (ret) {
		// �t�@�C���p�X����t�@�C�����̂ݒ��o
		std::string fileName;

		for (int i = filePathLength - 1; 0 <= i; i--) {
			if (filePath.at(i) == '\\') {
				fileName = filePath.substr(i + 1);
				break;
			}
		}

		// �ۑ�
		fileNameMap_[filePath] = fileName;
		filePathMap_[fileName] = filePath;
	}

	return ret;
}

//=========================================================================
// �t�@�C�������ׂăC���|�[�g
//=========================================================================
void ImportFileManager::AllImportFile()
{
	for (auto itr = fileNameMap_.begin(); itr != fileNameMap_.end(); itr++) {
		std::string filePath = (*itr).first;
		std::string fileName = (*itr).second;
		Manager::GetInstance()->GetModelFactory()->ImportModel(filePath);

		HWND hCombo = GetDlgItem(GetDialogHandle(), IDC_COMBO1);

		SendMessage(
			(HWND)hCombo,				// �R���{�{�b�N�X�̃n���h��
			(UINT)CB_ADDSTRING,			// ���ڂ̒ǉ�
			0,							// �O�Œ�
			(LPARAM)fileName.c_str()	// �ǉ����鍀�ڂ̕�����
			);

	}
}

//=========================================================================
// �t�@�C���p�X����t�@�C�����̂ݎ擾
//=========================================================================
const char *ImportFileManager::GetFileName(std::string filePath)
{
	return fileNameMap_[filePath].c_str();
}

//=========================================================================
// �t�@�C��������t�@�C���̃t���p�X���擾
//=========================================================================
const char *ImportFileManager::GetFilePath(std::string fileName)
{
	return filePathMap_[fileName].c_str();
}

//=========================================================================
// �C���|�[�g�����O���ǂݍ���
//=========================================================================
void ImportFileManager::ReadImportData(FILE *inputFile)
{
	// �N���A
	fileNameMap_.clear();
	filePathMap_.clear();

	int num = 0;

	fseek(inputFile, 0, SEEK_SET);

	// �C���|�[�g�����t�@�C�����擾
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

		if (!strcmp(str, "#FILE")) {
			for (int i = 0; i < num; i++) {
				char fileName[4096];
				char filePath[4096];
				int n;
				fscanf(inputFile, "%d %s %s\n", &n, fileName, filePath);

				// �ۑ�
				fileNameMap_[filePath] = fileName;
				filePathMap_[fileName] = filePath;
			}
		}
	}
}

//=========================================================================
// �C���|�[�g�����O���o��
//=========================================================================
void ImportFileManager::SaveImportData(FILE *outputFile)
{
	int importNum = fileNameMap_.size();


	// �C���|�[�g�����t�@�C�����̏o��
	fprintf(outputFile, "#NUM\n");
	fprintf(outputFile, "%d\n", importNum);


	// �C���|�[�g�����t�@�C�����̏o��
	fprintf(outputFile, "#FILE\n");
	int i = 0;
	for (auto itr = fileNameMap_.begin(); itr != fileNameMap_.end(); itr++) {
		std::string fileName = (*itr).second;
		std::string filePath = (*itr).first;
		fprintf(outputFile, "%d %s %s\n", i, fileName.c_str(), filePath.c_str());
		i++;
	}
}

//=========================================================================
// �t�@�C���p�X��ID�擾
//=========================================================================
int ImportFileManager::GetFilePathID(char *filePath)
{
	std::string path0;
	path0.assign(filePath);

	int i = 0;
	for (auto itr = fileNameMap_.begin(); itr != fileNameMap_.end(); itr++) {
		std::string path1 = (*itr).first;
		if (!path0.compare(path1))
			return i;
		i++;
	}

	return -1;
}

//=========================================================================
// ID����t�@�C���p�X�擾
//=========================================================================
const char *ImportFileManager::GetFilePath(int ID)
{
	auto itr = fileNameMap_.begin();

	for (int i = 0; i < ID; i++)
		itr++;

	return (*itr).first.c_str();
}


// End of file