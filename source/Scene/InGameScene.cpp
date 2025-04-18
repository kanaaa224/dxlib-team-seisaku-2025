#include "InGameScene.h"

#include "../Utility/ResourceManager.h"
#include "../Utility/InputCtrl.h"

#include "../Objects/Player.h"

#include "DxLib.h"

InGameScene::InGameScene() : hp_ber(NULL),hp_frame(NULL){}

InGameScene::~InGameScene() {}

void InGameScene::Initialize()
{
	ResourceManager* rm = ResourceManager::GetInstance();

	hp_ber = LoadGraph("resource/images/ui/hp_bar_backA.png");
	hp_frame = LoadGraph("resource/images/ui/hp_frameA.png");
	

	player = CreateObject<Player>(Vector2D(100, 403));

	return __super::Initialize();
}

eSceneType InGameScene::Update(const float& delta_second)
{
	return __super::Update(delta_second);
}

void InGameScene::Draw() const
{
	SetFontSize(16);

	DrawFormatString(10, 400, GetColor(255, 255, 255), "This is the GameMain.");

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