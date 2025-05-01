#include "Collision.h"
#include <math.h>

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
	/*Vector2D vecA = this->GetPosition();
	Vector2D Vecb = other.GetPosition();

	float tmp = sqrtf(pow(Vecb.x - vecA.x, 2) + pow(Vecb.y - vecA.y, 2));

	if (tmp <= this->radius + other.radius) {
		return true;
	}
	return false;*/

	//カプセルで計算する
	//線分ベクトル
	Vector2D u = this->endPoint - this->startPoint;  //カプセルAの方向ベクトル
	Vector2D v = other.endPoint - this->startPoint;  //カプセルBの方向ベクトル
	Vector2D w = this->startPoint - other.startPoint;//始点同士の差ベクトル

	//スカラー値の計算
	float a = u.Dot(u);
	float b = u.Dot(v);
	float c = v.Dot(v);
	float d = u.Dot(w);
	float e = v.Dot(w);

	//
	float denom = a * c - b * b;

	float s, t;//線分上の最近傍点のパラメータ

	if (denom == 0.0f) {
		//線分がほぼ平行→とりあえずAの始点を使う
		s = 0.0f;
	}
	else {
		//線分A上のパラメータｓを求めて[0,1]に制限
		s = fmax(0.0f, fmin(1.0f, (b * e - c * d) / denom));//クランプ
	}

	//線分B上の対応するｔを計算し、[0,1]に制限
	if (c != 0.0f) {
		t = (b * s + e) / c;
		t = fmax(0.0f, fmin(1.0f, t));
	}
	else {
		//Bが点
		t = 0.0f;
	}

	//線分AとBの最近傍点
	Vector2D Pc = this->startPoint + u * s;
	Vector2D Qc = other.startPoint + v * t;

	//その２点間の距離
	float dist = (Pc - Qc).Length();

	//距離が半径の合計以下なら、カプセル同士が当たっている
	if (dist <= (this->radius + other.radius)) {
		return true;
	}
	return false;
}
