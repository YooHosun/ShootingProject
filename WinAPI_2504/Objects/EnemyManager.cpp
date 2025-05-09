#include "Framework.h"

EnemyManager::EnemyManager()
{
	//Reserve
	//enemies.reserve(ENEMY_POOL_SIZE);
	// 
	//for (int i = 0; i < ENEMY_POOL_SIZE; i++)
	//{
	//	Enemy* enemy = new Enemy();
	//	enemies.push_back(enemy);
	//}
	//Resize
	enemies.resize(ENEMY_POOL_SIZE);//Enemy* enemies[50];
	for (Enemy*& enemy : enemies)
	{
		enemy = new Enemy();
		enemy->SetActive(false);
	}
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
	{
		enemy->Update();
	}

	int aliveCount = 0;
	for (Enemy* enemy : enemies)
	{
		if (enemy->IsActive())
			aliveCount++;
	}
	enemyCount = aliveCount;

	if (enemyCount == 0 && !stageClearTriggered && IsAllEnemiesSpawned)
	{
		stageClearTriggered = true;
		stageClearTimer = 0.0f;
	}

	spawnTimer += DELTA;

	if (spawnedEnemyCount < 5)
	{
		if (spawnTimer >= SPAWN_INTERVAL)
		{
			spawnTimer = 0.0f;

			if (SpawnEnemy()) 
			{
				spawnedEnemyCount++;
			}

			if (spawnedEnemyCount >= 5)
			{
				IsAllEnemiesSpawned = true;
			}
		}
	}

	if (stageClearTriggered)
	{
		stageClearTimer += DELTA;

		if (stageClearTimer >= 2.0f)
		{
			allEnemiesCleared = true;
			SCENE->ChangeScene("Game2");
		}
	}
}

void EnemyManager::Update2()
{
	for (Enemy*& enemy : enemies)
	{
		enemy->Update();
	}

	int aliveCount = 0;
	for (Enemy* enemy : enemies)
	{
		if (enemy->IsActive())
			aliveCount++;
	}
	enemyCount = aliveCount;

	if (enemyCount == 0 && !stageClearTriggered && IsAllEnemiesSpawned)
	{
		stageClearTriggered = true;
		stageClearTimer = 0.0f;
	}

	spawnTimer += DELTA;

	if (spawnedEnemyCount < 10)
	{
		if (spawnTimer >= SPAWN_INTERVAL)
		{
			spawnTimer = 0.0f;

			if (SpawnEnemy())
			{
				spawnedEnemyCount++;
			}

			if (spawnedEnemyCount >= 10)
			{
				IsAllEnemiesSpawned = true;
			}
		}
	}

	if (stageClearTriggered)
	{
		stageClearTimer += DELTA;

		if (stageClearTimer >= 2.0f)
		{
			allEnemiesCleared = true;
			SCENE->ChangeScene("Game3");
		}
	}
}

void EnemyManager::Update3()
{
	for (Enemy*& enemy : enemies)
	{
		enemy->Update();
	}

	int aliveCount = 0;
	for (Enemy* enemy : enemies)
	{
		if (enemy->IsActive())
			aliveCount++;
	}
	enemyCount = aliveCount;

	if (enemyCount == 0 && !stageClearTriggered && IsAllEnemiesSpawned)
	{
		stageClearTriggered = true;
		stageClearTimer = 0.0f;
	}

	spawnTimer += DELTA;

	if (spawnedEnemyCount < 15)
	{
		if (spawnTimer >= SPAWN_INTERVAL)
		{
			spawnTimer = 0.0f;

			if (SpawnEnemy())
			{
				spawnedEnemyCount++;
			}

			if (spawnedEnemyCount >= 15)
			{
				IsAllEnemiesSpawned = true;
			}
		}
	}

	if (stageClearTriggered)
	{
		stageClearTimer += DELTA;

		if (stageClearTimer >= 2.0f)
		{
			allEnemiesCleared = true;
			SCENE->ChangeScene("Title");
		}
	}
}

void EnemyManager::Render(HDC hdc)
{
	for (Enemy*& enemy : enemies)
	{
		enemy->Render(hdc);
	}

	if (stageClearTriggered && stageClearTimer < 2.0f)
	{
		wstring clearText = L"Stage Clear!";

		rect.left = 0;
		rect.top = SCREEN_HEIGHT / 2 - 50;
		rect.right = SCREEN_WIDTH;
		rect.bottom = rect.top + 100;

		DrawText(hdc, clearText.c_str(), -1, &rect, DT_CENTER);
	}
}

bool EnemyManager::SpawnEnemy()
{
	int randomX = rand() % SCREEN_WIDTH;

	for (Enemy*& enemy : enemies)
	{
		if (!enemy->IsActive())
		{
			enemy->Spawn({ (float)randomX, 0 });
			return true; 
		}
	}
	return false;
}

bool EnemyManager::SpawnEnemy2()
{
	int randomX = rand() % SCREEN_WIDTH;

	for (Enemy*& enemy : enemies)
	{
		if (!enemy->IsActive())
		{
			enemy->Spawn({ (float)randomX, 0 });
			return true;
		}
	}
	return false;
}

bool EnemyManager::SpawnEnemy3()
{
	int randomX = rand() % SCREEN_WIDTH;

	for (Enemy*& enemy : enemies)
	{
		if (!enemy->IsActive())
		{
			enemy->Spawn({ (float)randomX, 0 });
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
