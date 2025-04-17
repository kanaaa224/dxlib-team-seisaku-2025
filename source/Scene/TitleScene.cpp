#include "TitleScene.h"

#include "../Utility/ResourceManager.h"
#include "../Utility/InputCtrl.h"

#include "DxLib.h"

TitleScene::TitleScene() {}
TitleScene::~TitleScene() {}

void TitleScene::Initialize()
{
	ResourceManager* rm = ResourceManager::GetInstance();

	return __super::Initialize();
}

eSceneType TitleScene::Update(const float& delta_second)
{
	if (InputCtrl::GetKeyState(KEY_INPUT_RETURN) || InputCtrl::GetButtonState(XINPUT_BUTTON_A)) return eSceneType::in_game;;

	return __super::Update(delta_second);
}

void TitleScene::Draw() const
{
	SetFontSize(16);

	DrawFormatString(10, 40, GetColor(255, 255, 255), "This is the Title.");
	DrawFormatString(10, 60, GetColor(255, 255, 255), "Press Enter or A button: GameMain");

	return __super::Draw();
}

void TitleScene::Finalize()
{
	return __super::Finalize();
}

const eSceneType TitleScene::GetNowSceneType() const
{
	return eSceneType::title;
}