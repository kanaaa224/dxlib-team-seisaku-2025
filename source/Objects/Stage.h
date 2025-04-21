#pragma once

#include "GameObject.h"
#include "../Utility/Vector2D.h"

class Stage : public GameObject
{
private:

	std::vector<int> stage_background;

	int draw_count;

public:

	Stage();

	~Stage();


	virtual void Initialize() override;

	virtual void Update(float delta_second) override;

	virtual void Draw(const Vector2D& screen_offset) const override;

	virtual void Finalize() override;

	virtual void OnHitCollision(GameObjectBase* hit_object) override;
};


