#include "Collision.h"
#include <math.h>

float Collision::CalcSegmentSegmentDist(const Vector2D& other_pivot, const float& other_boxSize_y)
{
	Vector2D a, b;
	a = this->pivot + (box_size.y / 2);
	b = other_pivot + (other_boxSize_y / 2);

	//チェック１(垂線を引いて比のベクトルが０～１の範囲か？)
	float m = Vector2D::Dot(a, b) / sqrtf(a.Length());
	Vector2D mp = a * m;

	return mp.Length();
}

Collision::Collision() :
	is_blocking(false),
	object_type(eObjectType::none),
	hit_object_type(),
	position(0)
{}

Collision::~Collision() {}

void Collision::SetPosition(const Vector2D& pos)
{
	position = pos;
}

const Vector2D& Collision::GetPosition() const
{
	return position;
}

void Collision::SetSize(const float& width, const float& height)
{
	box_size.x = width;
	box_size.y = height;
}

Vector2D Collision::GetSize()
{
	return box_size;
}

void Collision::SetObjectType(const eObjectType& FUNC_objecttype)
{
	object_type = FUNC_objecttype;
}

void Collision::SetHitObjectType(const std::vector<eObjectType>& FUNC_hitobjecttype)
{
	hit_object_type = FUNC_hitobjecttype;
}

bool Collision::IsCheckHitTarget(eObjectType FUNC_hitobject) const
{
	for (eObjectType type : hit_object_type) {
		if (type == FUNC_hitobject) return true;
	}

	return false;
}

bool Collision::CheckCollision(const Collision& other) const
{
	//Objectが当たり判定をONにしているか？
	if (other.is_blocking == false) {
		return false;
	}

	//下のコードは円で当たり判定を取る(カプセルで計算するコードができ次第消す)
	Vector2D a = this->GetPosition();
	Vector2D b = other.GetPosition();

	float tmp = sqrtf(pow(b.x - a.x, 2) + pow(b.y - a.y, 2));

	if (tmp <= this->radius + other.radius) {
		return true;
	}
	return false;

	//カプセルで計算するコードの試し（未完成）
	/*Vector2D a = this->GetPosition() + (box_size.y / 2);
	Vector2D b = other.GetPosition() + (other.box_size.y / 2);

	float m = Vector2D::Dot(a, b) / pow(a.Length(),2);
	Vector2D mp = a * m;

	if (m <= 1.0f) {
		return true;
	}
	return false;*/
}