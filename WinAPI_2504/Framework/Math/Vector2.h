#pragma once

struct Vector2
{
	float x;
	float y;

	Vector2() : x(0), y(0) 
	{}
	Vector2(float x, float y) : x(x), y(y)
	{}

	Vector2 operator+(const Vector2& other) const
	{
		return Vector2(x + other.x, y + other.y);
	}
	Vector2 operator-(const Vector2& other) const
	{
		return Vector2(x - other.x, y - other.y);
	}
	Vector2 operator*(const float& scala) const
	{
		return Vector2(x * scala, y * scala);
	}

	void operator+=(const Vector2& other)
	{
		x += other.x;
		y += other.y;
	}
	void operator-=(const Vector2& other)
	{
		x -= other.x;
		y -= other.y;
	}
	void operator*=(const float& scala)
	{
		x *= scala;
		y *= scala;
	}

	float Magnitude() const	{ return sqrt(x * x + y * y); }
	float SqrMagnitude() const { return x * x + y * y; }

	void Normalize()
	{
		float length = Magnitude();

		if (length > 0)
		{
			x /= length;
			y /= length;
		}
	}

	Vector2 GetNormalized() const
	{
		float length = Magnitude();

		return Vector2(x / length, y / length);
	}

	static const Vector2 Zero() { return Vector2(0, 0); }
	static const Vector2 One() { return Vector2(1, 1); }
		   
	static const Vector2 Right() { return Vector2(1, 0); }
	static const Vector2 Left() { return Vector2(-1, 0); }
	static const Vector2 Down() { return Vector2(0, 1); }
	static const Vector2 Up() { return Vector2(0, -1); }
};