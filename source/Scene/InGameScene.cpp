#include "InGameScene.h"
#include "../Utility/ResourceManager.h"
#include "../Utility/InputCtrl.h"
#include "../Objects/Player.h"
#include "../Objects/Stage.h"
#include "../Objects/Enemy/Scarerun/Scarerun.h"
#include "DxLib.h"

InGameScene::InGameScene() : player(NULL), stage(NULL), hp_ber(NULL), hp_frame(NULL) {}

InGameScene::~InGameScene() {}

void InGameScene::Initialize()
{
	ResourceManager* rm = ResourceManager::GetInstance();

	hp_ber   = LoadGraph("resource/images/ui/hp_bar_backA.png");
	hp_frame = LoadGraph("resource/images/ui/hp_frameA.png");
	
	player = CreateObject<Player>(Vector2D(100, 400));
	stage  = CreateObject<Stage>(Vector2D(640, 360));

	scareruns.push_back(CreateObject<Scarerun>(Vector2D(200,400)));

	return __super::Initialize();
}

eSceneType InGameScene::Update(const float& delta_second)
{
	return __super::Update(delta_second);
}

void InGameScene::Draw() const
{
	//HPフレーム表示
	DrawGraph(25, 30, hp_frame, FALSE);

	//HPバー表示
	DrawGraph(20, 40, hp_ber, FALSE);

	return __super::Draw();
}

void InGameScene::Finalize()
{
	return __super::Finalize();
}

const eSceneType InGameScene::GetNowSceneType() const
{
	return eSceneType::in_game;
}