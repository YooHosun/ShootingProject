#pragma once

#include "Bullet.h"

//정방선언
//class Bullet;

class Player : public Circle
{
private:
	const int SPEED = 300;
	const int BULLET_POOL_SIZE = 50;
	const float AIM_LENGTH = 50.0f;

public:
	Player();
	~Player();

	void Update();	
	void Render(HDC hdc);

private:
	void Fire();
	void ControlFire();
	void ControlMove();
	void ClampToScreenBounds();
	void Aming();

	void DrawLine(HDC hdc);

private:
	//전방선전
	//Bullet* bullet;
	//vector<Bullet*> bullets;
	float angle = PI * 0.5f;

	Vector2 firePos = {};
	Vector2 aimPoint = {};

	HPEN hPen;
};