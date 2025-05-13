#include "Framework.h"

BulletManager::BulletManager()
{
	bullets.resize(BULLET_POOL_SIZE);
	for (Bullet*& bullet : bullets)
	{
		bullet = new Bullet();
		bullet->SetActive(false);
	}
}

BulletManager::~BulletManager()
{
	for (Bullet*& bullet : bullets)
	{
		delete bullet;
	}
	bullets.clear();
}

void BulletManager::Update()
{
	for (Bullet*& bullet : bullets)
	{
		bullet->Update();
	}
}

void BulletManager::Render(HDC hdc)
{
	//bullet->Render(hdc);
	for (Bullet*& bullet : bullets)
	{
		bullet->Render(hdc);
	}
}

bool BulletManager::IsCollision(Circle* circle, string tag)
{
	for (Bullet*& bullet : bullets)
	{
		if (!bullet->IsActive())
			continue;
		if (bullet->GetTag() != tag)
			continue;
		if (!bullet->IsCollisionCircle(circle))
			continue;

		bullet->SetActive(false);
		return true;
	}

	return false;
}

void BulletManager::Fire(Vector2 pos, string tag, Vector2 direction, COLORREF color)
{
	for (Bullet*& bullet : bullets)
	{
		if (!bullet->IsActive())
		{
			bullet->Fire(pos, direction);
			bullet->SetTag(tag);
			bullet->SetColor(color);
			break;
		}
	}
}
