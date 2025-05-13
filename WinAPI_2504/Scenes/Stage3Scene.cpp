#include "Framework.h"
#include "Stage3Scene.h"

Stage3Scene::Stage3Scene()
{
	skillCardScene = new SkillCardScene();
}

Stage3Scene::~Stage3Scene()
{
	delete skillCardScene;
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
	if (skillCardScene->IsActive())
	{
		skillCardScene->Update();
		return;
	}

	player->Update();

	BulletManager::Get()->Update();
	EnemyManager::Get()->Update();

	if (EnemyManager::Get()->IsBossDefeated()) 
		isBossDefeated = true;

	if (isBossDefeated) 
	{
		stageClearTimer += DELTA;
		if (stageClearTimer >= 2.0f) 
		{
			SCENE->ChangeScene("Title"); // Á÷Á¢ ¾À ÀüÈ¯
		}
	}
}

void Stage3Scene::Render(HDC hdc)
{
	player->Render(hdc);

	BulletManager::Get()->Render(hdc);
	EnemyManager::Get()->Render(hdc);

	if (skillCardScene->IsActive())
	{
		skillCardScene->Render(hdc);
		return;
	}
}

void Stage3Scene::Start()
{
	player = new Player();

	BulletManager::Get();
	EnemyManager::Get()->SetPlayer(player);
	EnemyManager::Get()->SetStage(3);

	skillCardScene->Show(player);
}

void Stage3Scene::End()
{
	delete player;

	BulletManager::Delete();
	EnemyManager::Delete();
}
