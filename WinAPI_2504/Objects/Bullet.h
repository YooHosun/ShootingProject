#pragma once
#include <windows.h>

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

	void Render(HDC hdc) override;

	string GetTag() { return tag; }
	void SetTag(string tag) { this->tag = tag; }

	COLORREF GetColor() const { return color; }
	void SetColor(COLORREF color) { this->color = color; }

private:
	string tag;
	Vector2 direction = Vector2::Up();
	COLORREF color = RGB(255, 255, 255);
};