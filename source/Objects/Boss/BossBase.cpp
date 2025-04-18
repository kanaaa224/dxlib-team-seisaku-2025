#include "BossBase.h"
#include "../../Utility/ResourceManager.h"
#include "DxLib.h"

BossBase* BossBase::instance = nullptr;

BossBase::BossBase() :
	velocity(0.0f),
	idle_animation(),
	animation_count(0),
	animation_time(0.0f),
	state(0),
	bossBase(nullptr),
	bossBase_state(eBossBaseState::idle) {}

BossBase::~BossBase() {}

void BossBase::Initialize()
{
	ResourceManager* rm = ResourceManager::GetInstance();

	idle_animation = rm->GetImages("resource/images/boss/boss1/idle/dark fantasy big boss idle.png", 16, 16, 1, 64, 64);

	image = idle_animation[0];

	if (image == -1) throw("アセットのロードに失敗\n");


	collision.is_blocking = true;
	collision.SetSize(D_OBJECT_SIZE + 10, D_OBJECT_SIZE + 10);
	collision.pivot = Vector2D(6.0f);
	collision.SetObjectType(eObjectType::enemy);
	collision.SetHitObjectType({ eObjectType::player, eObjectType::enemy, eObjectType::ground });


	//SetDrawCollisionBox(true);
}

void BossBase::Update(float delta_second)
{
	//velocity.x = -0.1;

	location += velocity;

	Vector2D collisionPosition = collision.GetPosition();

	collision.SetPosition(location);

	//Animation(delta_second);
}

void BossBase::Draw(const Vector2D& screen_offset) const
{
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
		animation_time += delta_second;

		if (animation_time >= (1.0f / 8.0f)) {
			animation_time = 0.0f;

			animation_count++;

			if (animation_count >= 16) animation_count = 0;

			image = idle_animation[/*animation_nums[*/animation_count/*]*/];
		}

		break;

	default:
		break;
	}
}

void BossBase::Movement(float delta_second) {}

BossBase* BossBase::GetInstance()
{
	if (instance == nullptr) instance = new BossBase();

	return instance;
}

void BossBase::SetVelocity(float v)
{
	location.x -= v;
}