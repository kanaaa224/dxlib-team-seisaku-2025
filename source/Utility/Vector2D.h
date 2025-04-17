#pragma once

class Vector2D
{
public:
	float x;
	float y;

public:
	Vector2D() : x(0.0f), y(0.0f) {}
	Vector2D(float scalar) : x(scalar), y(scalar) {}
	Vector2D(float mx, float my) : x(mx), y(my) {}
	~Vector2D() {}

public:
	Vector2D& operator = (const Vector2D& v)
	{
		this->x = v.x;
		this->y = v.y;

		return *this;
	}

	const Vector2D operator + (const Vector2D& v) const
	{
		return Vector2D(this->x + v.x, this->y + v.y);
	}

	Vector2D& operator += (const Vector2D& v)
	{
		this->x += v.x;
		this->y += v.y;

		return *this;
	}

	const Vector2D operator - (const Vector2D& v) const
	{
		return Vector2D(this->x - v.x, this->y - v.y);
	}

	Vector2D& operator -= (const Vector2D& v)
	{
		this->x -= v.x;
		this->y -= v.y;

		return *this;
	}

	const Vector2D operator * (const float& scalar) const
	{
		return Vector2D(this->x * scalar, this->y * scalar);
	}

	const Vector2D operator * (const Vector2D& v) const
	{
		return Vector2D(this->x * v.x, this->y * v.y);
	}

	Vector2D& operator *= (const float& scalar)
	{
		this->x *= scalar;
		this->y *= scalar;

		return *this;
	}

	Vector2D& operator *= (const Vector2D& v)
	{
		this->x *= v.x;
		this->y *= v.y;

		return *this;
	}

	const Vector2D operator / (const float& scalar) const;

	const Vector2D operator / (const Vector2D& v) const;

	Vector2D& operator /= (const float& scalar);

	Vector2D& operator /= (const Vector2D& v);

public:
	float SqrLength() const;
	float Length() const;

	Vector2D Normalize() const;

	static float Dot(const Vector2D& a);
	static float Dot(const Vector2D& a, const Vector2D& b);

	static float Cross(const Vector2D& a, const Vector2D& b);

	static Vector2D Lerp(const Vector2D& a, const Vector2D& b, const float t);

	static float Distance(const Vector2D& a, const Vector2D& b);
};