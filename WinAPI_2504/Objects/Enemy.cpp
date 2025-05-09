#include "Framework.h"

Enemy::Enemy() : Circle(30)
{
	hRedBrush = CreateSolidBrush(RGB(255, 0, 0));
	hBlueBrush = CreateSolidBrush(RGB(0, 0, 255));
	hGreenBrush = CreateSolidBrush(RGB(0, 255, 0));
	hYellowBrush = CreateSolidBrush(RGB(255, 255, 0));
	hCyanBrush = CreateSolidBrush(RGB(0, 255, 255));
	hMagentaBrush = CreateSolidBrush(RGB(255, 0, 255));
}

Enemy::~Enemy()
{
	DeleteObject(hRedBrush);
	DeleteObject(hBlueBrush);
	DeleteObject(hGreenBrush);
	DeleteObject(hYellowBrush);
	DeleteObject(hCyanBrush);
	DeleteObject(hMagentaBrush);
}

void Enemy::Update()
{
	if (!isActive) return;

	Move();
	Damage();
	Fire();
}

void Enemy::Render(HDC hdc)
{
	if (!isActive) return;

	switch (color) {
	case EnemyColor::Red:
		hSelectBrush = hRedBrush;
		break;
	case EnemyColor::Green:
		hSelectBrush = hGreenBrush;
		break;
	case EnemyColor::Blue:
		hSelectBrush = hBlueBrush;
		break;
	case EnemyColor::Yellow:
		hSelectBrush = hYellowBrush;
		break;
	case EnemyColor::Cyan:
		hSelectBrush = hCyanBrush;
		break;
	case EnemyColor::Magenta:
		hSelectBrush = hMagentaBrush;
		break;
	}

	HBRUSH defaultBrush = (HBRUSH)SelectObject(hdc, hSelectBrush);

	Circle::Render(hdc);

	SelectObject(hdc, defaultBrush);
}

void Enemy::Spawn(Vector2 pos)
{
	center = pos;
	pivotCenter = pos;
	pivotAngle = 0.0f;
	pivotRadius = 50.0f;
	pivotSpeed = 5.0f;
	center = pos;
	isActive = true;
	//hSelectBrush = hBlueBrush;
	isDamaged = false;

	color = EnemyColor::Green;
	shootingType = EnemyShootingType::Single;
	moveType = EnemyMoveType::Linear;
	pivotDir = Vector2::Down();  // �⺻�� �Ʒ���
	hp = 20;
	//direction = Vector2::Down();
}

void Enemy::Spawn2(Vector2 pos)
{
	center = pos;
	pivotCenter = pos;
	pivotAngle = 0.0f;
	pivotRadius = 50.0f;
	pivotSpeed = 5.0f;
	center = pos;
	isActive = true;
	//hSelectBrush = hBlueBrush;
	isDamaged = false;

	color = EnemyColor::Red;
	shootingType = EnemyShootingType::Spread;
	moveType = EnemyMoveType::Circular;
	pivotDir = Vector2::Down();  // �⺻�� �Ʒ���
	hp = MAX_HP;
	//direction = Vector2::Down();
}

void Enemy::Spawn3(Vector2 pos)
{
	center = pos;
	pivotCenter = pos;
	pivotAngle = 0.0f;
	pivotRadius = 50.0f;
	pivotSpeed = 5.0f;
	center = pos;
	isActive = true;
	//hSelectBrush = hBlueBrush;
	isDamaged = false;

	color = EnemyColor::Cyan;
	shootingType = EnemyShootingType::Wave;
	moveType = EnemyMoveType::Sine;
	pivotDir = Vector2::Down();  // �⺻�� �Ʒ���
	hp = MAX_HP;
	//direction = Vector2::Down();
}

void Enemy::Damage()
{
	if (isDamaged)
	{
		damageTimer += DELTA;

		if (damageTimer >= DAMAGE_INTERVAL)
		{
			damageTimer = 0;
			isDamaged = false;
			hSelectBrush = hBlueBrush;
		}
		return;
	}

	if (BulletManager::Get()->IsCollision(this, "Player"))
	{
		//isActive = false;
		hp -= 10;
		isDamaged = true;
		hSelectBrush = hRedBrush;

		if (hp <= 0)
		{
			isActive = false;
		}
	}
}

