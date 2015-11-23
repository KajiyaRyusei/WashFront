//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// リソースインターフェース
//
// Created by Ryusei Kajiya on 20151102
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//*****************************************************************************
// 多重インクルード防止
#pragma once

//*****************************************************************************
// include
#include "Resource/resource_box.h"

//*****************************************************************************
// 前方宣言
class RendererDevice;

//*****************************************************************************
// クラス設計
template<class T, typename ID>
class Resource
{
public:

	Resource(){ _resource_box = new ResourceBox<T>; }
	virtual ~Resource(){ SafeDelete(_resource_box); }
	// 作成
	virtual void Create(ID id, RendererDevice* device) = 0;
	// 全削除
	virtual void Clear() = 0;
	// 取得
	virtual T Get(ID id) = 0;

protected:
	ResourceBox<T>* _resource_box;
};