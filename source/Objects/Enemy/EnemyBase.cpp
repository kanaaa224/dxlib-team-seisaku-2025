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
}

void EnemyBase::Draw(const Vector2D& screen_offset) const
{
}

void EnemyBase::Finalize()
{
}

void EnemyBase::OnHitCollision(GameObjectBase* hit_object)
{
}
