#include "TileMap.h"
void TileMap::Load()
{
	mTextureIds[0] = X::LoadTexture("grass.png");
	mTextureIds[1] = X::LoadTexture("stone.png");
	mTextureIds[2] = X::LoadTexture("tree0.png");
	mTextureIds[3] = X::LoadTexture("tree1.png");
	mTextureIds[4] = X::LoadTexture("tree2.png");
	mTextureIds[5] = X::LoadTexture("tree3.png");
	mTextureIds[6] = X::LoadTexture("flower.png");

	mColumns = 25;
	mRows = 20;

	mTiles.resize(mColumns*mRows, 0);
}

void TileMap::Unload()
{

}

void TileMap::Update(float deltaTime)
{
	mGraph.Resize(mColumns, mRows);
	mNodes = mGraph.GetNodes();
	//Check bound and make sure we are within the map
	//Check if mouse is clicked
	//Index into mTiles and change value
	int column = static_cast<int>(X::GetMouseScreenX() / mTileSize);
	int row = static_cast<int>(X::GetMouseScreenY() / mTileSize);
	int i = GetIndex(column, row);
	if (column < mColumns&&row < mRows)
	{
		if (X::IsMousePressed(X::Mouse::RBUTTON))
		{
			mTiles[i] = 1;
		}
	}
	//test
	mStartPoint = { 2,2 };
	mEndPoint = { 10,15 };
	if (X::IsKeyPressed(X::Keys::SPACE))
	{
		mPath = mBFS.Search(mGraph, mStartPoint, mEndPoint);
		mCloseList = mBFS.GetClosedList();
		mParents = mBFS.GetParents();
	}
}

void TileMap::Render() const
{
	for (int y = 0; y < mRows; y++)
	{
		for (int x = 0; x < mColumns; x++)
		{
			const int index = GetIndex(x, y);
			X::Math::Vector2 pos = GetPosition({ x,y });
			//X::Math::Vector2 pos = { static_cast<float>(x)*mTileSize,static_cast<float>(y)*mTileSize };

			X::DrawSprite(mTextureIds[mTiles[index]], pos - mOffset, X::Pivot::TopLeft);
			X::DrawScreenCircle(pos, 5.0f, X::Colors::LightGray);
			for (int i = 0; i < mNodes[index].neighbors.size(); i++)
			{
				X::DrawScreenLine(pos, GetPosition(mNodes[index].neighbors[i]), X::Colors::SlateGray);
			}
		}
	}
	//Draw Closed List
	for (auto close : mCloseList)
	{
		X::DrawScreenLine(
			GetPosition(close),
			GetPosition(mParents[GetIndex(close.x, close.y)]),
			X::Colors::Black
		);
	}

	//Draw Path
	for (int i = 1; i < mPath.size(); i++)
	{
		X::DrawScreenLine(GetPosition(mParents[GetIndex(mPath[i].x, mPath[i].y)]), GetPosition(mPath[i]), X::Colors::Red);
	}
	X::DrawScreenDiamond(GetPosition(mStartPoint), 10.0f, X::Colors::Blue);
	X::DrawScreenDiamond(static_cast<float>(mEndPoint.x)*mTileSize + mOffset.x, static_cast<float>(mEndPoint.y)*mTileSize + mOffset.x, 10.0f, X::Colors::Red);
}

int TileMap::GetIndex(int x, int y) const
{
	return x + (y*mColumns);
}

X::Math::Vector2 TileMap::GetPosition(AI::Coord coord) const
{
	return
	{
		static_cast<float>(coord.x*mTileSize + mOffset.x),
		static_cast<float>(coord.y*mTileSize + mOffset.y)
	};
}