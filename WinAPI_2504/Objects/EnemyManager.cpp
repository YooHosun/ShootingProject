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
	spawnTimer += DELTA;

	if (spawnTimer >= SPAWN_INTERVAL)
	{
		if (enemyCount < 5) // 최대 적 수
		{
			spawnTimer = 0.0f;
			SpawnEnemy();
		}
	}

	for (Enemy*& enemy : enemies)
	{
		enemy->Update();
	}
}

void EnemyManager::Update2()
{
	spawnTimer += DELTA;

	if (spawnTimer >= SPAWN_INTERVAL)
	{
		if (enemyCount < 10) // 최대 적 수
		{
			spawnTimer = 0.0f;
			SpawnEnemy2();
		}
	}

	for (Enemy*& enemy : enemies)
	{
		enemy->Update();
	}
}

void EnemyManager::Update3()
{
	spawnTimer += DELTA;

	if (spawnTimer >= SPAWN_INTERVAL)
	{
		if (enemyCount < 15) // 최대 적 수
		{
			spawnTimer = 0.0f;
			SpawnEnemy3();
		}
	}

	for (Enemy*& enemy : enemies)
	{
		enemy->Update();
	}
}

void EnemyManager::Render(HDC hdc)
{
	for (Enemy*& enemy : enemies)
	{
		enemy->Render(hdc);
	}
}

void EnemyManager::SpawnEnemy()
{
	int randomX = rand() % SCREEN_WIDTH;

	for (Enemy*& enemy : enemies)
	{
		if (!enemy->IsActive())
		{
			enemy->Spawn({(float)randomX, 0 });
			enemyCount++;
			break;
		}
	}
}

void EnemyManager::SpawnEnemy2()
{
	int randomX = rand() % SCREEN_WIDTH;

	for (Enemy*& enemy : enemies)
	{
		if (!enemy->IsActive())
		{
			enemy->Spawn2({ (float)randomX, 0 });
			enemyCount++;
			break;
		}
	}
}

void EnemyManager::SpawnEnemy3()
{
	int randomX = rand() % SCREEN_WIDTH;

	for (Enemy*& enemy : enemies)
	{
		if (!enemy->IsActive())
		{
			enemy->Spawn3({ (float)randomX, 0 });
			enemyCount++;
			break;
		}
	}
}

void EnemyManager::SetPlayer(Player* player)
{
	for (Enemy*& enemy : enemies)
	{
		enemy->SetPlayer(player);
	}
}
