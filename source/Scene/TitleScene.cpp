﻿#include "TitleScene.h"

#include "../Utility/ResourceManager.h"
#include "../Utility/ProjectConfig.h"
#include "../Utility/InputCtrl.h"

#include "DxLib.h"

TitleScene::TitleScene() :background_image1(NULL),
background_image2(NULL),
background_image3(NULL),
background_image4(NULL){}
TitleScene::~TitleScene() {}

void TitleScene::Initialize()
{
	ResourceManager* rm = ResourceManager::GetInstance();

	//背景
	background_image1 = LoadGraph("resource/images/title/j1.png");
	background_image2 = LoadGraph("resource/images/title/j2.png");
	background_image3 = LoadGraph("resource/images/title/j3.png");
	background_image4 = LoadGraph("resource/images/title/j4.png");

	//フォント
	if (AddFontResourceEx("resource/fonts/PressStart2P-Regular.ttf", FR_PRIVATE, NULL) <= 0) throw;

	//SE
	kettei = LoadSoundMem("resource/sounds/decision_button.mp3");
	ChangeVolumeSoundMem(250,kettei);

	return __super::Initialize();
}

eSceneType TitleScene::Update(const float& delta_second)
{
	//フェード中の処理
	if (is_fading)
	{
		//フェード中ボタンが押されたら即遷移_SPACEまたはBボタン
		//0以外の判定取っちゃうから押した瞬間（1）の判定の時にする
		if (InputCtrl::GetKeyState(KEY_INPUT_RETURN) == 1 || InputCtrl::GetButtonState(XINPUT_BUTTON_B))
		{
			fade_alpha = 255.0f;
			return next_scene;
		}

		// フェード処理
		fade_alpha += 255.0f * delta_second;
		if (fade_alpha >= 255.0f)
		{
			fade_alpha = 255.0f;
			return next_scene;
		}
	}
	//フェードしてないときの処理
	else
	{
		if (InputCtrl::GetKeyState(KEY_INPUT_RETURN) || InputCtrl::GetButtonState(XINPUT_BUTTON_A))
		{
			// 決定音
			PlaySoundMem(kettei, DX_PLAYTYPE_NORMAL);
			is_fading = true;
			fade_alpha = 0.0f;
			next_scene = eSceneType::in_game;
		}
		else if (InputCtrl::GetKeyState(KEY_INPUT_1))
		{
			is_fading = true;
			next_scene = eSceneType::debug_boss;
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

	DrawFormatString(1000, 10, GetColor(255, 255, 255), "%f",fade_alpha);

	DrawFormatString(10, 100, GetColor(0, 255, 255), "エンター二回押したらスキップされます");
}


void TitleScene::Finalize()
{
	RemoveFontResourceEx("resource/fonts/PressStart2P-Regular.ttf", FR_PRIVATE, NULL);

	// サウンドハンドルの削除
	DeleteSoundMem(kettei);

	return __super::Finalize();
}

const eSceneType TitleScene::GetNowSceneType() const
{
	return eSceneType::title;
}