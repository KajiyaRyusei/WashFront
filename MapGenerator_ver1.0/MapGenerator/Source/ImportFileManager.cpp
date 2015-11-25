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
	modelFileNameMap_.clear();
	modelFilePathMap_.clear();
	textureFileNameMap_.clear();
	textureFilePathMap_.clear();
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
	if (!strcmp(extension, "fbx")) {
		ret = Manager::GetInstance()->GetModelFactory()->ImportModel(filePath);
	}
	if (!(strcmp(extension, "jpg") &&
		strcmp(extension, "png"))) {
		ret = Manager::GetInstance()->GetTextureFactory()->ImportTexture(filePath);
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
		if (!strcmp(extension, "fbx")) {
			modelFileNameMap_[filePath] = fileName;
			modelFilePathMap_[fileName] = filePath;

			HWND hCombo = GetDlgItem(GetObjectDialogHandle(), IDC_COMBO1);

			SendMessage(
				(HWND)hCombo,				// �R���{�{�b�N�X�̃n���h��
				(UINT)CB_ADDSTRING,			// ���ڂ̒ǉ�
				0,							// �O�Œ�
				(LPARAM)fileName.c_str()	// �ǉ����鍀�ڂ̕�����
				);
		}
		if (!strcmp(extension, "jpg") ||
			!strcmp(extension, "png")) {
			textureFileNameMap_[filePath] = fileName;
			textureFilePathMap_[fileName] = filePath;

			HWND hCombo = GetDlgItem(GetObjectDialogHandle(), IDC_COMBO2);
			SendMessage(
				(HWND)hCombo,				// �R���{�{�b�N�X�̃n���h��
				(UINT)CB_ADDSTRING,			// ���ڂ̒ǉ�
				0,							// �O�Œ�
				(LPARAM)fileName.c_str()	// �ǉ����鍀�ڂ̕�����
				);
		}
	}

	return ret;
}

