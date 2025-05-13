#include "Framework.h"
#include "Stage2Scene.h"

Stage2Scene::Stage2Scene()
{
}

Stage2Scene::~Stage2Scene()
{
}

void Stage2Scene::Update()
{
	if (Input::Get()->IsKeyDown(VK_F1))
	{
		SCENE->ChangeScene("Game1");
	}
	
	if (Input::Get()->IsKeyDown(VK_F3))
	{
		SCENE->ChangeScene("Game3");
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
	EnemyManager::Get()->Update();
}

void Stage2Scene::Render(HDC hdc)
{
	player->Render(hdc);

	BulletManager::Get()->Render(hdc);
	EnemyManager::Get()->Render(hdc);
}

void Stage2Scene::Start()
{
	player = new Player();

	BulletManager::Get();
	EnemyManager::Get()->SetPlayer(player);
	EnemyManager::Get()->SetStage(2);
}

void Stage2Scene::End()
{
	delete player;

	BulletManager::Delete();
	EnemyManager::Delete();
}

