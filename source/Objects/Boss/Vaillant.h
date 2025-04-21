#pragma once

#include "BossBase.h"

class Vaillant : public BossBase
{
public:
	Vaillant();
	~Vaillant();

	virtual void Initialize() override;
	virtual void Update(float delta_second) override;
	virtual void Draw(const Vector2D& screen_offset) const override;
	virtual void Finalize() override;

	virtual void OnHitCollision(GameObject* hit_object) override;

private:
	virtual void Animation(float delta_second) override;
	virtual void Movement(float delta_second) override;
};