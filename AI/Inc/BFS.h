#pragma once

#include"Graph.h"

namespace AI
{
	class BFS
	{
	public:

		Path Search(const Graph& graph, const Coord& start, const Coord end);
		std::list<Coord> GetClosedList() const { return mClosedList; }
		std::vector<Coord> GetParents() const { return mParents; }
	private:
		std::list<Coord> mOpenList;
		std::list<Coord> mClosedList;
		std::vector<Coord> mParents;
		std::vector<bool> mOpened;
		std::vector<bool> mClosed;
	};
}