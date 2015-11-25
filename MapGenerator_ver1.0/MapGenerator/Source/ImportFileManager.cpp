//=============================================================================
//
// 読み込んだファイルの管理クラス [ImportFileManager.cpp]
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
// コンストラクタ
//=========================================================================
ImportFileManager::ImportFileManager()
{
	// クリア
	modelFileNameMap_.clear();
	modelFilePathMap_.clear();
	textureFileNameMap_.clear();
	textureFilePathMap_.clear();
}

//=========================================================================
// デストラクタ
//=========================================================================
ImportFileManager::~ImportFileManager()
{

}

//=========================================================================
// ファイルのインポート
//=========================================================================
int ImportFileManager::ImportFile(std::string filePath)
{

	// 拡張子の識別
	int filePathLength = filePath.length();
	char extension[10] = {};
	for (int i = filePathLength - 1; 0 <= i; i--) {
		if (filePath.at(i) == '.') {
			strcpy(extension, (filePath.c_str() + i + 1));
			break;
		}
	}


	int ret = 0;
	// 読み込み
	if (!strcmp(extension, "fbx")) {
		ret = Manager::GetInstance()->GetModelFactory()->ImportModel(filePath);
	}
	if (!(strcmp(extension, "jpg") &&
		strcmp(extension, "png"))) {
		ret = Manager::GetInstance()->GetTextureFactory()->ImportTexture(filePath);
	}

	// 読み込みの成功時のみファイル名保存
	if (ret) {
		// ファイルパスからファイル名のみ抽出
		std::string fileName;

		for (int i = filePathLength - 1; 0 <= i; i--) {
			if (filePath.at(i) == '\\') {
				fileName = filePath.substr(i + 1);
				break;
			}
		}

		// 保存
		if (!strcmp(extension, "fbx")) {
			modelFileNameMap_[filePath] = fileName;
			modelFilePathMap_[fileName] = filePath;

			HWND hCombo = GetDlgItem(GetObjectDialogHandle(), IDC_COMBO1);

			SendMessage(
				(HWND)hCombo,				// コンボボックスのハンドル
				(UINT)CB_ADDSTRING,			// 項目の追加
				0,							// ０固定
				(LPARAM)fileName.c_str()	// 追加する項目の文字列
				);
		}
		if (!strcmp(extension, "jpg") ||
			!strcmp(extension, "png")) {
			textureFileNameMap_[filePath] = fileName;
			textureFilePathMap_[fileName] = filePath;

			HWND hCombo = GetDlgItem(GetObjectDialogHandle(), IDC_COMBO2);
			SendMessage(
				(HWND)hCombo,				// コンボボックスのハンドル
				(UINT)CB_ADDSTRING,			// 項目の追加
				0,							// ０固定
				(LPARAM)fileName.c_str()	// 追加する項目の文字列
				);
		}
	}

	return ret;
}

//=========================================================================
// ファイルをすべてインポート
//=========================================================================
void ImportFileManager::AllImportFile()
{
	for (auto itr = modelFileNameMap_.begin(); itr != modelFileNameMap_.end(); itr++) {
		std::string filePath = (*itr).first;
		std::string fileName = (*itr).second;
		Manager::GetInstance()->GetModelFactory()->ImportModel(filePath);

		HWND hCombo = GetDlgItem(GetObjectDialogHandle(), IDC_COMBO1);

		SendMessage(
			(HWND)hCombo,				// コンボボックスのハンドル
			(UINT)CB_ADDSTRING,			// 項目の追加
			0,							// ０固定
			(LPARAM)fileName.c_str()	// 追加する項目の文字列
			);
	}

	for (auto itr = textureFileNameMap_.begin(); itr != textureFileNameMap_.end(); itr++) {
		std::string filePath = (*itr).first;
		std::string fileName = (*itr).second;
		Manager::GetInstance()->GetTextureFactory()->ImportTexture(filePath);

		HWND hCombo = GetDlgItem(GetObjectDialogHandle(), IDC_COMBO2);

		SendMessage(
			(HWND)hCombo,				// コンボボックスのハンドル
			(UINT)CB_ADDSTRING,			// 項目の追加
			0,							// ０固定
			(LPARAM)fileName.c_str()	// 追加する項目の文字列
			);
	}

}

//=========================================================================
// ファイルパスからファイル名のみ取得
//=========================================================================
const char *ImportFileManager::GetModelFileName(std::string filePath)
{
	return modelFileNameMap_[filePath].c_str();
}

//=========================================================================
// ファイル名からファイルのフルパスを取得
//=========================================================================
const char *ImportFileManager::GetModelFilePath(std::string fileName)
{
	return modelFilePathMap_[fileName].c_str();
}

//=========================================================================
// ファイルパスからファイル名のみ取得
//=========================================================================
const char *ImportFileManager::GetTextureFileName(std::string filePath)
{
	return textureFileNameMap_[filePath].c_str();
}

//=========================================================================
// ファイル名からファイルのフルパスを取得
//=========================================================================
const char *ImportFileManager::GetTextureFilePath(std::string fileName)
{
	return textureFilePathMap_[fileName].c_str();
}

//=========================================================================
// インポート情報を外部読み込み
//=========================================================================
void ImportFileManager::ReadImportData(FILE *inputFile)
{
	// クリア
	modelFileNameMap_.clear();
	modelFilePathMap_.clear();
	textureFileNameMap_.clear();
	textureFilePathMap_.clear();

	int modelNum = 0;
	int textureNum = 0;

	fseek(inputFile, 0, SEEK_SET);

	// インポートしたファイル数取得
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

	// インポートファイルパス読み込み
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

				// 保存
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

				// 保存
				textureFileNameMap_[filePath] = fileName;
				textureFilePathMap_[fileName] = filePath;
			}
		}
	}
}

//=========================================================================
// インポート情報を外部出力
//=========================================================================
void ImportFileManager::SaveImportData(FILE *outputFile)
{
	int importNum = modelFileNameMap_.size();


	// インポートしたファイル数の出力
	fprintf(outputFile, "#MODELNUM\n");
	fprintf(outputFile, "%d\n", importNum);


	// インポートしたファイル名の出力
	fprintf(outputFile, "#MODELFILE\n");
	int i = 0;
	for (auto itr = modelFileNameMap_.begin(); itr != modelFileNameMap_.end(); itr++) {
		std::string fileName = (*itr).second;
		std::string filePath = (*itr).first;
		fprintf(outputFile, "%d %s %s\n", i, fileName.c_str(), filePath.c_str());
		i++;
	}



	importNum = textureFileNameMap_.size();

	// インポートしたファイル数の出力
	fprintf(outputFile, "#TEXTURENUM\n");
	fprintf(outputFile, "%d\n", importNum);


	// インポートしたファイル名の出力
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
// ファイルパスのID取得
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
// ファイルパスのID取得
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
// IDからファイルパス取得
//=========================================================================
const char *ImportFileManager::GetModelFilePath(int ID)
{
	auto itr = modelFileNameMap_.begin();

	for (int i = 0; i < ID; i++)
		itr++;

	return (*itr).first.c_str();
}

//=========================================================================
// IDからファイルパス取得
//=========================================================================
const char *ImportFileManager::GetTextureFilePath(int ID)
{
	auto itr = textureFileNameMap_.begin();

	for (int i = 0; i < ID; i++)
		itr++;

	return (*itr).first.c_str();
}

// End of file