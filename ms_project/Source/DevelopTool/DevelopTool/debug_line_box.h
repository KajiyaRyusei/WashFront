//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// デバッグ用ラインBOX
//
// Created by Ryusei Kajiya on 20151028
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//*****************************************************************************
// 多重インクルード防止
#pragma once

//*****************************************************************************
// クラス設計
class DebugLineBox
{
public:

	DebugLineBox(){}
	virtual ~DebugLineBox(){}

	void Initialize();
	void Finalize();
	void Draw();

	// これで登録してください
	void RegisteBox(
		const D3DXVECTOR3& volume,
		const D3DXVECTOR3& position,
		const D3DXVECTOR3& rotation);

private:

#ifdef _DEBUG

	static const u32 kVertexMax = 22;

	struct LineBox
	{
		D3DXVECTOR3 position;
		D3DXVECTOR3 rotation;
		D3DXVECTOR3 scaling;
	};

	struct VERTEX_BOX
	{
		D3DXVECTOR3 position;
		D3DCOLOR color;
	};

	static const u32 kMaxBox = 1000;
	LineBox _boxs[kMaxBox];
	VERTEX_BOX vertices[22];

	u32 _current_line_box_index;

#endif
};