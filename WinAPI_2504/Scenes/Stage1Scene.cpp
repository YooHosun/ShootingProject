#include "Framework.h"
#include "Stage1Scene.h"

Stage1Scene::Stage1Scene()
{
	
}

Stage1Scene::~Stage1Scene()
{	
	
}

void Stage1Scene::Update()
{
	if (Input::Get()->IsKeyDown(VK_F2))
	{
		SCENE->ChangeScene("Game2");
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

void Stage1Scene::Render(HDC hdc)
{
	player->Render(hdc);

	BulletManager::Get()->Render(hdc);
	EnemyManager::Get()->Render(hdc);
}

void Stage1Scene::Start()
{
	player = new Player();

	BulletManager::Get();
	EnemyManager::Get()->SetPlayer(player);
	EnemyManager::Get()->SetStage(1);
}

void Stage1Scene::End()
{
	delete player;

	BulletManager::Delete();
	EnemyManager::Delete();
}
