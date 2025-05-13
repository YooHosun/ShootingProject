#pragma once
#include "SKillCardScene.h"
class Stage3Scene : public Scene
{
public:
	Stage3Scene();
	~Stage3Scene();

	void Update() override;
	void Render(HDC hdc) override;

	void Start() override;
	void End() override;

private:
	Player* player;
	bool isBossDefeated = false;
	float stageClearTimer = 0.0f;

	SkillCardScene* skillCardScene;
};