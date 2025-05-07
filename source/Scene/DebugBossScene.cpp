#include "DebugBossScene.h"
#include "../Utility/InputCtrl.h"
#include "../Objects/Boss/Vaillant.h"
#include "DxLib.h"

DebugBossScene::DebugBossScene() {}

DebugBossScene::~DebugBossScene() {}

void DebugBossScene::Initialize()
{
	for (int i = 0; i < 3; i++) {
		float x, y;

		x = (i + 1) * 220.0f;
		y = 430;

		vaillants.push_back(CreateObject<Vaillant>(Vector2D(x, y)));
	}

	return __super::Initialize();
}

eSceneType DebugBossScene::Update(const float& delta_second)
{
	if (InputCtrl::GetKeyState(KEY_INPUT_0)) return eSceneType::title;

	return __super::Update(delta_second);
}

void DebugBossScene::Draw() const
{
	DrawBox(0, 0, 1280, 720, GetColor(100, 100, 100), true);

	return __super::Draw();
}

void DebugBossScene::Finalize()
{
	return __super::Finalize();
}

const eSceneType DebugBossScene::GetNowSceneType() const
{
	return eSceneType::debug_boss;
}