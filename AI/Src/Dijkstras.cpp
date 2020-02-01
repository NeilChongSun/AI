#include"Precompiled.h"
#include"Dijkstras.h"

using namespace AI;

Path Dijkstras::Search(const Graph & graph,
	const Coord & start, const Coord end,
	std::function<bool(Coord)> isBlocked,
	std::function<float(Coord, Coord)> getCost)
{
	mOpenList.clear();
	mClosedList.clear();
	mParents.clear();
	mOpened.clear();
	mClosed.clear();
	//g.clear();

	const int nodeCount = graph.GetColumns()*graph.GetRows();
	mParents.resize(nodeCount);
	g.resize(nodeCount);
	mOpened.resize(nodeCount);
	mClosed.resize(nodeCount);

	//Add start to the open list;
	mOpenList.push_back(start);
	mOpened[graph.GetIndex(start)] = true;
	//Keep seraching until we are done
	bool found = false;
	while (!found && !mOpenList.empty())
	{
		//Pick the next node from the open list
		Coord current = mOpenList.front();
		mOpenList.pop_front();

		//If node is end, we are done
		if (current == end)
			found = true;

		//Else, expand node
		else
		{
			auto currentNode = graph.GetNode(current);
			for (auto neighbors : currentNode->neighbors)
			{
				const int neighborIndex = graph.GetIndex(neighbors);
				if (isBlocked(neighbors) || mClosed[neighborIndex])
					continue;
				const float cost = g[graph.GetIndex(current)] + getCost(current, neighbors);
				if (!mOpened[neighborIndex])
				{
					mOpened[neighborIndex] = true;
					mParents[neighborIndex] = current;
					g[neighborIndex] = cost;
					//Wrong! Cannot just add to back;
					//mOpenList.push_back(neighbors);
					for (auto it = mOpenList.begin(); it != mOpenList.end(); ++it)
					{
						auto list = *it;
						if (g[neighborIndex]<=getCost(current,neighbors))//cost<g(i)
						{

						}
					}
				}
				else if (cost < g[neighborIndex])
				{
					//update parents
					//update g
					//remobe and reinsert using new parent
				}
			}
		}
		//Close node
		mClosedList.push_back(current);
		mClosed[graph.GetIndex(current)] = true;
	}
	Path path;
	if (found)
	{
		std::list<Coord> trace;
		Coord next = end;
		while (next.IsValid())
		{
			trace.push_front(next);
			next = mParents[graph.GetIndex(next)];
		}
		path.reserve(trace.size());
		for (auto node : trace)
			path.push_back(node);
	}
	return path;
}
