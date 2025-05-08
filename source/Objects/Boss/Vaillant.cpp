#include "Vaillant.h"
#include "../../Utility/InputCtrl.h"
#include "../../Utility/ResourceManager.h"
#include "DxLib.h"

Vaillant::Vaillant() :
	idle_animation_state(0),
	walk_animation_state(0),
	idle_animation_time(0.0f),
	walk_animation_time(0.0f),
	state(VaillantState::idle) {}

Vaillant::~Vaillant() {}

void Vaillant::Initialize()
{
	__super::Initialize();

	ResourceManager* rm = ResourceManager::GetInstance();

	std::string base_path = "resource/images/enemy_boss/vaillant";

	idle_images = rm->GetImages((base_path + "/idle.png").c_str(), 16, 16, 1, 450, 360);
	walk_images = rm->GetImages((base_path + "/walk.png").c_str(), 16, 16, 1, 450, 360);

	image = idle_images[idle_animation_state];

	img_size = Vector2D(200.0f, 220.0f);

	collision.radius = 80.0f;

#ifdef DEBUG
	SetDrawCollisionBox(true);
	SetDarwCollisionCapsule(true);
#endif
}

void Vaillant::Update(float delta_second)
{
	__super::Update(delta_second);

	if (true) {
		debug[0] += delta_second * (60.0f / GetFPS());

		if (debug[0] >= 1.0f) {
			debug[0] = 0.0f;

			debug[1] = GetRand(10);

			velocity = 0.0f;
		}

		if (debug[1] > 0 && debug[1] <= 3) velocity.x = -0.25f;
		if (debug[1] > 3 && debug[1] <= 7) velocity.x =  0.25f;

		if (debug[1] == 8) flip_flag = true;
		if (debug[1] == 9) flip_flag = false;
	}

	collision.SetStartPoint(Vector2D(location.x, location.y - (img_size.y / 2.0f)));
	collision.SetEndPoint(Vector2D(location.x, location.y + (img_size.y / 2.0f)));

	if (flip_flag) {
		collision.SetSize(200.0f, 220.0f);
		collision.pivot = Vector2D(12.0f, 27.0f);
	}
	else {
		collision.SetSize(200.0f, 220.0f);
		collision.pivot = Vector2D(-12.0f, 27.0f);
	}

	if ((velocity.x == 0.0f) && (velocity.y == 0.0f)) state = VaillantState::idle;
	else state = VaillantState::walk;
}

void Vaillant::Animation(float delta_second)
{
	__super::Animation(delta_second);

	switch (state)
	{
	case VaillantState::idle:
		idle_animation_time += delta_second * (60.0f / GetFPS());

		if (idle_animation_time >= 0.075f) {
			idle_animation_time = 0.0f;

			if (idle_animation_state >= 15) idle_animation_state = 0;
			else idle_animation_state++;

			image = idle_images[idle_animation_state];
		}

		break;

	case VaillantState::walk:
		walk_animation_time += delta_second * (60.0f / GetFPS());

		if (walk_animation_time >= 0.1f) {
			walk_animation_time = 0.0f;

			if (walk_animation_state >= 15) walk_animation_state = 0;
			else walk_animation_state++;

			image = walk_images[walk_animation_state];
		}

		if (velocity.x > 0.0f) flip_flag = false;
		if (velocity.x < 0.0f) flip_flag = true;

		break;

	case VaillantState::damage:
	case VaillantState::die:
		break;

	default:
		break;
	}
}

void Vaillant::Movement(float delta_second)
{
	__super::Movement(delta_second);

#ifdef DEBUG
	if (InputCtrl::GetKeyState(KEY_INPUT_A)) velocity.x = -0.25f;
	if (InputCtrl::GetKeyState(KEY_INPUT_D)) velocity.x =  0.25f;
#endif
}

void Vaillant::OnHitCollision(GameObject* hit_object)
{
	__super::OnHitCollision(hit_object);

	if (hit_object->GetCollision().object_type == eObjectType::player) owner_scene->DestroyObject(this);
}

void Vaillant::Draw(const Vector2D& screen_offset) const
{
	__super::Draw(screen_offset);
}

void Vaillant::Finalize() 
{
	__super::Finalize();

	//ResourceManager* rm = ResourceManager::GetInstance();

	//rm->UnLoadImages();

	idle_images.clear();
	walk_images.clear();
}