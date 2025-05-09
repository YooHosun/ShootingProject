#pragma once

class Enemy : public Circle
{
private:
	const int SPEED = 200;
	const int MAX_HP = 30;
	const float DAMAGE_INTERVAL = 0.1f;
	const float FIRE_INTERVAL = 1.0f;
	const int FIRE_COUNT = 10;

public:
	Enemy();
	~Enemy();

	enum class EnemyColor
	{
		Red = RGB(255, 0, 0),
		Green = RGB(0, 255, 0),
		Blue = RGB(0, 0, 255),
		Yellow = RGB(255, 255, 0),
		Cyan = RGB(0, 255, 255),
		Magenta = RGB(255, 0, 255),
		End
	};

	enum class EnemyShootingType
	{
		Single,
		Spread,
		Wave,
		End
	};

	enum class EnemyMoveType
	{
		Linear,
		Circular,
		Rectangular,
		Sine,
		End
	};

	void Update();
	void Render(HDC hdc);

	void Spawn(Vector2 pos);
	void Spawn2(Vector2 pos);
	void Spawn3(Vector2 pos);


	void SetPlayer(Player* player) { this->player = player; }

private:
	void Damage();
	void Move();
	void Fire();

private:
	int hp = 0;
	float angle = 0;
	float damageTimer = 0;
	float fireTimer = 0;
	bool isDamaged = false;

	Vector2 pivotCenter;         // 기준 중심점 (회전, 사각, 웨이브 모두 사용)
	Vector2 pivotDir = Vector2::Down(); // 중심의 이동 방향 (상하 or 좌우)
	float pivotAngle = 0.0f;     // 회전 각도 (모든 타입 공용)
	float pivotRadius = 50.0f;   // 원/네모 반지름 or 진폭
	float pivotSpeed = 1.0f;     // 회전 또는 파형 속도

	bool isWaveFiring = false;
	int waveShotCount = 0;
	float waveFireTimer = 0.0f;
	float waveBaseAngle = 0.0f;

	EnemyColor color;
	EnemyShootingType shootingType;
	EnemyMoveType moveType;

	HBRUSH hRedBrush;
	HBRUSH hBlueBrush;
	HBRUSH hGreenBrush;
	HBRUSH hYellowBrush;
	HBRUSH hCyanBrush;
	HBRUSH hMagentaBrush;
	HBRUSH hSelectBrush;

	Player* player = nullptr;;

	Vector2 direction = Vector2::Up();
};