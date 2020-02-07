#pragma once
#include<XEngine.h>
#include<AI.h>
enum ESearchMode
{
	eBFS,
	eDFS,
	eDijkstars,
	eAStar
};
enum EMouseClick
{
	eSetStart,
	eSetEnd,
	eSetTile
};
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
	AI::Coord GetClickPosition()const;
	bool CheckClick() const;
	int mClickIndex;
	void ShowDebugUI();

	std::array<X::TextureId, 9> mTextureIds;
	std::vector<int> mTiles;
	int mCurrentTile;

	int mColumns = 0;
	int mRows = 0;
	int mTileSize = 32;

	std::vector<AI::Graph::Node> mNodes;

	AI::Graph mGraph;
	AI::Coord mStartPoint = { 0,0 };
	AI::Coord mEndPoint = { 0,1 };
	AI::Coord mClickPos;
	X::Math::Vector2 mOffset = { static_cast<float>(mTileSize / 2),static_cast<float>(mTileSize / 2) };

	std::vector<AI::Coord> mPath;
	std::list<AI::Coord> mCloseList;
	std::vector<AI::Coord> mParents;

	AI::BFS mBFS;
	AI::DFS mDFS;
	AI::Dijkstras mDijkstras;
	AI::AStar mAStar;

	const char* mSearchModeText="";
	const char* mCurrentClickText="";

	ESearchMode mSearchMode;
	EMouseClick mMouseClick;

	bool mDraw = false;
};