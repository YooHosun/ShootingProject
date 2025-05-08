#pragma once

class Bullet : public Circle
{
private:
	const float SPEED = 500;

public:
	Bullet();
	~Bullet();

	void Update();

	void Fire(Vector2 pos, Vector2 direction = Vector2::Up())
	{
		this->direction = direction.GetNormalized();
		isActive = true;
		center = pos;
	}

	string GetTag() { return tag; }
	void SetTag(string tag) { this->tag = tag; }	

private:
	string tag;
	Vector2 direction = Vector2::Up();
};