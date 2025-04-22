#pragma once

#include "../EnemyBase.h"

class Scarerun : public EnemyBase
{
public:
	Scarerun();
	~Scarerun();

	void Initialize() override;
	void Update(float delta_second) override;
	void Draw(const Vector2D& screen_offset) const override;
	void Finalize() override;

	void OnHitCollision(GameObjectBase* hit_object) override;

protected:
	//親クラスに実際の処理を書いている
	void Animation(float delta_second) override;
	//親クラスに実際の処理を書いている
	void SetEnemyState(eEnemyState setState) override { __super::SetEnemyState(setState); };
};

