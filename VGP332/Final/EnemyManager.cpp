#include "EnemyManager.h"
namespace
{
	EnemyManager* sInstance = nullptr;
	AI::AIWorld world;
}
void EnemyManager::StaticInitialize()
{
	XASSERT(sInstance == nullptr, "Already initialized!");
	sInstance = new EnemyManager();
}

void EnemyManager::StaticTerminate()
{
	delete sInstance;
	sInstance = nullptr;
}

EnemyManager & EnemyManager::Get()
{
	XASSERT(sInstance != nullptr, "No created!");
	return *sInstance;
}

void EnemyManager::Load()
{
	for (int i = 0; i < mEnemiesCount; i++)
	{
		Enemy* enemy = new Enemy(world);
		enemy->Load();
		mEnemies.push_back(enemy);
	}
	mPositions.resize(mEnemies.size());
}

void EnemyManager::Unload()
{
}

void EnemyManager::Update(float deltaTime)
{
	for (auto enemy : mEnemies)
	{
		enemy->Update(deltaTime);
	}
	for (int i = 0; i < mEnemies.size(); i++)
	{
		mPositions[i] = mEnemies[i]->position;
	}
}

void EnemyManager::Render()
{
	for (auto enemy : mEnemies)
	{
		enemy->Render();
	}
}
