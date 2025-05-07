#pragma once

#include "BossBase.h"

enum class VaillantState
{
	idle,
	walk,
	damage,
	die
};

class Vaillant : public BossBase
{
private:
	std::vector<int> idle_images;
	std::vector<int> walk_images;

	int idle_animation_state;
	int walk_animation_state;

	float idle_animation_time;
	float walk_animation_time;

	VaillantState state;

	float debug[2];

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