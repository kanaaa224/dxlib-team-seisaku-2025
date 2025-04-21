#include "Vaillant.h"
#include "DxLib.h"

Vaillant::Vaillant() {}

Vaillant::~Vaillant() {}

void Vaillant::Initialize()
{
	float size = D_OBJECT_SIZE * 4;

	collision.SetSize(size, size);
	//collision.pivot = Vector2D(6.0f);

	SetDrawCollisionBox(true);

	__super::Initialize();
}

void Vaillant::Update(float delta_second)
{
	__super::Update(delta_second);
}

void Vaillant::Animation(float delta_second)
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

	__super::Animation(delta_second);
}

void Vaillant::Movement(float delta_second)
{
	//velocity.x = -0.1;

	__super::Movement(delta_second);
}

void Vaillant::OnHitCollision(GameObject* hit_object)
{
	__super::OnHitCollision(hit_object);
}

void Vaillant::Draw(const Vector2D& screen_offset) const
{
	DrawBox(location.x, location.y, location.x, location.y, GetColor(255, 255, 255), false);

	__super::Draw(screen_offset);
}

void Vaillant::Finalize() 
{
	__super::Finalize();
}