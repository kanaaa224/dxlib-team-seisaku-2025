#include "InGameScene.h"

#include "../Utility/ResourceManager.h"
#include "../Utility/InputCtrl.h"

//#include "../Objects/Player.h"

#include "DxLib.h"

InGameScene::InGameScene() {}
InGameScene::~InGameScene() {}

void InGameScene::Initialize()
{
	ResourceManager* rm = ResourceManager::GetInstance();

	//player = CreateObject<Player>(Vector2D(100, 403));

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