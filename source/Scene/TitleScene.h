#pragma once

#include "SceneBase.h"

class TitleScene : public SceneBase
{
private:
	int background_image1;
	int background_image2;
	int background_image3;
	int background_image4;

	bool is_fading = false;
	float fade_alpha = 0.0f;
	eSceneType next_scene = eSceneType::title;

public:
	TitleScene();
	virtual ~TitleScene();

	virtual void Initialize() override;
	virtual eSceneType Update(const float& delta_second) override;
	virtual void Draw() const override;
	virtual void Finalize() override;

	virtual const eSceneType GetNowSceneType() const override;
};