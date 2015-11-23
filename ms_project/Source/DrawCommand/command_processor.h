//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// コマンドプロセッサ
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
class CommandProcessor
{
public:

	explicit CommandProcessor(const CommandBuffer& command_buffer) :
		_command_buffer(command_buffer){}

	~CommandProcessor(){}

	// 描画処理を行う。
	void ProccessLightDepth(void) const;
	void ProccessDefault(void) const;
	void ProccessShadow(void) const;
	void ProccessField(void) const;
	void ProccessBackGround(void) const;
	void ProccessTranslucent(void) const;
	void ProccessAIM(void) const;
	void Proccess2D(void) const;

private:

	// コピー禁止
	CommandProcessor& operator=(const CommandProcessor& rhs);

	// 上記のプロセス処理の本体
	void Proccess(u32 render_state_paramater) const;

	const CommandBuffer& _command_buffer;
};