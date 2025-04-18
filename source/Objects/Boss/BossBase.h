#pragma once

#include "../GameObject.h"

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
	void SetVelocity(float v);

	static BossBase* GetInstance();

private:
	void Movement(float delta_second);
	void Animation(float delta_second);
};