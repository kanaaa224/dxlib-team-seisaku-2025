#include "InGameScene.h"
#include "../Utility/ResourceManager.h"
#include "../Utility/InputCtrl.h"
#include "../Objects/Player.h"
#include "../Objects/Stage.h"
#include "../Objects/Enemy/Scarerun/Scarerun.h"
#include "GameUI.h"
#include "DxLib.h"

InGameScene::InGameScene() : player(NULL), stage(NULL){}

InGameScene::~InGameScene() {}

void InGameScene::Initialize()
{
	ResourceManager* rm = ResourceManager::GetInstance();
	
	player = CreateObject<Player>(Vector2D(100, 400));
	stage  = CreateObject<Stage>(Vector2D(640, 360));

	scareruns.push_back(CreateObject<Scarerun>(Vector2D(200,400)));

	//ui初期化処理
	GameUI* gameui = GameUI::GetInstance();
	gameui->Initialize();

	return __super::Initialize();
}

eSceneType InGameScene::Update(const float& delta_second)
{

	__super::Update(delta_second);

	return GetNowSceneType();
}

void InGameScene::Draw() const
{

	__super::Draw();

	//UIのインスタンスを取得
	GameUI* gameui = GameUI::GetInstance();
	//描画処理呼び出し
	gameui->Draw();
	
}

void InGameScene::Finalize()
{
	return __super::Finalize();
}

const eSceneType InGameScene::GetNowSceneType() const
{
	return eSceneType::in_game;
}