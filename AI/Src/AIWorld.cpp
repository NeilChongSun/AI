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

uint32_t AIWorld::GetNextId()
{
	XASSERT(mNextId < UINT32_MAX, "Run out of ids!");
	return mNextId++;
}

void AIWorld::AddObstacles(const X::Math::Circle & circle)
{
	mOBstacles.push_back(circle);
}

void AIWorld::AddWall(const X::Math::LineSegment & wall)
{
	mWalls.push_back(wall);
}

void AIWorld::DebugDraw()
{
	{
		for (auto& obstical : mOBstacles)
		{
			X::DrawScreenCircle(obstical.center, obstical.radius, X::Colors::Cyan);
		}

		for (auto& wall : mWalls)
		{
			X::DrawScreenLine(wall.from, wall.to, X::Colors::Cyan);
		}

	}
}
