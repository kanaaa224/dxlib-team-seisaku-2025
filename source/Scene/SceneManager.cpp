#include "SceneManager.h"
#include "../Utility/ResourceManager.h"
#include "../Utility/ProjectConfig.h"

#include "../Utility/FPS.h"
#include "../Utility/InputCtrl.h"

#include "DxLib.h"

#include "TitleScene.h"
#include "InGameScene.h"
#include "DebugBossScene.h"

SceneBase* SceneManager::CreateScene(eSceneType next_type)
{
	switch (next_type) {
	case eSceneType::title:
		return dynamic_cast<SceneBase*>(new TitleScene());

	case eSceneType::in_game:
		return dynamic_cast<SceneBase*>(new InGameScene());

	case eSceneType::debug_boss:
		return dynamic_cast<SceneBase*>(new DebugBossScene());

	default:
		return nullptr;
	}
}

SceneManager::SceneManager() : current_scene(nullptr) {}

SceneManager::~SceneManager()
{
	Shutdown();
}

void SceneManager::WakeUp()
{
	ChangeWindowMode(TRUE);

	SetGraphMode(D_WIN_MAX_X, D_WIN_MAX_Y, D_COLOR_BIT);

	SetWindowText(D_APP_NAME);

	SetWaitVSyncFlag(FALSE);

#if DEBUG
	SetOutApplicationLogValidFlag(TRUE);
#else
	SetOutApplicationLogValidFlag(FALSE);
#endif

	if (DxLib_Init() == D_FAILURE) throw std::string("DxLibの初期化に失敗\n");

	SetDrawScreen(DX_SCREEN_BACK);

	ChangeScene(eSceneType::title);

	SetAlwaysRunFlag(TRUE);
}

void SceneManager::Run()
{
	FPS::SetLimitRate(D_FPS);
	FPS::SetUpdateInterval(1000);

	while (ProcessMessage() == D_SUCCESS) {
		if (GetMainWindowHandle() == GetForegroundWindow()) InputCtrl::Update();

		FPS::Limit();
		FPS::Update();

#if DEBUG
		if (InputCtrl::GetKeyState(KEY_INPUT_ESCAPE) || InputCtrl::GetButtonState(XINPUT_BUTTON_BACK)) break;

		if (InputCtrl::GetKeyState(KEY_INPUT_F) && InputCtrl::GetKeyState(KEY_INPUT_3)) FPS::SetLimitRate(30);
		if (InputCtrl::GetKeyState(KEY_INPUT_F) && InputCtrl::GetKeyState(KEY_INPUT_6)) FPS::SetLimitRate(60);
#endif

		FrameControl();

		eSceneType next_scene_type = current_scene->Update(GetDeltaSecond());

		Graph();

		if (next_scene_type == eSceneType::exit) break;

		if (current_scene->GetNowSceneType() != next_scene_type) ChangeScene(next_scene_type);
	}
}

void SceneManager::Shutdown()
{
	if (current_scene != nullptr) {
		current_scene->Finalize();

		delete current_scene;

		current_scene = nullptr;
	}

	ResourceManager::DeleteInstance();

	DxLib_End();
}

void SceneManager::Graph() const
{
	ClearDrawScreen();

	current_scene->Draw();

#if DEBUG
	SetFontSize(16);
	DrawFormatString(10, 10, GetColor(255, 255, 255), "FPS: %0.0f", FPS::Get());
#endif

	ScreenFlip();
}

void SceneManager::ChangeScene(eSceneType next_type)
{
	SceneBase* next_scene = CreateScene(next_type);

	if (next_scene == nullptr) throw ("シーン切り替えに失敗\n");

	if (current_scene != nullptr) {
		current_scene->Finalize();

		delete current_scene;
	}

	next_scene->Initialize();

	current_scene = next_scene;
}