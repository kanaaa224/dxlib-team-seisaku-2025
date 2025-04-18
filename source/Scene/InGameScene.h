#pragma once

#include "SceneBase.h"

class InGameScene : public SceneBase
{
private:
	class Player* player;

	int hp_ber;     //HPバー
	int hp_frame;   //HPフレーム

public:
	InGameScene();
	virtual ~InGameScene();

	virtual void Initialize() override;
	virtual eSceneType Update(const float& delta_second) override;
	virtual void Draw() const override;
	virtual void Finalize() override;

	virtual const eSceneType GetNowSceneType() const override;
};