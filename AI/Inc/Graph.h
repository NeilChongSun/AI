#pragma once
#include"Common.h"
namespace AI
{
	struct Coord
	{
		int x, y;
	};
	class Graph
	{
	public:
		struct Node
		{
			std::vector<Coord> neighbors;
		};

		inline void Resize(int columns, int rows);
		Node* GetNode(Coord coord) { int index = GetIndex(coord); return &mNodes[index]; }

		int GetColumns()const { return mColumns; }
		int GetRows()const { return mRows; }
	private:
		inline int GetIndex(Coord coord)const;
		std::vector<Node> mNodes;
		int mColumns;
		int mRows;
	};

	void Graph::Resize(int columns, int rows)
	{
		mColumns = columns;
		mRows = rows;
		mNodes.resize(columns*rows);

		for (int y = 0; y < rows; y++)
		{
			for (int x = 0; x < columns; x++)
			{
				//Homework: Connect neighbors to each node (up to 8, mabe less)
				int index = GetIndex(Coord{ x,y });

				if (y == 0 && x == 0)
				{
					mNodes[index].neighbors.push_back(Coord{ x + 1,y });
					mNodes[index].neighbors.push_back(Coord{ x + 1,y + 1 });
					mNodes[index].neighbors.push_back(Coord{ x,y + 1 });
				}
				else if (y == 0 && x == columns - 1)
				{
					mNodes[index].neighbors.push_back(Coord{ x - 1,y });	 //Left
					mNodes[index].neighbors.push_back(Coord{ x - 1,y + 1 }); //Left Buttom
					mNodes[index].neighbors.push_back(Coord{ x ,y + 1 });	 //Buttom
				}
				else if (y == 0 && x != 0 && x != columns - 1)
				{
					mNodes[index].neighbors.push_back(Coord{ x - 1,y });	 //Left
					mNodes[index].neighbors.push_back(Coord{ x + 1,y });	 //Right
					mNodes[index].neighbors.push_back(Coord{ x - 1,y + 1 }); //Left Buttom
					mNodes[index].neighbors.push_back(Coord{ x ,y + 1 });	 //Buttom
					mNodes[index].neighbors.push_back(Coord{ x + 1 ,y + 1 });//Right Buttom
				}
				else if (y == rows - 1 && x == 0)
				{
					mNodes[index].neighbors.push_back(Coord{ x,y - 1 });	 //Top
					mNodes[index].neighbors.push_back(Coord{ x + 1,y - 1 }); //Right Top
					mNodes[index].neighbors.push_back(Coord{ x + 1,y });	 //Right
				}
				else if (y == rows - 1 && x == columns - 1)
				{
					mNodes[index].neighbors.push_back(Coord{ x - 1,y - 1 }); //Left Top    
					mNodes[index].neighbors.push_back(Coord{ x,y - 1 });	 //Top
					mNodes[index].neighbors.push_back(Coord{ x - 1,y });	 //Left
				}
				else if (y == rows - 1 && x != 0 && x != columns - 1)
				{
					mNodes[index].neighbors.push_back(Coord{ x - 1,y - 1 }); //Left Top    
					mNodes[index].neighbors.push_back(Coord{ x,y - 1 });	 //Top
					mNodes[index].neighbors.push_back(Coord{ x + 1,y - 1 }); //Right Top
					mNodes[index].neighbors.push_back(Coord{ x - 1,y });	 //Left
					mNodes[index].neighbors.push_back(Coord{ x + 1,y });	 //Right
				}
				else if (y != 0 && y != rows - 1 && x == 0)
				{
					mNodes[index].neighbors.push_back(Coord{ x,y - 1 });	 //Top
					mNodes[index].neighbors.push_back(Coord{ x + 1,y - 1 }); //Right Top
					mNodes[index].neighbors.push_back(Coord{ x + 1,y });	 //Right
					mNodes[index].neighbors.push_back(Coord{ x ,y + 1 });	 //Buttom
					mNodes[index].neighbors.push_back(Coord{ x + 1 ,y + 1 });//Right Buttom
				}
				else if (y != 0 && y != rows - 1 && x == columns - 1)
				{
					mNodes[index].neighbors.push_back(Coord{ x - 1,y - 1 }); //Left Top    
					mNodes[index].neighbors.push_back(Coord{ x,y - 1 });	 //Top
					mNodes[index].neighbors.push_back(Coord{ x - 1,y });	 //Left
					mNodes[index].neighbors.push_back(Coord{ x - 1,y + 1 }); //Left Buttom
					mNodes[index].neighbors.push_back(Coord{ x ,y + 1 });	 //Buttom
				}
				else
				{
					mNodes[index].neighbors.push_back(Coord{ x - 1,y - 1 }); //Left Top    
					mNodes[index].neighbors.push_back(Coord{ x,y - 1 });	 //Top
					mNodes[index].neighbors.push_back(Coord{ x + 1,y - 1 }); //Right Top
					mNodes[index].neighbors.push_back(Coord{ x - 1,y });	 //Left
					mNodes[index].neighbors.push_back(Coord{ x + 1,y });	 //Right
					mNodes[index].neighbors.push_back(Coord{ x - 1,y + 1 }); //Left Buttom
					mNodes[index].neighbors.push_back(Coord{ x ,y + 1 });	 //Buttom
					mNodes[index].neighbors.push_back(Coord{ x + 1 ,y + 1 });//Right Buttom
				}
			}
		}
	}
	//Graph::Node* GetNode(Coord coord)
	//{
	//	//Homework: Do bound check, then either return & of node, or nullptr
	//}

	int Graph::GetIndex(Coord coord)const
	{
		return coord.x + (coord.y*mColumns);
	}
}