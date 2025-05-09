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

	Vector2 pivotCenter;         // ���� �߽��� (ȸ��, �簢, ���̺� ��� ���)
	Vector2 pivotDir = Vector2::Down(); // �߽��� �̵� ���� (���� or �¿�)
	float pivotAngle = 0.0f;     // ȸ�� ���� (��� Ÿ�� ����)
	float pivotRadius = 50.0f;   // ��/�׸� ������ or ����
	float pivotSpeed = 1.0f;     // ȸ�� �Ǵ� ���� �ӵ�

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