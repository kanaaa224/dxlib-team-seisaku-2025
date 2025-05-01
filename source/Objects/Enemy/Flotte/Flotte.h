#pragma once

#include "../EnemyBase.h"

class Flotte : public EnemyBase
{
public:
	Flotte();
	~Flotte();

	void Initialize() override;
	void Update(float delta_second) override;
	void Draw(const Vector2D& screen_offset) const override;
	void Finalize() override;

	void OnHitCollision(GameObjectBase* hit_object) override;

protected:
	//親クラスに実際の処理を書いている
	void Animation(float delta_second) override { __super::Animation(delta_second); };
	//親クラスに実際の処理を書いている
	void SetEnemyState(eEnemyState setState) override { __super::SetEnemyState(setState); };
	//
	void Movement(float distance) override;

	void InitUpdate() override { __super::InitUpdate(); };
};

