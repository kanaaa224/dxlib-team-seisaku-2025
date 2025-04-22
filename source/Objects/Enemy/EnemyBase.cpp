#include "EnemyBase.h"

EnemyBase::EnemyBase() : 
	idle_img(), 
	attackPosition_img(),
	attack_img(),
	getAttack_img(),
	die_img(),
	nowState(eEnemyState::IDLE),
	nowStateTime(0.0f),
	fov_BoxSize(Vector2D(0.0f)),
	playerFoundFlg(false)
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

void EnemyBase::Animation(float delta_second)
{
	switch (nowState)
	{
	case IDLE:
		
		break;
	case ATTACK_POSITION:
		break;
	case ATTACK:
		break;
	case GET_ATTACK:
		break;
	case DIE:
		break;
	default:
		break;
	}
}
