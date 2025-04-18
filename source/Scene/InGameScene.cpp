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

	hp_ber = LoadGraph("resource/images/ui/hp_bar_back.png");
	if (hp_ber == -1)
	{
		throw("resource/images/ui/hp_bar_back.pngがありません\n");
	}

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

	DrawFormatString(10, 40, GetColor(255, 255, 255), "This is the GameMain.");

	//HPフレーム表示

	//HPバー表示

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