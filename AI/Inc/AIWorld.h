#pragma once

#include"Entity.h"

namespace AI
{
	class AIWorld
	{
	public:
		using Obstacles = std::vector<X::Math::Circle>;
		using Walls = std::vector<X::Math::LineSegment>;

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

		void DebugDraw();

	private:
		Obstacles mOBstacles;
		Walls mWalls;
		Entities mEntities;
		uint32_t mNextId = 0;
	};
}