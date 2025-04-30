#include "TitleScene.h"

#include "../Utility/ResourceManager.h"
#include "../Utility/ProjectConfig.h"
#include "../Utility/InputCtrl.h"

#include "DxLib.h"

TitleScene::TitleScene() :background_image1(NULL),
background_image2(NULL),
background_image3(NULL),
background_image4(NULL) {}
TitleScene::~TitleScene() {}

void TitleScene::Initialize()
{
	ResourceManager* rm = ResourceManager::GetInstance();

	background_image1 = LoadGraph("resource/images/title/j1.png");
	background_image2 = LoadGraph("resource/images/title/j2.png");
	background_image3 = LoadGraph("resource/images/title/j3.png");
	background_image4 = LoadGraph("resource/images/title/j4.png");

	if (AddFontResourceEx("resource/fonts/PressStart2P-Regular.ttf", FR_PRIVATE, NULL) <= 0) throw;

	return __super::Initialize();
}

eSceneType TitleScene::Update(const float& delta_second)
{
	if (!is_fading)
	{
		if (InputCtrl::GetKeyState(KEY_INPUT_RETURN) || InputCtrl::GetButtonState(XINPUT_BUTTON_A))
		{
			is_fading = true;
			next_scene = eSceneType::in_game;
		}
		else if (InputCtrl::GetKeyState(KEY_INPUT_1))
		{
			is_fading = true;
			next_scene = eSceneType::debug_boss;
		}
	}
	else
	{
		// フェード処理（1秒で255まで増加）
		fade_alpha += 255.0f * delta_second;
		if (fade_alpha >= 255.0f)
		{
			fade_alpha = 255.0f;
			return next_scene;
		}
	}

	return __super::Update(delta_second);
}


void TitleScene::Draw() const
{
	// 背景描画（逆順で描画）
	DrawExtendGraph(0, 0, D_WIN_MAX_X, D_WIN_MAX_Y, background_image4, TRUE);
	DrawExtendGraph(0, 0, D_WIN_MAX_X, D_WIN_MAX_Y, background_image3, TRUE);
	DrawExtendGraph(0, 0, D_WIN_MAX_X, D_WIN_MAX_Y, background_image2, TRUE);
	DrawExtendGraph(0, 0, D_WIN_MAX_X, D_WIN_MAX_Y, background_image1, TRUE);

	// 文字描画
	ChangeFont("Press Start 2P", DX_CHARSET_DEFAULT);
	SetFontSize(65);
	DrawFormatString(440, 150, GetColor(255, 255, 255), "Temple");
	DrawFormatString(130, 500, GetColor(255, 255, 255), "Please A button");

	SetFontSize(16);
	DrawFormatString(10, 40, GetColor(255, 255, 255), "This is the Title.");
	DrawFormatString(10, 60, GetColor(255, 255, 255), "Press Enter or A button: GameMain");
	ChangeFont("");

	// フェード用の黒い矩形
	if (is_fading)
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, static_cast<int>(fade_alpha));
		DrawBox(0, 0, D_WIN_MAX_X, D_WIN_MAX_Y, GetColor(0, 0, 0), TRUE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}

	return __super::Draw();
}


void TitleScene::Finalize()
{
	RemoveFontResourceEx("resource/fonts/PressStart2P-Regular.ttf", FR_PRIVATE, NULL);

	return __super::Finalize();
}

const eSceneType TitleScene::GetNowSceneType() const
{
	return eSceneType::title;
}