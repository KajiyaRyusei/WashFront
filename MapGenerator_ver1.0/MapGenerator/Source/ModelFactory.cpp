//=============================================================================
//
// モデルファクトリ [ModelFactory.cpp]
// Author : KEITA OHUCHI
//
//=============================================================================

#include "ModelFactory.h"
#include "Manager.h"
#include "Renderer.h"


//=========================================================================
// コンストラクタ
//=========================================================================
ModelFactory::ModelFactory()
{
}

//=========================================================================
// デストラクタ
//=========================================================================
ModelFactory::~ModelFactory()
{

	// モデルポインタの解放
	for (auto itr = modelMap_.begin(); itr != modelMap_.end(); ++itr) {
		// 解放処理
		SafeDelete(itr->second);
	}
	modelMap_.clear();

}



//=========================================================================
// モデルの読み込み
//=========================================================================
int ModelFactory::ImportModel(std::string xFilePath)
{

	// すでにあるかどうかチェック
	if (modelMap_.find(xFilePath) == modelMap_.end()) {
		// モデル生成
		modelMap_[xFilePath] = Model::Create(xFilePath.c_str());
		return 1;
	} else {
		return 0;
	}

}


//=========================================================================
// モデルポインタの取得
//=========================================================================
Model *ModelFactory::GetModel(std::string xFilePath)
{

	// すでにあるかどうかチェック
	if (modelMap_.find(xFilePath) == modelMap_.end()) {
		// モデル生成
		modelMap_[xFilePath] = Model::Create(xFilePath.c_str());
	}

	return modelMap_[xFilePath];

}


// End of file