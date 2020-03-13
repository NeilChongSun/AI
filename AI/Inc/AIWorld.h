#pragma once

#include"Agent.h"
#include "PartitionGrid.h"

namespace AI
{
	class AIWorld
	{
	public:

		struct Settings
		{
			X::Math::Vector2 worldSize = { 0.0f,0.0f };
			float partitionGridSize = 0.0f;
		};


		using Obstacles = std::vector<X::Math::Circle>;
		using Walls = std::vector<X::Math::LineSegment>;

		void Initialize(const Settings& settings);
		void Update();

		void RegisterEnetity(Entity* eneity);
		void UnregisterEnetity(Entity* enetity);

		uint32_t GetNextId();
		
		void AddObstacles(const X::Math::Circle& circle);
		void AddWall(const X::Math::LineSegment& wall);

		bool HasLineOfSight(const X::Math::Vector2& start, const X::Math::Vector2& end) const
		{
			X::Math::LineSegment line{ start,end };
			for (auto& wall : mWalls)
			{
				if (X::Math::Intersect(line,wall))
					return false;
			}
			for (auto& Obstacles : mOBstacles)
			{
				if (X::Math::Intersect(line,Obstacles))
				{
					return false;
				}
			}
			return true;
		}

		EntityList GetEntities(const X::Math::Circle& range, int typeId);
		AgentList GetNeighborhood(const X::Math::Circle& range, int typeId);
		
		void DebugDraw();

		const Obstacles& GetObstacles() const { return mObstacles; }
		const Walls& GetWalls() const { return mWalls; }

	private:
		Obstacles mOBstacles;
		Walls mWalls;
		Entities mEntities;
		uint32_t mNextId = 0;
		Settings mSetting;
		Obstacles mObstacles;
		PartitionGrid<Entity> mPartitionGrid;
		
	};
}