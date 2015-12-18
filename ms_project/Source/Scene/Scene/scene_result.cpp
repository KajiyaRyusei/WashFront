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
#include "Unit\Title\text.h"
#include "Unit\Result\message_box.h"
#include "Unit\Result\judge.h"
#include "Unit/Result/score.h"
#include "Unit/Game/water_spray_pool_dummy.h"

// viewport
#include "Renderer/directx9.h"
#include "Windows/window.h"

// sound
#include "Sound\sound.h"

//*****************************************************************************
// const
const int			countUpTime		= 60;
const float			countTimeSpeed	= 1.0f / countUpTime;


const D3DXVECTOR3	WindowPos[2][19] =
{
	// 960 : 540
	{
		// Bg
		D3DXVECTOR3(480.0f, 270.0f, 0.0f),

		// keiji
		D3DXVECTOR3(480.0f, 790.0f, 0.0),

		// text
		D3DXVECTOR3(680.0f, 500.0f, 0.0f),

		// mesBox
		D3DXVECTOR3(270.0f, 700.0f, 0.0f),
		D3DXVECTOR3(270.0f, 740.0f, 0.0f),
		D3DXVECTOR3(270.0f, 780.0f, 0.0f),
		D3DXVECTOR3(270.0f, 870.0f, 0.0f),
		D3DXVECTOR3(270.0f, 910.0f, 0.0f),
		D3DXVECTOR3(270.0f, 950.0f, 0.0f),

		// score
		D3DXVECTOR3(430.0f, 700.0f, 0.0f),
		D3DXVECTOR3(430.0f, 740.0f, 0.0f),
		D3DXVECTOR3(430.0f, 780.0f, 0.0f),
		D3DXVECTOR3(700.0f, 700.0f, 0.0f),
		D3DXVECTOR3(430.0f, 870.0f, 0.0f),
		D3DXVECTOR3(430.0f, 910.0f, 0.0f),
		D3DXVECTOR3(430.0f, 950.0f, 0.0f),
		D3DXVECTOR3(700.0f, 860.0f, 0.0f),

		// judge
		D3DXVECTOR3(680.0f, 210.0f, 0.0f),
		D3DXVECTOR3(680.0f, 370.0f, 0.0f)
	},

	// 1280 : 720
	{
		// Bg
		D3DXVECTOR3(640.0f, 360.0f, 0.0f),

		// keiji
		D3DXVECTOR3(640.0f, 1300.0f, 0.0),

		// text
		D3DXVECTOR3(980.0f, 670.0f, 0.0f),

		// mesBox
		D3DXVECTOR3(330.0f, 1170.0f, 0.0f),
		D3DXVECTOR3(330.0f, 1225.0f, 0.0f),
		D3DXVECTOR3(330.0f, 1280.0f, 0.0f),
		D3DXVECTOR3(330.0f, 1410.0f, 0.0f),
		D3DXVECTOR3(330.0f, 1465.0f, 0.0f),
		D3DXVECTOR3(330.0f, 1520.0f, 0.0f),

		// score
		D3DXVECTOR3(580.0f, 1170.0f, 0.0f),
		D3DXVECTOR3(580.0f, 1225.0f, 0.0f),
		D3DXVECTOR3(580.0f, 1280.0f, 0.0f),
		D3DXVECTOR3(1000.0f, 1170.0f, 0.0f),
		D3DXVECTOR3(580.0f, 1410.0f, 0.0f),
		D3DXVECTOR3(580.0f, 1465.0f, 0.0f),
		D3DXVECTOR3(580.0f, 1520.0f, 0.0f),
		D3DXVECTOR3(1000.0f, 1410.0f, 0.0f),

		// judge
		D3DXVECTOR3(980.0f, 290.0f, 0.0f),
		D3DXVECTOR3(980.0f, 520.0f, 0.0f)
	}
};

