#pragma once
#include"Common.h"
namespace AI
{
	struct Coord
	{
		int x = -1;
		int y = -1;
		bool IsValid() const
		{
			return x != -1 & y != -1;
		}
		bool operator==(const Coord& rhs)const
		{
			return x == rhs.x && y == rhs.y;
		}
	};

	using Path = std::vector<Coord>;

	class Graph
	{
	public:
		struct Node
		{
			std::vector<Coord> neighbors;
		};
		void Load(int columns, int rows);
		void Resize(int columns, int rows);
		Node* GetNode(const Coord& coord);
		const Node* GetNode(const Coord& coord) const;
		int GetColumns()const { return mColumns; }
		int GetRows()const { return mRows; }
		std::vector<Node> GetNodes()const { return mNodes; }
		int GetIndex(Coord coord)const;
		void SetObstacles(std::vector<bool> isObstacle);
	private:
		std::vector<Node> mNodes;
		std::vector<bool> mObstacles;
		int mColumns;
		int mRows;
	};
}