//=========================================================================
// �t�@�C�������ׂăC���|�[�g
//=========================================================================
void ImportFileManager::AllImportFile()
{
	for (auto itr = modelFileNameMap_.begin(); itr != modelFileNameMap_.end(); itr++) {
		std::string filePath = (*itr).first;
		std::string fileName = (*itr).second;
		Manager::GetInstance()->GetModelFactory()->ImportModel(filePath);

		HWND hCombo = GetDlgItem(GetObjectDialogHandle(), IDC_COMBO1);

		SendMessage(
			(HWND)hCombo,				// �R���{�{�b�N�X�̃n���h��
			(UINT)CB_ADDSTRING,			// ���ڂ̒ǉ�
			0,							// �O�Œ�
			(LPARAM)fileName.c_str()	// �ǉ����鍀�ڂ̕�����
			);
	}

	for (auto itr = textureFileNameMap_.begin(); itr != textureFileNameMap_.end(); itr++) {
		std::string filePath = (*itr).first;
		std::string fileName = (*itr).second;
		Manager::GetInstance()->GetTextureFactory()->ImportTexture(filePath);

		HWND hCombo = GetDlgItem(GetObjectDialogHandle(), IDC_COMBO2);

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
const char *ImportFileManager::GetModelFileName(std::string filePath)
{
	return modelFileNameMap_[filePath].c_str();
}

//=========================================================================
// �t�@�C��������t�@�C���̃t���p�X���擾
//=========================================================================
const char *ImportFileManager::GetModelFilePath(std::string fileName)
{
	return modelFilePathMap_[fileName].c_str();
}

//=========================================================================
// �t�@�C���p�X����t�@�C�����̂ݎ擾
//=========================================================================
const char *ImportFileManager::GetTextureFileName(std::string filePath)
{
	return textureFileNameMap_[filePath].c_str();
}

//=========================================================================
// �t�@�C��������t�@�C���̃t���p�X���擾
//=========================================================================
const char *ImportFileManager::GetTextureFilePath(std::string fileName)
{
	return textureFilePathMap_[fileName].c_str();
}

//=========================================================================
// �C���|�[�g�����O���ǂݍ���
//=========================================================================
void ImportFileManager::ReadImportData(FILE *inputFile)
{
	// �N���A
	modelFileNameMap_.clear();
	modelFilePathMap_.clear();
	textureFileNameMap_.clear();
	textureFilePathMap_.clear();

	int modelNum = 0;
	int textureNum = 0;

	fseek(inputFile, 0, SEEK_SET);

	// �C���|�[�g�����t�@�C�����擾
	while (true) {
		char str[4096] = {};
		if (EOF == fscanf(inputFile, "%s", str))
			break;

		if (!strcmp(str, "#MODELNUM")) {
			fscanf(inputFile, "%d", &modelNum);
		}
		if (!strcmp(str, "#TEXTURENUM")) {
			fscanf(inputFile, "%d", &textureNum);
		}
	}

	fseek(inputFile, 0, SEEK_SET);

	// �C���|�[�g�t�@�C���p�X�ǂݍ���
	while (true) {
		char str[4096] = {};
		if (EOF == fscanf(inputFile, "%s", str))
			break;

		if (!strcmp(str, "#MODELFILE")) {
			for (int i = 0; i < modelNum; i++) {
				char fileName[4096];
				char filePath[4096];
				int n;
				fscanf(inputFile, "%d %s %s\n", &n, fileName, filePath);

				// �ۑ�
				modelFileNameMap_[filePath] = fileName;
				modelFilePathMap_[fileName] = filePath;
			}
		}

		if (!strcmp(str, "#TEXTUREFILE")) {
			for (int i = 0; i < textureNum; i++) {
				char fileName[4096];
				char filePath[4096];
				int n;
				fscanf(inputFile, "%d %s %s\n", &n, fileName, filePath);

				// �ۑ�
				textureFileNameMap_[filePath] = fileName;
				textureFilePathMap_[fileName] = filePath;
			}
		}
	}
}

//=========================================================================
// �C���|�[�g�����O���o��
//=========================================================================
void ImportFileManager::SaveImportData(FILE *outputFile)
{
	int importNum = modelFileNameMap_.size();


	// �C���|�[�g�����t�@�C�����̏o��
	fprintf(outputFile, "#MODELNUM\n");
	fprintf(outputFile, "%d\n", importNum);


	// �C���|�[�g�����t�@�C�����̏o��
	fprintf(outputFile, "#MODELFILE\n");
	int i = 0;
	for (auto itr = modelFileNameMap_.begin(); itr != modelFileNameMap_.end(); itr++) {
		std::string fileName = (*itr).second;
		std::string filePath = (*itr).first;
		fprintf(outputFile, "%d %s %s\n", i, fileName.c_str(), filePath.c_str());
		i++;
	}



	importNum = textureFileNameMap_.size();

	// �C���|�[�g�����t�@�C�����̏o��
	fprintf(outputFile, "#TEXTURENUM\n");
	fprintf(outputFile, "%d\n", importNum);


	// �C���|�[�g�����t�@�C�����̏o��
	fprintf(outputFile, "#TEXTUREFILE\n");
	i = 0;
	for (auto itr = textureFileNameMap_.begin(); itr != textureFileNameMap_.end(); itr++) {
		std::string fileName = (*itr).second;
		std::string filePath = (*itr).first;
		fprintf(outputFile, "%d %s %s\n", i, fileName.c_str(), filePath.c_str());
		i++;
	}
}

//=========================================================================
// �t�@�C���p�X��ID�擾
//=========================================================================
int ImportFileManager::GetModelFilePathID(char *filePath)
{
	std::string path0;
	path0.assign(filePath);

	int i = 0;
	for (auto itr = modelFileNameMap_.begin(); itr != modelFileNameMap_.end(); itr++) {
		std::string path1 = (*itr).first;
		if (!path0.compare(path1))
			return i;
		i++;
	}

	return -1;
}
//=========================================================================
// �t�@�C���p�X��ID�擾
//=========================================================================
int ImportFileManager::GetTextureFilePathID(char *filePath)
{
	std::string path0;
	path0.assign(filePath);

	int i = 0;
	for (auto itr = textureFileNameMap_.begin(); itr != textureFileNameMap_.end(); itr++) {
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
const char *ImportFileManager::GetModelFilePath(int ID)
{
	auto itr = modelFileNameMap_.begin();

	for (int i = 0; i < ID; i++)
		itr++;

	return (*itr).first.c_str();
}

//=========================================================================
// ID����t�@�C���p�X�擾
//=========================================================================
const char *ImportFileManager::GetTextureFilePath(int ID)
{
	auto itr = textureFileNameMap_.begin();

	for (int i = 0; i < ID; i++)
		itr++;

	return (*itr).first.c_str();
}

// End of file