#pragma once
#include "SKillCardScene.h"
class Stage2Scene : public Scene
{
public:
	Stage2Scene();
	~Stage2Scene();

	void Update() override;
	void Render(HDC hdc) override;

	void Start() override;
	void End() override;

private:
	Player* player;

	SkillCardScene* skillCardScene;
};