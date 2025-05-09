#include "Framework.h"
#include "Stage3Scene.h"

Stage3Scene::Stage3Scene()
{

}

Stage3Scene::~Stage3Scene()
{

}

void Stage3Scene::Update()
{
	if (Input::Get()->IsKeyDown(VK_F1))
	{
		SCENE->ChangeScene("Game1");

	}if (Input::Get()->IsKeyDown(VK_F2))
	{
		SCENE->ChangeScene("Game2");
	}

	if (Input::Get()->IsKeyDown(VK_F4))
	{
		SCENE->ChangeScene("Title");
	}

	if (Input::Get()->IsKeyDown(VK_F5))
	{
		SCENE->ChangeScene("Menu");
	}

	player->Update();

	BulletManager::Get()->Update();
	EnemyManager::Get()->Update3();
}

void Stage3Scene::Render(HDC hdc)
{
	player->Render(hdc);

	BulletManager::Get()->Render(hdc);
	EnemyManager::Get()->Render(hdc);
}

void Stage3Scene::Start()
{
	player = new Player();

	BulletManager::Get();
	EnemyManager::Get()->SetPlayer(player);
}

void Stage3Scene::End()
{
	delete player;

	BulletManager::Delete();
	EnemyManager::Delete();
}
