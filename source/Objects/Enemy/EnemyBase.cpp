#include "EnemyBase.h"

EnemyBase::EnemyBase() : 
	move_img(), 
	attackPosition_img(),
	attack_img(),
	getAttack_img(),
	die_img()
{
}

EnemyBase::~EnemyBase()
{
}

void EnemyBase::Initialize()
{
}

void EnemyBase::Update(float delta_second)
{
	location += velocity;

	Vector2D collisionPosition = collision.GetPosition();

	collision.SetPosition(location);
}

void EnemyBase::Draw(const Vector2D& screen_offset) const
{
	__super::Draw(screen_offset);
}

void EnemyBase::Finalize()
{
}

void EnemyBase::OnHitCollision(GameObjectBase* hit_object)
{
}
