#pragma once

#include "SceneBase.h"

class DebugBossScene : public SceneBase
{
private:
	std::vector<class BossBase*> bosses;

public:
	DebugBossScene();
	virtual ~DebugBossScene();

	virtual void Initialize() override;
	virtual eSceneType Update(const float& delta_second) override;
	virtual void Draw() const override;
	virtual void Finalize() override;

	virtual const eSceneType GetNowSceneType() const override;
};