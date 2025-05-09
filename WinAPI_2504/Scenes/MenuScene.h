#pragma once

class MenuScene : public Scene
{
public:
	MenuScene();
	~MenuScene();

	// Scene을(를) 통해 상속됨
	void Update() override;
	void Render(HDC hdc) override;

private:
	RECT gameStartRect;

	RECT rect;
	SIZE textSize;

	POINT pt;
};