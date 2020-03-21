#include "PickupManager.h"
#include"Ship.h"
#include<AI.h>
namespace
{
	PickupManager* sInstance = nullptr;
	AI::AIWorld world;
}
void PickupManager::StaticInitialize()
{
	XASSERT(sInstance == nullptr, "Already initialized!");
	sInstance = new PickupManager();
}

void PickupManager::StaticTerminate()
{
	delete sInstance;
	sInstance = nullptr;
}

PickupManager & PickupManager::Get()
{
	XASSERT(sInstance != nullptr, "No created!");
	return *sInstance;
}

void PickupManager::Load()
{
	for (int i = 0; i < mPickupsCount; i++)
	{
		Pickups* pickup = new Pickups(world);
		pickup->Load();
		mPickups.push_back(pickup);		
	}
	mPositions.resize(mPickups.size());
	Ship::Get().ResizeDP(mPickups.size());
}

void PickupManager::Unload()
{
}

void PickupManager::Update(float deltaTime)
{
	for (auto iter = mPickups.begin(); iter != mPickups.end();)
	{
		Pickups* pickup = (*iter);
		if (!pickup->Destroy())
		{
			pickup->Update(deltaTime);
		}

		if (pickup->Destroy())
		{
			delete pickup;
			iter = mPickups.erase(iter);
			mPositions.resize(mPickups.size());
			Ship::Get().ResizeDP(mPickups.size());
		}
		else
			++iter;
	}

	for (int i = 0; i < mPickups.size(); i++)
	{
		//mPickups[i]->Update(deltaTime);
		mPositions[i]=mPickups[i]->position;
	}
}

void PickupManager::Render()
{
	for (auto pickup:mPickups)
	{
		pickup->Render();
	}
}
