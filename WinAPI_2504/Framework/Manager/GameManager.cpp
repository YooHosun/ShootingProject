#include "Framework.h"

#include "Scenes/Stage1Scene.h"
#include "Scenes/TitleScene.h"
#include "Scenes/MenuScene.h"
#include "Scenes/Stage2Scene.h"
#include "Scenes/Stage3Scene.h"

GameManager::GameManager()
{
	hdc = GetDC(hWnd);	

	backBufferDC = CreateCompatibleDC(hdc);
	backBufferBitmap = CreateCompatibleBitmap(hdc, SCREEN_WIDTH, SCREEN_HEIGHT);
	SelectObject(backBufferDC, backBufferBitmap);

	Create();

	SCENE->AddScene("Title", new TitleScene());
	SCENE->AddScene("Game1", new Stage1Scene());
	SCENE->AddScene("Game2", new Stage2Scene());
	SCENE->AddScene("Game3", new Stage3Scene());
	SCENE->AddScene("Menu", new MenuScene());

	SCENE->ChangeScene("Title");
	SCENE->ChangeScene("Menu");
}

GameManager::~GameManager()
{
	ReleaseDC(hWnd, hdc);			

	Release();

	DeleteObject(backBufferBitmap);
	DeleteDC(backBufferDC);
}

void GameManager::Update()
{
	Timer::Get()->Update();
	Input::Get()->Update();

	SCENE->Update();

	InvalidateRect(hWnd, nullptr, false);
}

void GameManager::Render()
{
	PatBlt(backBufferDC, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, WHITENESS);	

	SCENE->Render(backBufferDC);
	Timer::Get()->Render(backBufferDC);

	BitBlt(hdc, 
		0, 0, SCREEN_WIDTH, SCREEN_HEIGHT,
		backBufferDC, 0, 0, SRCCOPY);
}

void GameManager::Create()
{
	Timer::Get();
	Input::Get();
	SceneManager::Get();
}

void GameManager::Release()
{
	Timer::Delete();
	Input::Delete();

	SceneManager::Delete();
}
