#pragma once

#include "Vector2D.h"
#include <vector>

enum class eObjectType : unsigned char
{
	none,
	wall,
	ground,
	item,
	buff,
	player,
	enemy
};

class Collision
{
public:
	bool is_blocking;

	Vector2D box_size;
	Vector2D pivot;

	eObjectType object_type;
	std::vector<eObjectType> hit_object_type;

	float radius;//半径
	float GetRadius() { return radius; };

private:
	Vector2D position;
	Vector2D startPoint, endPoint;//カプセルの始点と終点

public:
	Collision();
	~Collision();

	void SetPosition(const Vector2D& pos);
	const Vector2D& GetPosition() const;

	const Vector2D& GetStartPoint() const { return startPoint; };
	const Vector2D& GetEndPoint() const { return endPoint; };
	void SetStartPoint(Vector2D sp) { startPoint = sp; };
	void SetEndPoint(Vector2D ep) { endPoint = ep; };

	void SetSize(const float& width, const float& height);
	Vector2D GetSize();

	void SetObjectType(const eObjectType& FUNC_objecttype);
	void SetHitObjectType(const std::vector<eObjectType>& FUNC_hitobjecttype);
	bool IsCheckHitTarget(eObjectType FUNC_hitobject) const;
	bool CheckCollision(const Collision& other) const;
};