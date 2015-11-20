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
	fileNameMap_.clear();
	filePathMap_.clear();
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
	if (!strcmp(extension, "x")) {
		ret = Manager::GetInstance()->GetModelFactory()->ImportModel(filePath);
	}
	if (!strcmp(extension, "jpg") ||
		!strcmp(extension, "png")) {
//		Manager::GetInstance()->GetModelFactory()->ImportTexture(filePath);
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
		fileNameMap_[filePath] = fileName;
		filePathMap_[fileName] = filePath;
	}

	return ret;
}

//=========================================================================
// ファイルをすべてインポート
//=========================================================================
void ImportFileManager::AllImportFile()
{
	for (auto itr = fileNameMap_.begin(); itr != fileNameMap_.end(); itr++) {
		std::string filePath = (*itr).first;
		std::string fileName = (*itr).second;
		Manager::GetInstance()->GetModelFactory()->ImportModel(filePath);

		HWND hCombo = GetDlgItem(GetDialogHandle(), IDC_COMBO1);

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
const char *ImportFileManager::GetFileName(std::string filePath)
{
	return fileNameMap_[filePath].c_str();
}

//=========================================================================
// ファイル名からファイルのフルパスを取得
//=========================================================================
const char *ImportFileManager::GetFilePath(std::string fileName)
{
	return filePathMap_[fileName].c_str();
}

//=========================================================================
// インポート情報を外部読み込み
//=========================================================================
void ImportFileManager::ReadImportData(FILE *inputFile)
{
	// クリア
	fileNameMap_.clear();
	filePathMap_.clear();

	int num = 0;

	fseek(inputFile, 0, SEEK_SET);

	// インポートしたファイル数取得
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

		if (!strcmp(str, "#FILE")) {
			for (int i = 0; i < num; i++) {
				char fileName[4096];
				char filePath[4096];
				int n;
				fscanf(inputFile, "%d %s %s\n", &n, fileName, filePath);

				// 保存
				fileNameMap_[filePath] = fileName;
				filePathMap_[fileName] = filePath;
			}
		}
	}
}

//=========================================================================
// インポート情報を外部出力
//=========================================================================
void ImportFileManager::SaveImportData(FILE *outputFile)
{
	int importNum = fileNameMap_.size();


	// インポートしたファイル数の出力
	fprintf(outputFile, "#NUM\n");
	fprintf(outputFile, "%d\n", importNum);


	// インポートしたファイル名の出力
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
// ファイルパスのID取得
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
// IDからファイルパス取得
//=========================================================================
const char *ImportFileManager::GetFilePath(int ID)
{
	auto itr = fileNameMap_.begin();

	for (int i = 0; i < ID; i++)
		itr++;

	return (*itr).first.c_str();
}


// End of file