#include "InGameScene.h"

#include "../Utility/ResourceManager.h"
#include "../Utility/InputCtrl.h"

#include "DxLib.h"

InGameScene::InGameScene() {}
InGameScene::~InGameScene() {}

void InGameScene::Initialize()
{
	ResourceManager* rm = ResourceManager::GetInstance();
}

eSceneType InGameScene::Update(const float& delta_second)
{
	return __super::Update(delta_second);
}

void InGameScene::Draw() const
{
	SetFontSize(16);

	DrawFormatString(10, 40, GetColor(255, 255, 255), "This is the GameMain.");
}

void InGameScene::Finalize()
{
	__super::Finalize();
}

const eSceneType InGameScene::GetNowSceneType() const
{
	return eSceneType::in_game;
}