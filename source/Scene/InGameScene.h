﻿#pragma once

#include "SceneBase.h"

class InGameScene : public SceneBase
{
private:
	class Player* player;
	class Stage* stage;
	std::vector<class Scarerun*> scareruns;

public:
	InGameScene();
	virtual ~InGameScene();

	virtual void Initialize() override;
	virtual eSceneType Update(const float& delta_second) override;
	virtual void Draw() const override;
	virtual void Finalize() override;

	virtual const eSceneType GetNowSceneType() const override;
};