#include"Precompiled.h"
#include"DFS.h"

using namespace AI;

Path DFS::Search(const Graph & graph, const Coord & start, const Coord end)
{
	mOpenList.clear();
	mClosedList.clear();
	mParents.clear();
	mOpened.clear();
	mClosed.clear();
	mParents.resize(graph.GetColumns()*graph.GetRows());
	mOpened.resize(graph.GetColumns()*graph.GetRows());
	mClosed.resize(graph.GetColumns()*graph.GetRows());

	//Add start to the open list;
	mOpenList.push_back(start);
	mOpened[graph.GetIndex(start)] = true;
	//Keep seraching until we are done
	bool found = false;
	while (!found && !mOpenList.empty())
	{
		//Pick the next node from the open list
		//Coord current = mOpenList.front();
		Coord current = mOpenList.back();
		//mOpenList.pop_front();
		mOpenList.pop_back();
		
		//If node is end, we are done
		if (current == end)
			found = true;

		//Else, expand node
		else
		{
			auto currentNode = graph.GetNode(current);
			for (auto neighbors:currentNode->neighbors)
			{
				int neighborIndex = graph.GetIndex(neighbors);
				if (!mOpened[neighborIndex])
				{
					mOpenList.push_back(neighbors);
					mOpened[graph.GetIndex(neighbors)] = true;
					mParents[neighborIndex]=current;
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
		for (auto node: trace)
			path.push_back(node);
	}
	return path;
}
