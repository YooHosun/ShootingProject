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

			if (SpawnEnemy2())
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
	//for (Enemy*& enemy : enemies)
	//{
	//	enemy->Update();
	//}

	//int aliveCount = 0;
	//for (Enemy* enemy : enemies)
	//{
	//	if (enemy->IsActive())
	//		aliveCount++;
	//}
	//enemyCount = aliveCount;

	//if (enemyCount == 0 && !stageClearTriggered && IsAllEnemiesSpawned)
	//{
	//	stageClearTriggered = true;
	//	stageClearTimer = 0.0f;
	//}

	//spawnTimer += DELTA;

	//if (spawnedEnemyCount < 2)
	//{
	//	if (spawnTimer >= SPAWN_INTERVAL)
	//	{
	//		spawnTimer = 0.0f;

	//		if (SpawnEnemy3())
	//		{
	//			spawnedEnemyCount++;
	//		}

	//		if (spawnedEnemyCount >= 2)
	//		{
	//			IsAllEnemiesSpawned = true;
	//		}
	//	}
	//}

	//// 4. �Ϲ� �� ��� ���� �� �� ���� ���� �غ�
	//if (enemyCount == 0 && !stageClearTriggered && IsAllEnemiesSpawned)
	//{
	//	stageClearTriggered = true;
	//	stageClearTimer = 0.0f;
	//}

	//// 5. ���� ����
	//if (stageClearTriggered && !isBossSpawned)
	//{
	//	boss = new Boss();
	//	boss->Spawn({ SCREEN_WIDTH / 2.0f, 150.0f });
	//	isBossSpawned = true;
	//}

	//// 6. ���� ������Ʈ
	//if (isBossSpawned && boss && !isBossDefeated)
	//{
	//	boss->Update();

	//	if (!boss->IsActive()) {
	//		isBossDefeated = true;
	//		stageClearTimer = 0.0f;
	//	}
	//}

	//// 7. ���� ���� �� �� ��ȯ
	//if (isBossDefeated)
	//{
	//	stageClearTimer += DELTA;

	//	if (stageClearTimer >= 2.0f)
	//	{
	//		SCENE->ChangeScene("Title");
	//	}
	//}

	///*if (stageClearTriggered)
	//{
	//	stageClearTimer += DELTA;

	//	if (stageClearTimer >= 2.0f)
	//	{
	//		allEnemiesCleared = true;
	//		SCENE->ChangeScene("Title");
	//	}
	//}*/

	for (Enemy*& enemy : enemies)
	{
		enemy->Update();
	}

	// ���� ����ִ� �� ���� ���
	int aliveCount = 0;
	for (Enemy* enemy : enemies)
	{
		if (enemy->IsActive())
			aliveCount++;
	}
	enemyCount = aliveCount;

	// �Ϲ� �� ����
	spawnTimer += DELTA;
	if (spawnedEnemyCount < 2)
	{
		if (spawnTimer >= SPAWN_INTERVAL)
		{
			spawnTimer = 0.0f;

			if (SpawnEnemy3())
			{
				spawnedEnemyCount++;
			}

			if (spawnedEnemyCount >= 2)
			{
				IsAllEnemiesSpawned = true;
			}
		}
	}

	if (!isBossSpawned && enemyCount == 0 && IsAllEnemiesSpawned) {
		for (Enemy*& enemy : enemies) {
			if (!enemy->IsActive()) {
				enemy->SpawnBoss({ SCREEN_WIDTH / 2.0f, 150.0f });
				bossEnemy = enemy;
				isBossSpawned = true;
				break;
			}
		}
	}

	// ���� ���� ���� üũ
	if (isBossSpawned && bossEnemy && !bossEnemy->IsActive()) {
		if (!isBossDefeated) {
			isBossDefeated = true;
			stageClearTimer = 0.0f;
		}
	}

	// �� ��ȯ ó�� �߰�
	if (isBossDefeated) {
		stageClearTimer += DELTA;
		if (stageClearTimer >= 2.0f) {
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

	/*if (isBossSpawned && boss && boss->IsActive())
		boss->Render(hdc);*/

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
			enemy->Spawn2({ (float)randomX, 0 });
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
			enemy->Spawn3({ (float)randomX, 0 });
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
