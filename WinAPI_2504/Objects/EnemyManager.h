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
	struct EnemySpawnData
	{
		Enemy::EnemyColor color;
		Enemy::EnemyShootingType shootingType;
		Enemy::EnemyMoveType moveType;
		Vector2 pivotDir;
		int hp;
		int spawnCount;
		bool hasBoss;
	};

public:
	void Update();
	void Render(HDC hdc);

	bool SpawnEnemy(const EnemySpawnData& data);

	void SetPlayer(Player* player);
	void SetEnemyCount(int count) { enemyCount = count; }
	void SetStage(int stage) { currentStage = stage; }
	bool IsBossDefeated() const { return isBossDefeated; }
	void Reset();
	bool AreAllEnemiesDead();


	RECT rect;

private:
	vector<Enemy*> enemies;
	std::unordered_map<int, EnemySpawnData> stageData;
	float spawnTimer = 0.0f;
	int enemyCount = 0;
	int spawnedEnemyCount = 0;
	int currentStage = 1;

	const float spawnInterval = 2.0f;
	bool allEnemiesCleared = false;
	bool stageClearTriggered = false;
	bool IsAllEnemiesSpawned = false;

	float stageClearTimer = 0.0f;
	bool isBossSpawned = false;
	bool isBossDefeated = false;
	Enemy* bossEnemy = nullptr;
};