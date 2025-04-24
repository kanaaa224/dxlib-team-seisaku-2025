#include "TitleScene.h"

#include "../Utility/ResourceManager.h"
#include "../Utility/InputCtrl.h"

#include "DxLib.h"

TitleScene::TitleScene():background_image1(NULL),
						background_image2(NULL),
						background_image3(NULL),
						background_image4(NULL){}
TitleScene::~TitleScene() {}

void TitleScene::Initialize()
{
	ResourceManager* rm = ResourceManager::GetInstance();

	background_image1 = LoadGraph("resource/images/stage/title/j1.png");
	background_image2 = LoadGraph("resource/images/stage/title/j2.png");
	background_image3 = LoadGraph("resource/images/stage/title/j3.png");
	background_image4 = LoadGraph("resource/images/stage/title/j4.png");

	return __super::Initialize();
}

eSceneType TitleScene::Update(const float& delta_second)
{
	if (InputCtrl::GetKeyState(KEY_INPUT_RETURN) || InputCtrl::GetButtonState(XINPUT_BUTTON_A)) return eSceneType::in_game;
	if (InputCtrl::GetKeyState(KEY_INPUT_1)) return eSceneType::debug_boss; // 島袋 デバッグ

	return __super::Update(delta_second);
}

void TitleScene::Draw() const
{
	//背景描画
	DrawGraph(0, 0, background_image4, TRUE);
	DrawGraph(0, 0, background_image3, TRUE);
	DrawGraph(0, 0, background_image2, TRUE);
	DrawGraph(0, 0, background_image1, TRUE);


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