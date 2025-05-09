#pragma once

class TitleScene : public Scene
{
public:
	TitleScene();
	~TitleScene();

	// Scene을(를) 통해 상속됨
	void Update() override;
	void Render(HDC hdc) override;
};