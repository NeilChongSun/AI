#include<XEngine.h>
#include"Ship.h"
#include"PickupManager.h"
#include"EnemyManager.h"
void GameInit()
{
	Ship::StaticInitialize();
	PickupManager::StaticInitialize();
	EnemyManager::StaticInitialize();
	Ship::Get().Load();
	EnemyManager::Get().SetEnemyiesCount(1);
	PickupManager::Get().SetPickupsCount(1);
	PickupManager::Get().Load();
	EnemyManager::Get().Load();
}

void GameCleanup()
{
	PickupManager::StaticTerminate();
	Ship::StaticTerminate();
	EnemyManager::StaticTerminate();
}

bool GameLoop(float deltaTime)
{
	Ship::Get().Update(deltaTime);
	Ship::Get().Render();
	PickupManager::Get().Update(deltaTime);
	PickupManager::Get().Render();
	EnemyManager::Get().Update(deltaTime);
	EnemyManager::Get().Render();
	return X::IsKeyPressed(X::Keys::ESCAPE);
}

int WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	X::Start();
	GameInit();
	X::Run(GameLoop);
	GameCleanup();
	X::Stop();
	return 0;
}