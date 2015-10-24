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
		const fx32 length,
		const D3DXVECTOR3& position,
		const D3DXVECTOR3& rotation);

private:

#ifndef _RELEASE


	struct LINE
	{
		D3DXVECTOR3 vertices[2];
		D3DXVECTOR3 position;
		D3DXVECTOR3 rotation;
	};

	static const u32 kMaxLine = 1000;

	LINE _lines[kMaxLine];
	u32 _current_line_index;

#endif

};