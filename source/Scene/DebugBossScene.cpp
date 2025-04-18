#include "DebugBossScene.h"
#include "../Utility/InputCtrl.h"
#include "../Objects/Boss/BossBase.h"
#include "DxLib.h"

DebugBossScene::DebugBossScene() {}

DebugBossScene::~DebugBossScene() {}

void DebugBossScene::Initialize()
{
	for (int i = 0; i < 3; i++) {
		float x, y;

		x = (i + 1) * 100 + 200;
		y = 430;

		bosses.push_back(CreateObject<BossBase>(Vector2D(x, y)));
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
	DrawBox(0, 200, 1280, 520, GetColor(100, 100, 100), true);

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