const D3DXVECTOR3 WindowScale[2][7] =
{
	// 960 : 540
	{
		// Bg
		D3DXVECTOR3(960.0f, 540.0f, 0.0f),

		// keiji
		D3DXVECTOR3(800.0f, 430.0f, 0.0f),

		// text
		D3DXVECTOR3(500.0f, 50.0f, 0.0f),

		// mesBox
		D3DXVECTOR3(100.0f, 30.0f, 0.0f),

		// score
		D3DXVECTOR3(20.0f, 40.0f, 0.0f),
		D3DXVECTOR3(40.0f , 70.0f, 0.0f ) ,

		// judge
		D3DXVECTOR3(200.0f, 80.0f, 0.0f)
	},

	// 1280 : 720
	{
		// Bg
		D3DXVECTOR3(1280.0f, 720.0f, 0.0f),

		// keiji
		D3DXVECTOR3(1200.0f, 620.0f, 0.0f),

		// text
		D3DXVECTOR3(500.0f, 60.0f, 0.0f),

		// mesBox
		D3DXVECTOR3(150.0f, 45.0f, 0.0f),

		// score
		D3DXVECTOR3(30.0f, 60.0f, 0.0f),
		D3DXVECTOR3(50.0f , 105.0f, 0.0f ) ,

		// judge
		D3DXVECTOR3(250.0f, 120.0f, 0.0f)
	}
};



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
	Result_BGUnit* pBg = new Result_BGUnit(_application, _world);
	pBg->SetPosition(WindowPos[windowSizeID][0]);
	pBg->SetScaling(WindowScale[windowSizeID][0]);
	unit_list.push_back(pBg);

	// 掲示板
	BulletinUnit* pBulletin = new BulletinUnit(_application, _world);
	pBulletin->SetPosition(WindowPos[windowSizeID][1]);
	pBulletin->SetScaling(WindowScale[windowSizeID][1]);
	unit_list.push_back(pBulletin);

	// 点滅文字
	TextUnit* text = new TextUnit(_application, _world);
	text->SetPosition(WindowPos[windowSizeID][2]);
	text->SetScaling(WindowScale[windowSizeID][2]);
	unit_list.push_back(text);

	// メッセージボックス
	Message_BoxUnit* box1 = new Message_BoxUnit(_application, _world);
	Message_BoxUnit* box2 = new Message_BoxUnit(_application, _world);
	Message_BoxUnit* box3 = new Message_BoxUnit(_application, _world);
	Message_BoxUnit* box4 = new Message_BoxUnit(_application, _world);
	Message_BoxUnit* box5 = new Message_BoxUnit(_application, _world);
	Message_BoxUnit* box6 = new Message_BoxUnit(_application, _world);

	box1->SetPosition(WindowPos[windowSizeID][3]);
	box2->SetPosition(WindowPos[windowSizeID][4]);
	box3->SetPosition(WindowPos[windowSizeID][5]);
	box4->SetPosition(WindowPos[windowSizeID][6]);
	box5->SetPosition(WindowPos[windowSizeID][7]);
	box6->SetPosition(WindowPos[windowSizeID][8]);

	box1->SetScaling(WindowScale[windowSizeID][3]);
	box2->SetScaling(WindowScale[windowSizeID][3]);
	box3->SetScaling(WindowScale[windowSizeID][3]);
	box4->SetScaling(WindowScale[windowSizeID][3]);
	box5->SetScaling(WindowScale[windowSizeID][3]);
	box6->SetScaling(WindowScale[windowSizeID][3]);

	// ポイントの内容で絵を変える
	/*box1->ChangeTexture();
	box2->ChangeTexture();
	box3->ChangeTexture();
	box4->ChangeTexture();
	box5->ChangeTexture();
	box6->ChangeTexture();*/

	unit_list.push_back(box1);
	unit_list.push_back(box2);
	unit_list.push_back(box3);
	unit_list.push_back(box4);
	unit_list.push_back(box5);
	unit_list.push_back(box6);


	// スコア
	for( int i = 0; i < 8; i++ )
	{
		_pScore[i] = new ScoreUnit(_application, _world);
		_pScore[i]->SetScale(WindowScale[windowSizeID][4]);
	}

	_pScore[0]->SetPos(WindowPos[windowSizeID][9]);
	_pScore[1]->SetPos(WindowPos[windowSizeID][10]);
	_pScore[2]->SetPos(WindowPos[windowSizeID][11]);
	_pScore[3]->SetPos(WindowPos[windowSizeID][12]);
	_pScore[4]->SetPos(WindowPos[windowSizeID][13]);
	_pScore[5]->SetPos(WindowPos[windowSizeID][14]);
	_pScore[6]->SetPos(WindowPos[windowSizeID][15]);
	_pScore[7]->SetPos(WindowPos[windowSizeID][16]);

	_pScore[3]->SetTexture( TEXT( "data/Texture/number2.png" ) );
	_pScore[7]->SetTexture( TEXT( "data/Texture/number2.png" ) );

	_pScore[3]->SetScale( WindowScale[windowSizeID][ 5 ] );
	_pScore[7]->SetScale( WindowScale[windowSizeID][ 5 ] );

	// 1P のポイント１
	_pScore[0]->SetDestScore(43786);
	// 1P のポイント２
	_pScore[1]->SetDestScore(99999);
	// 1P のポイント３
	_pScore[2]->SetDestScore(1732);
	// 1P の合計ポイント
	_pScore[3]->SetDestScore(6887);
	// 2P のポイント１
	_pScore[4]->SetDestScore(32526);
	// 2P のポイント２
	_pScore[5]->SetDestScore(9);
	// 2P のポイント３
	_pScore[6]->SetDestScore(35247);
	// 2P の合計ポイント
	_pScore[7]->SetDestScore(78);

	for( int i = 0; i < 8; i++ )
	{
		unit_list.push_back(_pScore[i]);
	}


	// 勝敗
	_pJudge[0] = new JudgeUnit(_application, _world);
	_pJudge[1] = new JudgeUnit(_application, _world);
	_pJudge[0]->SetPosition(WindowPos[windowSizeID][17]);
	_pJudge[1]->SetPosition(WindowPos[windowSizeID][18]);

	_pJudge[0]->SetScaling(WindowScale[windowSizeID][6]);
	_pJudge[1]->SetScaling(WindowScale[windowSizeID][6]);

	// 上のスコアでここのテクスチャを変える
	_pJudge[0]->CreateTexture( L"data/texture/MS_win.png" );
	_pJudge[1]->CreateTexture( L"data/texture/MS_lose.png" );

	unit_list.push_back(_pJudge[0]);
	unit_list.push_back(_pJudge[1]);

	_grade = 0;

	_world->PushUnit(std::move(unit_list));

	_application->GetSound()->Play(BGM_RESULT);

}
//=============================================================================
// 終了
void SceneResult::Finalize()
{
	_application->GetSound()->Stop(BGM_RESULT);
	SafeDelete(_world);
	Unit::ResetID();
}
//=============================================================================
// 更新
void SceneResult::Update()
{
	Reference::GetInstance().GetDevelopToolManager()->GetDebugPrint().Print("リザルトシーンですよ\n");

	if( _pJudge[1]->GetTime() > disp_time )
	{
		if( _application->GetInputManager()->CheckTrigger(INPUT_EVENT_Z) )
		{
			_application->GetSound()->Play(SE_DECIDE);
			_application->GetSceneManager()->SetNextScene(new SpawnerForScene<SceneTitle>);
		}
	}

	if( ScoreUnit::GetFlg() == true )
	{
		if( _application->GetInputManager()->CheckTrigger(INPUT_EVENT_Z) )
		{
			_pJudge[0]->SetTime(disp_time);
			_pJudge[1]->SetTime(disp_time);
		}
	}

	if( BulletinUnit::GetUpdateFlg() )
	{
		for( int i = 0; i < 8; i++ )
		{
			_pScore[i]->Move();
		}
	}

	if( BulletinUnit::GetDispFlg() )
	{

		if( _application->GetInputManager()->CheckTrigger(INPUT_EVENT_Z) )
		{
			_grade = 4.0f;
			ScoreUnit::SetFlg(true);
		}

		_grade += countTimeSpeed;

		_pScore[0]->CountUp(_grade);
		_pScore[4]->CountUp(_grade);

		_pScore[1]->CountUp(_grade - 1.0f);
		_pScore[5]->CountUp(_grade - 1.0f);

		_pScore[2]->CountUp(_grade - 2.0f);
		_pScore[6]->CountUp(_grade - 2.0f);

		_pScore[3]->CountUp(_grade - 3.0f);
		_pScore[7]->CountUp(_grade - 3.0f);

		if( _grade >= 4.0f && ScoreUnit::GetFlg() == false )
		{
			ScoreUnit::SetFlg(true);
			_application->GetSound()->Stop(SE_COUNT);
			_application->GetSound()->Play(SE_REWARD);
		}


	}

	_world->Update();
}
//=============================================================================
// 描画
void SceneResult::Draw()
{
	_world->Draw();

	D3DVIEWPORT9 viewport;
	viewport.Height = _application->GetWindow()->GetSizeWindowHeight();
	viewport.Width = _application->GetWindow()->GetSizeWindowWidth();
	viewport.X = 0;
	viewport.Y = 0;
	viewport.MaxZ = 1.f;
	viewport.MinZ = 0.f;

	_application->GetRendererDevice()->GetDevice()->SetViewport(&viewport);

	// コマンドにたまっているものを描画
	_application->GetCommandBuffer()->Sort();
	_application->GetCommandProcessor()->ProccessDefault();
	_application->GetCommandProcessor()->ProccessField();
	_application->GetCommandProcessor()->ProccessBackGround();
	_application->GetCommandProcessor()->ProccessTranslucent();
	_application->GetCommandProcessor()->ProccessAIM();
	_application->GetCommandProcessor()->Proccess2D();
	_application->GetCommandBuffer()->Clear();
}
