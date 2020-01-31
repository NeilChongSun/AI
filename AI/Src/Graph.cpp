#include"Precompiled.h"
#include "Graph.h"

using namespace AI;

void AI::Graph::Load(int columns, int rows)
{
	mObstacles.resize(columns*rows);
	Resize(columns, rows);
}

void Graph::Resize(int columns, int rows)
{
	mColumns = columns;
	mRows = rows;
	mNodes.clear();
	mNodes.resize(columns*rows);
	for (int y = 0; y < rows; y++)
	{
		for (int x = 0; x < columns; x++)
		{
			//Homework: Connect neighbors to each node (up to 8, mabe less)
			//Good Way
			int index = GetIndex(Coord{ x,y });

			for (int v = y - 1; v <= y + 1; v++)
			{
				for (int h = x - 1; h <= x + 1; h++)
				{
					if (v >= 0 && h >= 0 && (v != y || h != x) && v < rows && h < columns && !mObstacles[GetIndex (Coord{h,v})])
					{
						if (!mObstacles[index])
						{
							mNodes[index].neighbors.push_back(Coord{ h,v });
						}
					}
				}
			}
			//Bad Way
			//if (y == 0 && x == 0)
			//{
			//	mNodes[index].neighbors.push_back(Coord{ x + 1,y });
			//	mNodes[index].neighbors.push_back(Coord{ x + 1,y + 1 });
			//	mNodes[index].neighbors.push_back(Coord{ x,y + 1 });
			//}
			//else if (y == 0 && x == columns - 1)
			//{
			//	mNodes[index].neighbors.push_back(Coord{ x - 1,y });	 //Left
			//	mNodes[index].neighbors.push_back(Coord{ x - 1,y + 1 }); //Left Buttom
			//	mNodes[index].neighbors.push_back(Coord{ x ,y + 1 });	 //Buttom
			//}
			//else if (y == 0 && x != 0 && x != columns - 1)
			//{
			//	mNodes[index].neighbors.push_back(Coord{ x - 1,y });	 //Left
			//	mNodes[index].neighbors.push_back(Coord{ x + 1,y });	 //Right
			//	mNodes[index].neighbors.push_back(Coord{ x - 1,y + 1 }); //Left Buttom
			//	mNodes[index].neighbors.push_back(Coord{ x ,y + 1 });	 //Buttom
			//	mNodes[index].neighbors.push_back(Coord{ x + 1 ,y + 1 });//Right Buttom
			//}
			//else if (y == rows - 1 && x == 0)
			//{
			//	mNodes[index].neighbors.push_back(Coord{ x,y - 1 });	 //Top
			//	mNodes[index].neighbors.push_back(Coord{ x + 1,y - 1 }); //Right Top
			//	mNodes[index].neighbors.push_back(Coord{ x + 1,y });	 //Right
			//}
			//else if (y == rows - 1 && x == columns - 1)
			//{
			//	mNodes[index].neighbors.push_back(Coord{ x - 1,y - 1 }); //Left Top    
			//	mNodes[index].neighbors.push_back(Coord{ x,y - 1 });	 //Top
			//	mNodes[index].neighbors.push_back(Coord{ x - 1,y });	 //Left
			//}
			//else if (y == rows - 1 && x != 0 && x != columns - 1)
			//{
			//	mNodes[index].neighbors.push_back(Coord{ x - 1,y - 1 }); //Left Top    
			//	mNodes[index].neighbors.push_back(Coord{ x,y - 1 });	 //Top
			//	mNodes[index].neighbors.push_back(Coord{ x + 1,y - 1 }); //Right Top
			//	mNodes[index].neighbors.push_back(Coord{ x - 1,y });	 //Left
			//	mNodes[index].neighbors.push_back(Coord{ x + 1,y });	 //Right
			//}
			//else if (y != 0 && y != rows - 1 && x == 0)
			//{
			//	mNodes[index].neighbors.push_back(Coord{ x,y - 1 });	 //Top
			//	mNodes[index].neighbors.push_back(Coord{ x + 1,y - 1 }); //Right Top
			//	mNodes[index].neighbors.push_back(Coord{ x + 1,y });	 //Right
			//	mNodes[index].neighbors.push_back(Coord{ x ,y + 1 });	 //Buttom
			//	mNodes[index].neighbors.push_back(Coord{ x + 1 ,y + 1 });//Right Buttom
			//}
			//else if (y != 0 && y != rows - 1 && x == columns - 1)
			//{
			//	mNodes[index].neighbors.push_back(Coord{ x - 1,y - 1 }); //Left Top    
			//	mNodes[index].neighbors.push_back(Coord{ x,y - 1 });	 //Top
			//	mNodes[index].neighbors.push_back(Coord{ x - 1,y });	 //Left
			//	mNodes[index].neighbors.push_back(Coord{ x - 1,y + 1 }); //Left Buttom
			//	mNodes[index].neighbors.push_back(Coord{ x ,y + 1 });	 //Buttom
			//}
			//else
			//{
			//	mNodes[index].neighbors.push_back(Coord{ x - 1,y - 1 }); //Left Top    
			//	mNodes[index].neighbors.push_back(Coord{ x,y - 1 });	 //Top
			//	mNodes[index].neighbors.push_back(Coord{ x + 1,y - 1 }); //Right Top
			//	mNodes[index].neighbors.push_back(Coord{ x - 1,y });	 //Left
			//	mNodes[index].neighbors.push_back(Coord{ x + 1,y });	 //Right
			//	mNodes[index].neighbors.push_back(Coord{ x - 1,y + 1 }); //Left Buttom
			//	mNodes[index].neighbors.push_back(Coord{ x ,y + 1 });	 //Buttom
			//	mNodes[index].neighbors.push_back(Coord{ x + 1 ,y + 1 });//Right Buttom
			//}
		}
	}
}
Graph::Node* Graph::GetNode(const Coord& coord)
{
	return const_cast<Node*>(static_cast<const Graph*>(this)->GetNode(coord));
}

const Graph::Node* Graph::GetNode(const Coord& coord) const
{
	//Homework: Do bound check, then either return & of node, or nullptr
	int index = GetIndex(coord);
	if (coord.x >= 0 && coord.x < mColumns&&coord.y >= 0 && coord.y < mRows)
	{
		if (coord.x >= 0 && coord.x < mColumns&&coord.y >= 0 && coord.y < mRows)
		{
			return &mNodes[index];
		}
		return nullptr;
	}
}

int Graph::GetIndex(Coord coord)const
{
	return coord.x + (coord.y*mColumns);
}

void AI::Graph::SetObstacles(std::vector<bool> isObstacle)
{
	mObstacles = isObstacle;
}



