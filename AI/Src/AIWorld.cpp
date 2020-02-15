#include"Precompiled.h"
#include"AIWorld.h"

using namespace AI;

void AIWorld::RegisterEnetity(Entity* entity)
{
	mEntities.push_back(entity);
}

void AIWorld::UnregisterEnetity(Entity* entity)
{
	auto iter = std::find(mEntities.begin(), mEntities.end(), entity);
	if (iter!=mEntities.end())
	{
		std::iter_swap(iter, mEntities.end() - 1);
		mEntities.pop_back();
	}
}