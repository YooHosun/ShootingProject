#pragma once

class MenuScene : public Scene
{
public:
	MenuScene();
	~MenuScene();

	// Scene��(��) ���� ��ӵ�
	void Update() override;
	void Render(HDC hdc) override;

private:
	RECT gameStartRect;

	RECT rect;
	SIZE textSize;

	POINT pt;
};