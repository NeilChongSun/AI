#include "TileMap.h"
void TileMap::Load()
{
	mTextureIds[0] = X::LoadTexture("grass.png");
	mTextureIds[1] = X::LoadTexture("flower.png");
	mTextureIds[2] = X::LoadTexture("tree0.png");
	mTextureIds[3] = X::LoadTexture("tree1.png");
	mTextureIds[4] = X::LoadTexture("tree2.png");
	mTextureIds[5] = X::LoadTexture("tree3.png");
	
	mColumns = 25;
	mRows = 20;
	
	mTiles.resize(mColumns*mRows, 0);
	mGraph.Resize(mColumns, mRows);
	mNodes = mGraph.GetNodes();
}

void TileMap::Unload()
{

}

void TileMap::Update(float deltaTime)
{
	//Check bound and make sure we are within the map
	//Check if mouse is clicked
	//Index into mTiles and change value
	int column = static_cast<int>(X::GetMouseScreenX() / mTileSize);
	int row = static_cast<int>(X::GetMouseScreenY() / mTileSize);
	int i = GetIndex(column, row);
	if (column < mColumns&&row <  mRows)
	{
		if (X::IsMousePressed(X::Mouse::LBUTTON))
		{
			mTiles[i] = 1;
			//mNode = mGraph.GetNode(AI::Coord{ column,row });
		}
	}	
}

void TileMap::Render() const
{
	for (int y = 0; y < mRows; y++)
	{
		for (int x = 0; x < mColumns; x++)
		{
			const int index = GetIndex(x, y);
			X::Math::Vector2 pos{ static_cast<float>(x)*mTileSize,static_cast<float>(y)*mTileSize };
			X::Math::Vector2 offset{ static_cast<float>( X::GetSpriteWidth(mTextureIds[mTiles[index]]) / 2),static_cast<float>(X::GetSpriteHeight(mTextureIds[mTiles[index]]) / 2) };
			X::DrawSprite(mTextureIds[mTiles[index]], pos, X::Pivot::TopLeft);
			X::DrawScreenCircle(pos + X::Math::Vector2{ 16,16 }, 5.0f, X::Colors::Red);
			for (int i = 0; i <mNodes[index].neighbors.size(); i++)
			{
				X::DrawScreenLine(pos + offset, X::Math::Vector2{ static_cast<float>(mNodes[index].neighbors[i].x*mTileSize),static_cast<float>(mNodes[index].neighbors[i].y*mTileSize) }+offset, X::Colors::LightGray);
			}
		}
	}
}

int TileMap::GetIndex(int x, int y) const
{
	return x + (y*mColumns);
}


//mPath = mBFS.Search(mGraph, start, end);

//auto& closedlist=mBFS.Getcloselist
//auto& parent=mBFS.Getcparent
//
//
//X::Math::Vector2 TileMap::GetPostition(AI::Coord coord)
//{
//	return (coord.x+0.5)*mTile.size(), (coord.y + 0.5)*mTile.size()
//}