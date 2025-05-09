#include "Framework.h"

Player::Player() : Circle(50)
{
	hPen = CreatePen(PS_SOLID, 5, RGB(100, 230, 150));

	center = { SCREEN_WIDTH >> 1, SCREEN_HEIGHT * 4 / 5 };
}

Player::~Player()
{
	DeleteObject(hPen);	
}

void Player::Update()
{
	ControlMove();
	ControlFire();	
	Aming();

	ClampToScreenBounds();
}

void Player::Render(HDC hdc)
{
	//Circle::Render(hdc);
	DrawLine(hdc);

	MoveToEx(hdc, firePos.x, firePos.y, nullptr);
	LineTo(hdc, aimPoint.x, aimPoint.y);
}

void Player::Fire()
{
	Vector2 direction = mousePos - firePos;

	BulletManager::Get()->Fire(firePos, "Player", direction.GetNormalized());
}

void Player::ControlFire()
{
	if (Input::Get()->IsKeyDown(VK_LBUTTON))
	{
		Fire();	
	}

	if (Input::Get()->IsKeyPress('E'))
	{
		angle -= DELTA;
	}
	if (Input::Get()->IsKeyPress('Q'))
	{
		angle += DELTA;
	}
}

void Player::ControlMove()
{
	if (GetAsyncKeyState('D'))
		center += Vector2::Right() * SPEED * DELTA;
	if (GetAsyncKeyState('A'))
		center += Vector2::Left() * SPEED * DELTA;
	if (GetAsyncKeyState('W'))
		center += Vector2::Up() * SPEED * DELTA;
	if (GetAsyncKeyState('S'))
		center += Vector2::Down() * SPEED * DELTA;
}

void Player::ClampToScreenBounds()
{
	//Left
	if(center.x - radius < 0)
		center.x = radius;

	//Right
	if (center.x + radius > SCREEN_WIDTH)
		center.x = SCREEN_WIDTH - radius;

	//Top
	if (center.y - radius < 0)
		center.y = radius;

	//Bottom
	if (center.y + radius > SCREEN_HEIGHT)
		center.y = SCREEN_HEIGHT - radius;
}

void Player::Aming()
{
	//Vector2 direction = mousePos - firePos;
	//aimPoint = firePos + direction.GetNormalized() * AIM_LENGTH;

	float x = cos(angle) * AIM_LENGTH;
	float y = -sin(angle) * AIM_LENGTH;

	aimPoint = firePos + Vector2(x, y);
}

void Player::DrawLine(HDC hdc)
{
	firePos = { center.x, center.y - radius };
	POINT right = { center.x + radius, center.y + radius };
	POINT left = { center.x - radius, center.y + radius };

	HPEN defaultPen = (HPEN)SelectObject(hdc, hPen);

	MoveToEx(hdc, firePos.x, firePos.y, nullptr);
	LineTo(hdc, right.x, right.y);

	MoveToEx(hdc, firePos.x, firePos.y, nullptr);
	LineTo(hdc, left.x, left.y);

	MoveToEx(hdc, center.x, center.y + (radius >> 1), nullptr);
	LineTo(hdc, right.x, right.y);

	MoveToEx(hdc, center.x, center.y + (radius >> 1), nullptr);
	LineTo(hdc, left.x, left.y);

	SelectObject(hdc, defaultPen);
}

