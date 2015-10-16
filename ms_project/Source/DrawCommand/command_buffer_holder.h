//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// コマンドバッファホルダー
// 
// Created by Ryusei Kajiya on 20151009
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//*****************************************************************************
// 多重インクルード防止
#pragma once

//*****************************************************************************
// 前方宣言
class CommandBuffer;

//*****************************************************************************
// クラス設計
class CommandBufferHolder
{
public:
	virtual ~CommandBufferHolder() {}

	// ミューテータ
	static void S_SetCommandBuffer(CommandBuffer* command_buffer)
	{
		s_command_buffer = command_buffer;
	}

protected:
	
	// アクセサ
	static CommandBuffer* S_GetCommandBuffer(void)
	{
		return s_command_buffer;
	}

private:
	static CommandBuffer* s_command_buffer;
};