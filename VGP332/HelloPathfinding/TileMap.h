#pragma once

#include<AI.h>
#include<XEngine.h>

class TileMap
{
public:
	void Load();
	void Unload();

	void Update(float deltaTime);
	void Render() const;
	

private:
	int GetIndex(int x, int y) const;
	std::array<X::TextureId,6> mTextureIds;
	std::vector<int> mTiles;
	int mColumns = 0;
	int mRows = 0;
	int mTileSize = 32;
};