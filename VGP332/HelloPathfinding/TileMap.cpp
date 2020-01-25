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
			X::DrawSprite(mTextureIds[mTiles[index]], pos, X::Pivot::TopLeft);
		}
	}
}

int TileMap::GetIndex(int x, int y) const
{
	return x + (y*mColumns);
}
