#pragma once

class Stage1Scene : public Scene
{
public:
	Stage1Scene();
	~Stage1Scene();

	void Update() override;
	void Render(HDC hdc) override;

	void Start() override;
	void End() override;

private:
	Player* player;	
};