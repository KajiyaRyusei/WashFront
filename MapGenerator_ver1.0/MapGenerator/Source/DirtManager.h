//=============================================================================
//
// 汚れの管理 [DirtManager.h]
// Author : KEITA OHUCHI
//
//=============================================================================
#ifndef _DIRT_MANAGER_H_
#define _DIRT_MANAGER_H_

#include "Main.h"



//-----------------------------------------------------------------------------
// STL使用宣言
//-----------------------------------------------------------------------------
using namespace std;
#include <vector>


//-----------------------------------------------------------------------------
// 前方宣言
//-----------------------------------------------------------------------------
class Dirt;


//-----------------------------------------------------------------------------
// クラス定義
//-----------------------------------------------------------------------------
class DirtManager {
public:
	//=========================================================================
	// コンストラクタとデストラクタ
	//=========================================================================
	DirtManager();
	virtual ~DirtManager();

	//=========================================================================
	// 初期化処理
	//=========================================================================
	HRESULT Init();
	//=========================================================================
	// 更新処理
	//=========================================================================
	void Update();
	//=========================================================================
	// 描画処理
	//=========================================================================
	void Draw();

	//=========================================================================
	// データの出力
	//=========================================================================
	void OutputData(FILE *outputFile);
	//=========================================================================
	// データの入力
	//=========================================================================
	void InputData(FILE *inputFile);


	//=========================================================================
	// 点の削除
	//=========================================================================
	void AllDeleteDirt();
	//=========================================================================
	// 点の生成
	//=========================================================================
	void CreateDirt();
	//=========================================================================
	// 点の削除
	//=========================================================================
	void DeleteDirt();


	//=========================================================================
	// 座標の設定
	//=========================================================================
	void SetPositionX(float positionX);
	void SetPositionY(float positionY);
	void SetPositionZ(float positionZ);
	void SetRadius(float radius);

	//=========================================================================
	// 選択中の点を設定
	//=========================================================================
	void SetDirtListCursor(int cursor) { dirtListCursor_ = cursor; }


	//=========================================================================
	// 座標の取得
	//=========================================================================
	D3DXVECTOR3 GetPosition();
	//=========================================================================
	// 半径の取得
	//=========================================================================
	float GetRadius();


private:

	std::vector <Dirt*>		dirtList_;			// ポイントのリスト
	int						dirtListCursor_;	// カーソル
};


#endif


// End of file