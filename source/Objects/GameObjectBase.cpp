#include "GameObjectBase.h"
#include "../Scene/SceneBase.h"
#include "DxLib.h"

GameObjectBase::GameObjectBase() :
	owner_scene(nullptr),
	location(0.0f),
	image(NULL),
	z_layer(0),
	mobility(eMobilityType::stationary),
	velocity(0),
	flip_flag(false),
	draw_collision_box(false) {}

GameObjectBase::~GameObjectBase() {}

void GameObjectBase::Initialize() {}

void GameObjectBase::Update(float delta_second) {}

void GameObjectBase::Draw(const Vector2D& screen_offset) const
{
	Vector2D graph_location = this->location + screen_offset;

	DrawRotaGraphF(graph_location.x, graph_location.y, 1.0, 0.0, image, TRUE, this->flip_flag);

	DrawCollision(screen_offset);
}

void GameObjectBase::DrawCollision(const Vector2D& screen_offset) const
{
	if (draw_collision_box) {
		Vector2D min = collision.GetPosition() - (collision.box_size / 2) + collision.pivot + screen_offset;
		Vector2D max = collision.GetPosition() + (collision.box_size / 2) + collision.pivot + screen_offset;

		DrawBoxAA(min.x, min.y, max.x, max.y, GetColor(255, 255, 255), false);
	}
}

void GameObjectBase::Finalize() {}

void GameObjectBase::OnHitCollision(GameObjectBase* hit_object) {}

eCollisionSide GameObjectBase::GetCollisionSide(const GameObjectBase& other) const
{
	Vector2D thisMin = collision.GetPosition() - (collision.box_size / 2) + collision.pivot;
	Vector2D thisMax = collision.GetPosition() + (collision.box_size / 2) + collision.pivot;

	Vector2D otherMin = other.collision.GetPosition() - (other.collision.box_size / 2) + other.collision.pivot;
	Vector2D otherMax = other.collision.GetPosition() + (other.collision.box_size / 2) + other.collision.pivot;

	float leftOverlap = otherMax.x - thisMin.x;
	float rightOverlap = thisMax.x - otherMin.x;
	float topOverlap = otherMax.y - thisMin.y;
	float bottomOverlap = thisMax.y - otherMin.y;

	if (leftOverlap <= 0.0f || rightOverlap <= 0.0f || topOverlap <= 0.0f || bottomOverlap <= 0.0f) return eCollisionSide::none;

	if (topOverlap < bottomOverlap && topOverlap < leftOverlap && topOverlap < rightOverlap) {
		return eCollisionSide::bottom;
	}
	else if (bottomOverlap < topOverlap && bottomOverlap < leftOverlap && bottomOverlap < rightOverlap) {
		return eCollisionSide::top;
	}
	else if (leftOverlap < rightOverlap) {
		return eCollisionSide::right;
	}
	else {
		return eCollisionSide::left;
	}
}

void GameObjectBase::SetOwnerScene(SceneBase* scene)
{
	this->owner_scene = scene;
}

const Vector2D& GameObjectBase::GetLocation() const
{
	return location;
}

void GameObjectBase::SetLocation(const Vector2D& location)
{
	this->location = location;
}

Collision GameObjectBase::GetCollision() const
{
	return collision;
}

const int GameObjectBase::GetZLayer() const
{
	return z_layer;
}

const eMobilityType GameObjectBase::GetMobility() const
{
	return mobility;
}

void GameObjectBase::SetDrawCollisionBox(bool flag)
{
	draw_collision_box = flag;
}