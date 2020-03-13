#include"Precompiled.h"
#include"AIWorld.h"

using namespace AI;

namespace // internal link
{
	template<class Element>
	std::vector<Element*> GetElements(const PartitionGrid<Entity>& gird, const X::Math::Circle& range, float cellsize, uint32_t typeId)
	{
		std::vector<Element*> elements;

		int minX = static_cast<int>((range.center.x - range.radius) / cellsize);
		int maxX = static_cast<int>((range.center.x + range.radius) / cellsize);
		int minY = static_cast<int>((range.center.y - range.radius) / cellsize);
		int maxY = static_cast<int>((range.center.y + range.radius) / cellsize);

		minX = X::Math::Max(minX, 0);
		maxX = X::Math::Min(maxX, gird.GetColumns() - 1);
		minY = X::Math::Max(minY, 0);
		maxY = X::Math::Min(maxY, gird.GetRows() - 1);

		for (int y = 0; y <= maxY; ++y)
		{
			for (int x = 0; x <= maxX; ++x)
			{
				auto& cell = gird.GetCell(x, y);
				for (auto& element : cell)
				{
					if (element->GetTypeId() == typeId)
						elements.push_back(static_cast<Element*>(element));
				}
			}
		}

		return elements;
	}
}

void AIWorld::Initialize(const Settings& settings)
{
	mSetting = settings;
	XASSERT(settings.partitionGridSize > 0.0f, "[AIWorld] Partition gird size must be greater than zero");
	const int columns = static_cast<int>(std::ceilf(settings.worldSize.x / settings.partitionGridSize));
	const int rows = static_cast<int>(std::ceilf(settings.worldSize.y / settings.partitionGridSize));
	mPartitionGrid.Resize(columns, rows);
}

void AIWorld::Update()
{
	mPartitionGrid.ClearCells();
	for (auto entity : mEntities)
	{
		int column = static_cast<int>(entity->position.x / mSetting.partitionGridSize);
		int row = static_cast<int>(entity->position.y / mSetting.partitionGridSize);
		mPartitionGrid.GetCell(column, row).push_back(entity);
	}
}

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

EntityList AIWorld::GetEntities(const X::Math::Circle & range, int typeId)
{
	return GetElements<Entity>(mPartitionGrid, range, mSetting.partitionGridSize, typeId);
}

AgentList AIWorld::GetNeighborhood(const X::Math::Circle & range, int typeId)
{
	return GetElements<Agent>(mPartitionGrid, range, mSetting.partitionGridSize, typeId);
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
