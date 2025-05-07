#include "BossBase.h"
#include "DxLib.h"

BossBase* BossBase::instance = nullptr;

BossBase::BossBase() : bossBase(nullptr) {}

BossBase::~BossBase() {}

void BossBase::Initialize()
{
	collision.is_blocking = true;
	collision.SetObjectType(eObjectType::enemy);
	collision.SetHitObjectType({ eObjectType::player, eObjectType::enemy, eObjectType::ground });
}

void BossBase::Update(float delta_second)
{
	location += velocity;

	collision.SetPosition(location);

	Animation(delta_second);
	Movement(delta_second);
}

void BossBase::Animation(float delta_second) {}

void BossBase::Movement(float delta_second) {}

void BossBase::OnHitCollision(GameObject* hit_object) {}

void BossBase::Draw(const Vector2D& screen_offset) const
{
	__super::Draw(screen_offset);
}

void BossBase::Finalize() {}

void BossBase::AddVelocity(const Vector2D& v)
{
	location -= v;
}

BossBase* BossBase::GetInstance()
{
	if (instance == nullptr) instance = new BossBase();

	return instance;
}