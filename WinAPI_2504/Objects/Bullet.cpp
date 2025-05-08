#include "Framework.h"

Bullet::Bullet() : Circle(10)
{
}

Bullet::~Bullet()
{
}

void Bullet::Update()
{
	center += direction * SPEED * DELTA;

	if (center.y < 0)
	{
		isActive = false;
	}
}
