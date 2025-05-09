#pragma once

class EnemyManager : public Singleton<EnemyManager>
{
	friend class Singleton;
private:
	const int ENEMY_POOL_SIZE = 50;
	const float SPAWN_INTERVAL = 1.0f;

private:
	EnemyManager();
	~EnemyManager();

public:
	void Update();
	void Update2();
	void Update3();
	void Render(HDC hdc);

	bool SpawnEnemy();
	bool SpawnEnemy2();
	bool SpawnEnemy3();

	void SetPlayer(Player* player);
	void SetEnemyCount(int count) { enemyCount = count; }
	bool AreAllEnemiesDead();


	RECT rect;

private:
	vector<Enemy*> enemies;
	float spawnTimer = 0.0f;
	int enemyCount = 0;
	int spawnedEnemyCount = 0;

	const float spawnInterval = 2.0f;
	bool allEnemiesCleared = false;
	bool stageClearTriggered = false;
	bool IsAllEnemiesSpawned = false;

	float stageClearTimer = 0.0f;
};