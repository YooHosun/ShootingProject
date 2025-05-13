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

	// ���� ���� ���� ������
	if (isBossEnemy)
	{
		int r = radius;
		int cx = (int)center.x;
		int cy = (int)center.y;

		HPEN hPen = CreatePen(PS_SOLID, 5, RGB(128, 128, 128));
		HPEN defaultPen = (HPEN)SelectObject(hdc, hPen);

		// �߽� ���簢��
		MoveToEx(hdc, cx - r, cy - r, nullptr);
		LineTo(hdc, cx + r, cy - r);
		LineTo(hdc, cx + r, cy + r);
		LineTo(hdc, cx - r, cy + r);
		LineTo(hdc, cx - r, cy - r);

		// ���� ����
		MoveToEx(hdc, cx - r, cy - r, nullptr);
		LineTo(hdc, cx - r * 3, cy - r);
		LineTo(hdc, cx - r, cy + r);
		LineTo(hdc, cx - r, cy - r);

		// ������ ����
		MoveToEx(hdc, cx + r, cy - r, nullptr);
		LineTo(hdc, cx + r * 3, cy - r);
		LineTo(hdc, cx + r, cy + r);
		LineTo(hdc, cx + r, cy - r);

		// �Ӹ�
		MoveToEx(hdc, cx - r, cy + r, nullptr);
		LineTo(hdc, cx + r, cy + r);
		LineTo(hdc, cx, cy + r * 3);
		LineTo(hdc, cx - r, cy + r);

		// ���� ����
		int gunW = r / 4;
		int gunH = r / 2;
		int gx = cx - r;
		int gy = cy - r;

		MoveToEx(hdc, gx, gy, nullptr);
		LineTo(hdc, gx - gunW, gy);
		LineTo(hdc, gx - gunW, gy - gunH);
		LineTo(hdc, gx, gy - gunH);
		LineTo(hdc, gx, gy);

		// ������ ����
		gx = cx + r;
		gy = cy - r;

		MoveToEx(hdc, gx, gy, nullptr);
		LineTo(hdc, gx + gunW, gy);
		LineTo(hdc, gx + gunW, gy - gunH);
		LineTo(hdc, gx, gy - gunH);
		LineTo(hdc, gx, gy);

		SelectObject(hdc, defaultPen);
		DeleteObject(hPen);
		return;
	}

	// �⺻ ���� �� ������
	switch (color) {
	case EnemyColor::Red: hSelectBrush = hRedBrush; break;
	case EnemyColor::Green: hSelectBrush = hGreenBrush; break;
	case EnemyColor::Blue: hSelectBrush = hBlueBrush; break;
	case EnemyColor::Yellow: hSelectBrush = hYellowBrush; break;
	case EnemyColor::Cyan: hSelectBrush = hCyanBrush; break;
	case EnemyColor::Magenta: hSelectBrush = hMagentaBrush; break;
	}

	HBRUSH defaultBrush = (HBRUSH)SelectObject(hdc, hSelectBrush);
	Circle::Render(hdc);
	SelectObject(hdc, defaultBrush);
}


