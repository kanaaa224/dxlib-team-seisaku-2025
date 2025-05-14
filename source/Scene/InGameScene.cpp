#include "InGameScene.h"
#include "../Utility/ResourceManager.h"
#include "../Utility/InputCtrl.h"
#include "../Utility/ProjectConfig.h"
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

	for (int i = 0; i < 50; i++) {
		float x, y;

		x = (i + 1) * 25.0f;
		y = 430;

		scareruns.push_back(CreateObject<Scarerun>(Vector2D(x, y)));
	}

	//ui初期化処理
	GameUI* gameui = GameUI::GetInstance();
	gameui->Initialize();

	return __super::Initialize();
}

eSceneType InGameScene::Update(const float& delta_second)
{

	__super::Update(delta_second);

	if ((player->GetLocation().x >= (D_WIN_MAX_X / 2) || player->GetLocation().x <= 100.0f)/* && stage->GetLocation().x <= (D_WIN_MAX_X / 2)*/)
	{
		Vector2D v = player->GetVelocity();

		stage->AddVelocity(Vector2D(v.x, 0.0f));

		for (int i = 0; i < scareruns.size(); i++) {
			scareruns[i]->AddVelocity(Vector2D(v.x, 0.0f));
		}

		v = player->GetLocation() - player->GetVelocity();

		player->SetLocation(Vector2D(v.x, player->GetLocation().y));
	}
	if (player->player_state == die)
	{
		//DestroyObject(player);
	}

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