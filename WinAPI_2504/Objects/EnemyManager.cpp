#include "Framework.h"

EnemyManager::EnemyManager()
{
	enemies.resize(ENEMY_POOL_SIZE);
	for (Enemy*& enemy : enemies)
	{
		enemy = new Enemy();
		enemy->SetActive(false);
	}

	stageData =
	{
		{1, {Enemy::EnemyColor::Green, Enemy::EnemyShootingType::Single, Enemy::EnemyMoveType::Linear, Vector2::Down(), 20, 5, false}},
		{2, {Enemy::EnemyColor::Red, Enemy::EnemyShootingType::Spread, Enemy::EnemyMoveType::Circular, Vector2::Down(), 30, 10, false}},
		{3, {Enemy::EnemyColor::Cyan, Enemy::EnemyShootingType::Wave, Enemy::EnemyMoveType::Sine, Vector2::Down(), 40, 2, true}}
	};
}

EnemyManager::~EnemyManager()
{
	for (Enemy*& enemy : enemies)
	{
		delete enemy;
	}
	enemies.clear();
}

void EnemyManager::Update()
{
	for (Enemy*& enemy : enemies)
		enemy->Update();

	int aliveCount = 0;
	for (Enemy* enemy : enemies)
	{
		if (enemy->IsActive())
			aliveCount++;
	}
	enemyCount = aliveCount;

	const EnemySpawnData& data = stageData[currentStage];

	spawnTimer += DELTA;
	if (spawnedEnemyCount < data.spawnCount)
	{
		if (spawnTimer >= SPAWN_INTERVAL)
		{
			spawnTimer = 0.0f;
			if (SpawnEnemy(data))
				spawnedEnemyCount++;

			if (spawnedEnemyCount >= data.spawnCount)
				IsAllEnemiesSpawned = true;
		}
	}

	if (data.hasBoss && !isBossSpawned && enemyCount == 0 && IsAllEnemiesSpawned)
	{
		for (Enemy*& enemy : enemies)
		{
			if (!enemy->IsActive())
			{
				enemy->SpawnBoss({ SCREEN_WIDTH / 2.0f, 150.0f });
				bossEnemy = enemy;
				isBossSpawned = true;
				break;
			}
		}
	}

	if (data.hasBoss && isBossSpawned && bossEnemy && !bossEnemy->IsActive())
	{
		if (!isBossDefeated)
		{
			isBossDefeated = true;
			stageClearTimer = 0.0f;
		}
	}

	if ((!data.hasBoss && enemyCount == 0 && !stageClearTriggered && IsAllEnemiesSpawned) || (data.hasBoss && isBossDefeated))
	{
		stageClearTriggered = true;
		stageClearTimer = 0.0f;
	}

	if (stageClearTriggered)
	{
		stageClearTimer += DELTA;
		if (stageClearTimer >= 2.0f)
		{
			if (currentStage == 1)
			{
				SCENE->ChangeScene("Game2");
			}
			else if (currentStage == 2)
			{
				SCENE->ChangeScene("Game3");
			}
			else if (currentStage == 3)
			{
				SCENE->ChangeScene("Title");
			}
			stageClearTriggered = false;
		}
	}
}

void EnemyManager::Render(HDC hdc)
{
	for (Enemy*& enemy : enemies)
	{
		enemy->Render(hdc);
	}

	if (stageClearTriggered && stageClearTimer < 2.0f && !isBossSpawned)
	{
		wstring clearText = L"Stage Clear!";

		rect.left = 0;
		rect.top = SCREEN_HEIGHT / 2 - 50;
		rect.right = SCREEN_WIDTH;
		rect.bottom = rect.top + 100;

		DrawText(hdc, clearText.c_str(), -1, &rect, DT_CENTER);
	}
}

bool EnemyManager::SpawnEnemy(const EnemySpawnData& data)
{
	int randomX = rand() % SCREEN_WIDTH;

	for (Enemy*& enemy : enemies)
	{
		if (!enemy->IsActive())
		{
			enemy->Spawn({ (float)randomX, 0 }, data.color, data.shootingType, data.moveType, data.pivotDir, data.hp);
			return true;
		}
	}
	return false;
}

void EnemyManager::SetPlayer(Player* player)
{
	for (Enemy*& enemy : enemies)
	{
		enemy->SetPlayer(player);
	}
}

void EnemyManager::Reset()
{
	currentStage = 1;
	spawnedEnemyCount = 0;
	isBossSpawned = false;
	isBossDefeated = false;
	stageClearTriggered = false;
	stageClearTimer = 0.0f;

	for (Enemy* enemy : enemies)
	{
		enemy->SetActive(false);
	}
}

bool EnemyManager::AreAllEnemiesDead()
{
	for (Enemy* enemy : enemies)
	{
		if (enemy->IsActive())
		{
			return false;
		}
	}
	return true;
}