void Enemy::Spawn(Vector2 pos, EnemyColor color, EnemyShootingType shootingType, EnemyMoveType moveType, Vector2 pivotDir, int hp)
{
	center = pos;
	pivotCenter = pos;
	pivotAngle = 0.0f;
	pivotRadius = 50.0f;
	pivotSpeed = 5.0f;
	center = pos;
	isActive = true;
	isDamaged = false;

	this->color = color;
	this->shootingType = shootingType;
	this->moveType = moveType;
	this->pivotDir = pivotDir;
	this->hp = hp;
}
/*
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
*/
void Enemy::SpawnBoss(Vector2 pos)
{
	center = pos;
	isActive = true;
	isDamaged = false;

	isBossEnemy = true;
	radius = 40;  // ���� ũ�� �ణ Ű���
	color = EnemyColor::Green; // �ǹ� ����
	hp = 200;

	shootingType = EnemyShootingType::Single;
	shootingType2 = EnemyShootingType::Spread;
	shootingType3 = EnemyShootingType::Wave;
	moveType = EnemyMoveType::Linear;
	direction = Vector2::Right(); // �¿� �պ�
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
	switch (moveType)
	{
	case EnemyMoveType::Linear:
		center += direction * SPEED * DELTA;
		if (isBossEnemy)
		{
			float limit = radius * 3; // ������ ��ü + ���� ũ�� ���
			if (center.x < limit)
			{
				center.x = limit;
				direction *= -1;
			}
			else if (center.x > SCREEN_WIDTH - limit)
			{
				center.x = SCREEN_WIDTH - limit;
				direction *= -1;
			}
		}
		else
		{
			// �Ϲ� �� ���� �̵�
			if (center.y > SCREEN_HEIGHT || center.y < 0)
			{
				direction *= -1;
			}
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

void Enemy::Fire()
{
	if (isBossEnemy)
	{
		// ���� ���� Ÿ�̸�
		fireTimerSingle += DELTA;
		fireTimerSpread += DELTA;
		waveStartTimer += DELTA;

		// Single �߻�
		if (fireTimerSingle >= FIRE_INTERVAL / 5.0f)
		{
			fireTimerSingle = 0.0f;
			SingleFire();
		}

		// Spread �߻�
		if (fireTimerSpread >= FIRE_INTERVAL / 2.0f)
		{
			fireTimerSpread = 0.0f;
			SpreadFire();
		}

		// Wave ����
		if (!isWaveFiring && waveStartTimer >= FIRE_INTERVAL * 2.0f)
		{
			isWaveFiring = true;
			waveShotCount = 0;
			waveFireTimer = 0.0f;
			waveStartTimer = 0.0f;

			Vector2 toPlayer = player->GetCenter() - center;
			waveBaseAngle = atan2(toPlayer.y, toPlayer.x);
		}

		// Wave ���� ó��
		WaveFire();

		return;
	}

	// �Ϲ� �� ó��
	fireTimer += DELTA;

	switch (shootingType)
	{
	case EnemyShootingType::Single:
		if (fireTimer >= FIRE_INTERVAL)
		{
			fireTimer = 0.0f;
			SingleFire();
		}
		break;

	case EnemyShootingType::Spread:
		if (fireTimer >= FIRE_INTERVAL)
		{
			fireTimer = 0.0f;
			SpreadFire();
		}
		break;

	case EnemyShootingType::Wave:
		if (!isWaveFiring && fireTimer >= FIRE_INTERVAL)
		{
			isWaveFiring = true;
			waveShotCount = 0;
			waveFireTimer = 0.0f;
			fireTimer = 0.0f;

			Vector2 toPlayer = player->GetCenter() - center;
			waveBaseAngle = atan2(toPlayer.y, toPlayer.x);
		}

		WaveFire();
		break;
	}
}

void Enemy::SingleFire()
{
	Vector2 toPlayer = player->GetCenter() - center;
	toPlayer.Normalize();
	BulletManager::Get()->Fire(center, "Enemy", toPlayer);
}

void Enemy::SpreadFire()
{
	float stepAngle = PI * 2.0f / FIRE_COUNT;
	for (int i = 0; i < FIRE_COUNT; i++)
	{
		float angle = stepAngle * i;
		Vector2 direction(cos(angle), sin(angle));
		BulletManager::Get()->Fire(center, "Enemy", direction);
	}
}

void Enemy::WaveFire()
{
	if (!isWaveFiring) return;

	waveFireTimer += DELTA;

	if (waveFireTimer >= 0.15f && waveShotCount < 4)
	{
		waveFireTimer = 0.0f;

		const int shotsPerWave = 5;
		float spread = PI / 6.0f;

		for (int i = 0; i < shotsPerWave; i++)
		{
			float offset = spread * ((float)i / (shotsPerWave - 1) - 0.5f);
			float angle = waveBaseAngle + offset;
			Vector2 dir(cos(angle), sin(angle));
			BulletManager::Get()->Fire(center, "Enemy", dir);
		}

		waveShotCount++;

		if (waveShotCount >= 4)
		{
			isWaveFiring = false;
			waveFireTimer = 0.0f;
		}
	}
}

