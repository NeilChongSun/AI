#include "TileMap.h"
#include"ImGui/Inc/imgui.h"
void TileMap::Load()
{
	mTextureIds[0] = X::LoadTexture("grass.png");
	mTextureIds[1] = X::LoadTexture("stone.png");
	mTextureIds[2] = X::LoadTexture("tree0.png");
	mTextureIds[3] = X::LoadTexture("tree1.png");
	mTextureIds[4] = X::LoadTexture("tree2.png");
	mTextureIds[5] = X::LoadTexture("tree3.png");
	mTextureIds[6] = X::LoadTexture("flower.png");

	mCurrentTile = 0;

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
	ShowDebugUI();
	//Check bound and make sure we are within the map
	//Check if mouse is clicked
	//Index into mTiles and change value
	AI::Coord clickPos = GetClickPosition();
	int index = GetIndex(clickPos.x, clickPos.y);

	if (X::IsMousePressed(X::Mouse::LBUTTON))
	{
		if (mIsChoosingStartPoint && !mIsChoosingTile)
		{
			mStartPoint = clickPos;
		}
		else if (mIsChoosingEndPoint && !mIsChoosingTile)
		{
			mEndPoint = clickPos;
		}
		else if (mIsChoosingTile)
		{
			mTiles[index] = mCurrentTile;
		}
	}

	if (mIsBFS&&mDraw)
	{
		mPath = mBFS.Search(mGraph, mStartPoint, mEndPoint);
		mCloseList = mBFS.GetClosedList();
		mParents = mBFS.GetParents();
	}
	if (!mIsBFS&&mDraw)
	{
		mPath = mDFS.Search(mGraph, mStartPoint, mEndPoint);
		mCloseList = mDFS.GetClosedList();
		mParents = mDFS.GetParents();
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
		//auto close = *it;
		X::DrawScreenLine(
			GetPosition(close),
			GetPosition(mParents[GetIndex(close.x, close.y)]),
			X::Colors::Black);
		//++it;
	}

	//Draw Path
	for (int i = 1; i < mPath.size(); i++)
	{
		X::DrawScreenLine(
			GetPosition(mParents[GetIndex(mPath[i].x, mPath[i].y)]),
			GetPosition(mPath[i]),
			X::Colors::Red);
	}
	//Draw start point and end point
	X::DrawScreenDiamond(GetPosition(mStartPoint), 10.0f, X::Colors::Blue);
	X::DrawScreenDiamond(GetPosition(mEndPoint), 10.0f, X::Colors::Red);
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

AI::Coord TileMap::GetClickPosition() const
{
	int column = static_cast<int>(X::GetMouseScreenX() / mTileSize);
	int row = static_cast<int>(X::GetMouseScreenY() / mTileSize);
	if (column < mColumns&&row < mRows)
	{
		return AI::Coord{ column,row };
	}
}

void TileMap::ShowDebugUI()
{
	//Start ImGui
	ImGui::SetNextWindowPos({ X::GetScreenWidth() - 300.0f,0.0f });
	ImGui::SetNextWindowSize({ 300.0f, 400.0f });
	ImGui::Begin("Pathfinding", nullptr, ImGuiWindowFlags_NoResize);
	//Show current search mode
	if (mIsBFS)
		ImGui::Text("Current Search Mode: BFS");
	else
		ImGui::Text("Current Search Mode: DFS");
	//Buttons
		//Choose BFS or DFS
	if (ImGui::Button("BFS", { 50,20 }))
		mIsBFS = true;
	ImGui::SameLine();
	ImGui::Spacing();
	ImGui::SameLine();
	if (ImGui::Button("DFS", { 50,20 }))
		mIsBFS = false;
	//Set start point and end point
	ImGui::Separator();
	ImGui::Text("Start Point: %d,%d", mStartPoint.x + 1, mStartPoint.y + 1);
	ImGui::Text("End Point: %d,%d", mEndPoint.x + 1, mEndPoint.y + 1);
	if (ImGui::Button("Set Start Point", { 120,20 }))
	{
		mIsChoosingEndPoint = false;
		mIsChoosingStartPoint = true;
		mIsChoosingTile = false;
	}
	ImGui::SameLine();
	ImGui::Spacing();
	ImGui::SameLine();
	if (ImGui::Button("Set End Point", { 120,20 }))
	{
		mIsChoosingStartPoint = false;
		mIsChoosingEndPoint = true;
		mIsChoosingTile = false;
	}

	//Draw Path
	ImGui::Separator();
	if (ImGui::Button("Draw", { 50,20 }))
		mDraw = true;
	ImGui::SameLine();
	ImGui::Spacing();
	ImGui::SameLine();
	//Clear Path
	if (ImGui::Button("Clear", { 50,20 }))
	{
		mDraw = false;
		mPath.clear();
		mCloseList.clear();
		mParents.clear();
	}

	//Show the image that I choose currently
	ImGui::Separator();
	ImGui::Text("Current: ");
	ImGui::SameLine();
	if (mIsChoosingTile)
		ImGui::Image(X::GetSprite(mTextureIds[mCurrentTile]), { 32.0,32.0 });
	else if (mIsChoosingStartPoint&&!mIsChoosingTile)
		ImGui::Text("Start Point");
	else if (mIsChoosingEndPoint && !mIsChoosingTile)
		ImGui::Text("End Point");

	ImGui::Separator();

	//Show tiles can be choose
	for (int i = 0; i < (int)mTextureIds.size(); i++)
	{
		if (ImGui::ImageButton(X::GetSprite(mTextureIds[i]), { 32.0f,32.0f }))
		{
			mCurrentTile = i;
			mIsChoosingTile = true;
		}
		if (i % 3 != 2)
			ImGui::SameLine();
	}
	ImGui::End();
}


