#pragma once

#include "../GameObject.h"
#include "../../Utility/Vector2D.h"

enum class eBossBaseState
{
	idle,
	move,
	damage,
	die
};

class BossBase : public GameObject
{
private:
	Vector2D velocity;

	std::vector<int> idle_animation;

	const int animation_nums[2] = { 0, 1 };

	int animation_count;

	float animation_time;

	int state;

	BossBase* bossBase;

	static BossBase* instance;

public:
	eBossBaseState bossBase_state;

public:
	BossBase();
	~BossBase();

	virtual void Initialize() override;
	virtual void Update(float delta_second) override;
	virtual void Draw(const Vector2D& screen_offset) const override;
	virtual void Finalize() override;

	virtual void OnHitCollision(GameObject* hit_object);

public:
	void SetVelocity(float velo);

	static BossBase* GetInstance();

private:
	void Movement(float delta_second);
	void Animation(float delta_second);
};