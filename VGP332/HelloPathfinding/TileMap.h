#pragma once

#include<XEngine.h>
#include<AI.h>
class TileMap
{
public:
	void Load();
	void Unload();
	void Update(float deltaTime);
	void Render() const;
private:
	int GetIndex(int x, int y) const;
	X::Math::Vector2 GetPosition(AI::Coord coord) const;

	std::array<X::TextureId,7> mTextureIds;
	std::vector<int> mTiles;
	int mColumns = 0;
	int mRows = 0;
	int mTileSize = 32;
	AI::Graph mGraph;
	std::vector<AI::Graph::Node> mNodes;
	AI::Coord mStartPoint;
	AI::Coord mEndPoint;
	X::Math::Vector2 mOffset = { static_cast<float>(mTileSize / 2),static_cast<float>(mTileSize / 2) };
	std::vector<AI::Coord> mPath;
	std::list<AI::Coord> mCloseList;
	std::vector<AI::Coord> mParents;
	AI::BFS mBFS;

};