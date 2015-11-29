//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// シーン：リザルト
//
// Created by Ryusei Kajiya on 20151123
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//*****************************************************************************
// インクルード
#include "scene_result.h"
#include "DevelopTool/develop_tool_manager.h"
#include "World/world.h"

// input
#include "Input/input_manager.h"

// scene
#include "Scene/scene_manager.h"
#include "Scene/scene_spawner.h"
#include "Scene/Scene/scene_title.h"

// unit
#include "Unit/Result/result_bg.h"
#include "Unit\Result\bulletin_board.h"
#include "Unit\Result\score_board.h"
#include "Unit\Title\text.h"
#include "Unit\Result\message_box.h"
#include "Unit\Result\judge.h"
#include "Unit/Result/score.h"
#include "Unit/Game/water_spray_pool_dummy.h"

//=============================================================================
// コンストラクタ
SceneResult::SceneResult(Application *application) :
Scene{ application }
{
	Initialize();
}

//=============================================================================
// 初期化
void SceneResult::Initialize()
{
	_world = new World();

	WaterSprayPoolDummy* water_spray_pool = new WaterSprayPoolDummy(_application, _world);
	_world->SetWaterSprayPool(water_spray_pool);

	std::list<Unit*> unit_list;

	// 背景
	unit_list.push_back(new Result_BGUnit(_application, _world));
	// 掲示板
	unit_list.push_back(new BulletinUnit(_application, _world));
	// スコアボード
	Score_BoardUnit* board1 = new Score_BoardUnit(_application, _world);
	Score_BoardUnit* board2 = new Score_BoardUnit(_application, _world);
	board1->SetPosition(D3DXVECTOR3(280.0f, 790.0f, 0.0f));
	board2->SetPosition(D3DXVECTOR3(677.0f, 790.0f, 0.0f));
	unit_list.push_back(board1);
	unit_list.push_back(board2);
	
	// メッセージボックス
	Message_BoxUnit* box1 = new Message_BoxUnit(_application, _world);
	Message_BoxUnit* box2 = new Message_BoxUnit(_application, _world);
	Message_BoxUnit* box3 = new Message_BoxUnit(_application, _world);
	Message_BoxUnit* box4 = new Message_BoxUnit(_application, _world);
	Message_BoxUnit* box5 = new Message_BoxUnit(_application, _world);
	Message_BoxUnit* box6 = new Message_BoxUnit(_application, _world);
	Message_BoxUnit* box7 = new Message_BoxUnit(_application, _world);
	Message_BoxUnit* box8 = new Message_BoxUnit(_application, _world);
	box1->SetPosition(D3DXVECTOR3(200.0f, 670.0f, 0.0f));
	box2->SetPosition(D3DXVECTOR3(200.0f, 730.0f, 0.0f));
	box3->SetPosition(D3DXVECTOR3(200.0f, 790.0f, 0.0f));
	box4->SetPosition(D3DXVECTOR3(200.0f, 850.0f, 0.0f));
	box5->SetPosition(D3DXVECTOR3(600.0f, 670.0f, 0.0f));
	box6->SetPosition(D3DXVECTOR3(600.0f, 730.0f, 0.0f));
	box7->SetPosition(D3DXVECTOR3(600.0f, 790.0f, 0.0f));
	box8->SetPosition(D3DXVECTOR3(600.0f, 850.0f, 0.0f));
	unit_list.push_back(box1);
	unit_list.push_back(box2);
	unit_list.push_back(box3);
	unit_list.push_back(box4);
	unit_list.push_back(box5);
	unit_list.push_back(box6);
	unit_list.push_back(box7);
	unit_list.push_back(box8);
	// キャプション

	//// スコア
	ScoreUnit* score1 = new ScoreUnit(_application, _world);
	ScoreUnit* score2 = new ScoreUnit(_application, _world);
	ScoreUnit* score3 = new ScoreUnit(_application, _world);
	ScoreUnit* score4 = new ScoreUnit(_application, _world);
	ScoreUnit* score5 = new ScoreUnit(_application, _world);
	ScoreUnit* score6 = new ScoreUnit(_application, _world);
	ScoreUnit* score7 = new ScoreUnit(_application, _world);
	ScoreUnit* score8 = new ScoreUnit(_application, _world);

	// sukoa no keisan wo kokode yaru
	// ex 
	// sorezore ni set
	score1->SetDestScore( 99999 );
	score2->SetDestScore( 1732 );
	score3->SetDestScore( 6887 );
	score4->SetDestScore( 32526 );
	score5->SetDestScore( 9 );
	score6->SetDestScore( 35247 );
	score7->SetDestScore( 78 );
	score8->SetDestScore( 437 );

	unit_list.push_back(score1);
	unit_list.push_back(score2);
	unit_list.push_back(score3);
	unit_list.push_back(score4);
	unit_list.push_back(score5);
	unit_list.push_back(score6);
	unit_list.push_back(score7);
	unit_list.push_back(score8);


	// 勝敗
	JudgeUnit* judge1 = new JudgeUnit(_application, _world);
	JudgeUnit* judge2 = new JudgeUnit(_application, _world);

	// syouhai de texture wo kaeru
	// judge1->CreateTexture(  );
	// judge2->CreateTexture(  );

	judge1->SetPosition(D3DXVECTOR3(280.0f, 390.0f, 0.0f));
	judge2->SetPosition(D3DXVECTOR3(677.0f, 390.0f, 0.0f));
	
	unit_list.push_back(judge1);
	unit_list.push_back(judge2);

	// 点滅文字
	TextUnit* text = new TextUnit(_application, _world);
	text->SetPosition(D3DXVECTOR3(680.0f, 500.0f, 0.0f));
	unit_list.push_back(text);


	_world->PushUnit(std::move(unit_list));

}
//=============================================================================
// 終了
void SceneResult::Finalize()
{
	SafeDelete(_world);
	Unit::ResetID();
}
//=============================================================================
// 更新
void SceneResult::Update()
{
	Reference::GetInstance().GetDevelopToolManager()->GetDebugPrint().Print("リザルトシーンですよ\n");

	if( _application->GetInputManager()->CheckTrigger(INPUT_EVENT_RETURN) )
	{
		_application->GetSceneManager()->SetNextScene(new SpawnerForScene<SceneTitle>);
	}

	_world->Update();
}
//=============================================================================
// 描画
void SceneResult::Draw()
{
	_world->Draw();
}
