#include "BossBase.h"
#include "DxLib.h"

BossBase* BossBase::instance = nullptr;

BossBase::BossBase() :
	velocity(0.0f),
	state(0),
	bossBase(nullptr),
	bossBase_state(eBossBaseState::idle) {}

BossBase::~BossBase() {}

void BossBase::Initialize()
{
	float size = D_OBJECT_SIZE * 4;

	collision.is_blocking = true;
	collision.SetSize(size, size);
	//collision.pivot = Vector2D(6.0f);
	collision.SetObjectType(eObjectType::enemy);
	collision.SetHitObjectType({ eObjectType::player, eObjectType::enemy, eObjectType::ground });


	SetDrawCollisionBox(true);
}

void BossBase::Update(float delta_second)
{
	//Animation(delta_second);

	Movement(delta_second);

	location += velocity;

	Vector2D collisionPosition = collision.GetPosition();

	collision.SetPosition(location);
}

void BossBase::Draw(const Vector2D& screen_offset) const
{
	DrawBox(location.x, location.y, location.x, location.y, GetColor(255, 255, 255), false);

	__super::Draw(screen_offset);
}

void BossBase::Finalize() {}

void BossBase::OnHitCollision(GameObject* hit_object)
{
	if (hit_object->GetCollision().object_type == eObjectType::player) owner_scene->DestroyObject(this);
}

void BossBase::Animation(float delta_second)
{
	switch (bossBase_state)
	{
	case eBossBaseState::idle:
	case eBossBaseState::move:
	case eBossBaseState::damage:
	case eBossBaseState::die:
		break;

	default:
		break;
	}
}

void BossBase::Movement(float delta_second)
{
	//velocity.x = -0.1;
}

BossBase* BossBase::GetInstance()
{
	if (instance == nullptr) instance = new BossBase();

	return instance;
}

void BossBase::SetVelocity(float v)
{
	location.x -= v;
}