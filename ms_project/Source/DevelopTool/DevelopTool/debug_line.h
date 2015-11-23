//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// デバッグ用ライン
//
// Created by Ryusei Kajiya on 20151023
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//*****************************************************************************
// 多重インクルード防止
#pragma once

//*****************************************************************************
// クラス設計
class DebugLine
{
public:

	DebugLine(){}
	virtual ~DebugLine(){}

	void Initialize();
	void Finalize();
	void Draw();

	// これで登録してください
	void RegisteLine(
		const D3DXVECTOR3& start_point,
		const D3DXVECTOR3& end_point);

private:

#ifdef _DEBUG


	struct LINE
	{
		D3DXVECTOR3 vertices[2];
	};

	static const u32 kMaxLine = 1000;

	LINE _lines[kMaxLine];
	u32 _current_line_index;

#endif

};