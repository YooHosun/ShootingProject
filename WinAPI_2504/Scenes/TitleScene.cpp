#include "Framework.h"
#include "TitleScene.h"

TitleScene::TitleScene()
{
}

TitleScene::~TitleScene()
{
}

void TitleScene::Update()
{
	if (Input::Get()->IsKeyDown(VK_F1))
	{
		SCENE->ChangeScene("Game");
	}

	if (Input::Get()->IsKeyDown(VK_F2))
	{
		SCENE->ChangeScene("Game2");
	}

	if (Input::Get()->IsKeyDown(VK_F5))
	{
		SCENE->ChangeScene("Menu");
	}
}

void TitleScene::Render(HDC hdc)
{
	TextOut(hdc, 100, 100, L"Title Scene", 12);
}
