#include "GameUI.h"
#include "DxLib.h"

// 静的メンバ変数定義 nullptrで初期化
GameUI* GameUI::instance = nullptr;

GameUI::GameUI() : hp_ber(NULL), hp_frame(NULL)
{
}

GameUI::~GameUI()
{
}

void GameUI::Initialize()
{
	hp_ber = LoadGraph("resource/images/ui/hp_bar_backA.png");
	hp_frame = LoadGraph("resource/images/ui/hp_frameA.png");

	if (hp_ber == -1)
	{
		printf("画像がないよ！\n");
	}
}

void GameUI::Update()
{
}

void GameUI::Draw()
{

	//HPフレーム表示
	DrawGraph(25, 30, hp_frame, FALSE);
	//HPバー表示
	DrawGraph(20, 40, hp_ber, FALSE);
}

void GameUI::Finalize()
{
}

GameUI* GameUI::GetInstance()
{
	if (instance == nullptr)
	{
		instance = new GameUI();
	}
	return instance;
}