void Enemy::Move()
{
	//center.y += SPEED * DELTA;

	/*if (center.y > SCREEN_HEIGHT)
	{
		isActive = false;
	}*/
	//direction.Normalize();

	switch (moveType)
	{
	case EnemyMoveType::Linear:
		center += direction * SPEED * DELTA;
		if (center.y > SCREEN_HEIGHT || center.y < 0)
		{
			direction *= -1;
		}
		break;
	case EnemyMoveType::Circular:
		// �߽� ���Ʒ� �̵�
		pivotCenter += pivotDir * SPEED * DELTA;

		// ���� ����
		if (pivotCenter.y > SCREEN_HEIGHT || pivotCenter.y < 0)
			pivotDir *= -1;

		// ���� ȸ��
		pivotAngle += pivotSpeed * DELTA;
		center.x = pivotCenter.x + cos(pivotAngle) * pivotRadius;
		center.y = pivotCenter.y + sin(pivotAngle) * pivotRadius;
		break;

	case EnemyMoveType::Rectangular: // �̰� ���� �ʿ������ �������� �ʹ� �����
		// �߽� �̵�
		pivotCenter += pivotDir * SPEED * DELTA;

		// ���� ����
		if (pivotCenter.y > SCREEN_HEIGHT || pivotCenter.y < 0)
			pivotDir *= -1;

		// �簢 ��� ȸ�� (0~4 * 90��)
		pivotAngle += pivotSpeed * DELTA;

		{
			float segment = fmod(pivotAngle, 4.0f); // 0~4 ����
			if (segment < 1.0f)
				center = pivotCenter + Vector2(pivotRadius * (segment), -pivotRadius);
			else if (segment < 2.0f)
				center = pivotCenter + Vector2(pivotRadius, pivotRadius * (segment - 1.0f));
			else if (segment < 3.0f)
				center = pivotCenter + Vector2(pivotRadius * (1.0f - (segment - 2.0f)), pivotRadius);
			else
				center = pivotCenter + Vector2(-pivotRadius, pivotRadius * (1.0f - (segment - 3.0f)));
		}
		break;
	case EnemyMoveType::Sine:
		center += pivotDir * SPEED * DELTA;

		// �¿� ���̺�
		pivotAngle += pivotSpeed * DELTA;
		center.x = pivotCenter.x + sin(pivotAngle) * pivotRadius;

		// ȭ�� ���̸� ���� ����
		if (center.y > SCREEN_HEIGHT)
			pivotDir = Vector2::Up();
		else if (center.y < 0)
			pivotDir = Vector2::Down();
		break;
	}
}

//void Enemy::Fire()
//{
//	fireTimer += DELTA;
//
//	if (fireTimer >= FIRE_INTERVAL)
//	{
//		fireTimer = 0.0f;
//
//		float stepAngle = PI * 2.0f / FIRE_COUNT;
//
//		for (int i = 0; i < FIRE_COUNT; i++)
//		{
//			float angle = stepAngle * i;
//			Vector2 direction(cos(angle), sin(angle));
//			BulletManager::Get()->Fire(center, "Enemy", direction);
//		}
//
//		//Vector2 direction = player->GetCenter() - center;
//		//BulletManager::Get()->Fire(center, "Enemy", direction);
//	}
//}

void Enemy::Fire()
{
	fireTimer += DELTA;

	switch (shootingType)
	{
	case EnemyShootingType::Single:
		if (fireTimer >= FIRE_INTERVAL)
		{
			fireTimer = 0.0f;

			Vector2 toPlayer = player->GetCenter() - center;
			toPlayer.Normalize();
			BulletManager::Get()->Fire(center, "Enemy", toPlayer);
		}
		break;

	case EnemyShootingType::Spread:
		if (fireTimer >= FIRE_INTERVAL)
		{
			fireTimer = 0.0f;

			float stepAngle = PI * 2.0f / FIRE_COUNT;
			for (int i = 0; i < FIRE_COUNT; i++)
			{
				float angle = stepAngle * i;
				Vector2 direction(cos(angle), sin(angle));
				BulletManager::Get()->Fire(center, "Enemy", direction);
			}
		}
		break;

	case EnemyShootingType::Wave:
		// ù �߻� ����
		if (!isWaveFiring && fireTimer >= FIRE_INTERVAL)
		{
			isWaveFiring = true;
			waveShotCount = 0;
			fireTimer = 0.0f;

			Vector2 toPlayer = player->GetCenter() - center;
			waveBaseAngle = atan2(toPlayer.y, toPlayer.x);
		}

		// ���� 5�߾� 4�� �߻� (�ð��� ����)
		if (isWaveFiring)
		{
			waveFireTimer += DELTA;

			if (waveFireTimer >= 0.15f && waveShotCount < 4) // 0.15�� �������� 4��Ʈ �߻�
			{
				waveFireTimer = 0.0f;

				const int shotsPerWave = 5;
				float spread = PI / 6.0f; // ��ä�� ����: ��15��

				for (int i = 0; i < shotsPerWave; i++)
				{
					float offset = spread * ((float)i / (shotsPerWave - 1) - 0.5f); // -0.5 ~ +0.5
					float angle = waveBaseAngle + offset;
					Vector2 dir(cos(angle), sin(angle));
					BulletManager::Get()->Fire(center, "Enemy", dir);
				}

				waveShotCount++;

				if (waveShotCount >= 4)
				{
					isWaveFiring = false;
					waveFireTimer = 0.0f;
					fireTimer = 0.0f;
				}
			}
		}
		break;
	}
}

