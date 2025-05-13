#pragma once

#include "Bullet.h"

//정방선언
//class Bullet;

enum class PlayerAbility
{
	None,
	TripleShot,
	DoubleShot,
	RLShot,
	BackShot,
	X2Shot
};

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

	void SetAbility(PlayerAbility ability) { currentAbility = ability; } // 능력 설정
	PlayerAbility GetAbility() const { return currentAbility; }
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

	PlayerAbility currentAbility = PlayerAbility::None;

	Vector2 firePos = {};
	Vector2 aimPoint = {};

	HPEN hPen;
};