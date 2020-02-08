#include"TileMap.h"
#include"ImGui/Inc/imgui.h"
void TileMap::Load()
{
	mTextureIds[0] = X::LoadTexture("grass.png");
	mTextureIds[1] = X::LoadTexture("flower.png");
	mTextureIds[2] = X::LoadTexture("grass_2.png");
	mTextureIds[3] = X::LoadTexture("flower_2.png");
	mTextureIds[4] = X::LoadTexture("tree0.png");
	mTextureIds[5] = X::LoadTexture("tree1.png");
	mTextureIds[6] = X::LoadTexture("stone.png");
	mTextureIds[7] = X::LoadTexture("tree2.png");
	mTextureIds[8] = X::LoadTexture("tree3.png");

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
	mClickPos = GetClickPosition();
	mClickIndex = GetIndex(mClickPos.x, mClickPos.y);
	//Set Obstacle or start\end point when mouse is click
	switch (mMouseClick)
	{
	case eSetStart:
		mCurrentClickText = "Start Point";
		if (CheckClick())
			mStartPoint = mClickPos;
		break;
	case eSetEnd:
		mCurrentClickText = "End Point";
		if (CheckClick())
			mEndPoint = mClickPos;
		break;
	case eSetTile:
		mCurrentClickText = "";
		if (CheckClick())
			mTiles[mClickIndex] = mCurrentTile;
		break;
	default:
		break;
	}
	//Draw Path
	auto isBlockedFunc = [this](AI::Coord coord)
	{
		return mTiles[GetIndex(coord.x, coord.y)] >= 4;
	};
	auto getCostFunc = [this](AI::Coord current, AI::Coord neighbor)
	{
		bool diagonal = current.x != neighbor.x && current.y != neighbor.y;
		return (mTiles[GetIndex(neighbor.x, neighbor.y)] + 1) * (diagonal ? 1.414f : 1.0f);
	};
	auto getHeuristic = [this](AI::Coord start, AI::Coord end)
	{
		return abs(start.x-end.x)+abs(start.y-end.y);
	};
	switch (mSearchMode)
	{
	case eBFS:
		mSearchModeText = "BFS";
		if (mDraw)
		{
			mPath = mBFS.Search(mGraph, mStartPoint, mEndPoint, isBlockedFunc);
			mCloseList = mBFS.GetClosedList();
			mParents = mBFS.GetParents();
		}
		break;
	case eDFS:
		mSearchModeText = "DFS";
		if (mDraw)
		{
			mPath = mDFS.Search(mGraph, mStartPoint, mEndPoint, isBlockedFunc);
			mCloseList = mDFS.GetClosedList();
			mParents = mDFS.GetParents();
		}
		break;
	case eDijkstars:
		mSearchModeText = "Dijkstars";
		if (mDraw)
		{
			mPath = mDijkstras.Search(mGraph, mStartPoint, mEndPoint, isBlockedFunc, getCostFunc);
			mCloseList = mDijkstras.GetClosedList();
			mParents = mDijkstras.GetParents();
		}
		break;
	case eAStar:
		mSearchModeText = "AStar";
		if (mDraw)
		{
			mPath = mAStar.Search(mGraph, mStartPoint, mEndPoint, isBlockedFunc, getCostFunc,getHeuristic);
			mCloseList = mAStar.GetClosedList();
			mParents = mAStar.GetParents();
		}
		break;
	default:
		break;
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
			for (int i = 0; i < mNodes[index].neighbors.size(); i++)
			{
				X::DrawScreenCircle(pos, 5.0f, X::Colors::LightGray);
				X::DrawScreenLine(pos, GetPosition(mNodes[index].neighbors[i]), X::Colors::SlateGray);
			}
		}
	}
	//Draw Closed List
	for (auto it = mCloseList.begin(); it != mCloseList.end(); ++it)
	{
		if (it != mCloseList.begin())
		{
			auto close = *it;
			X::DrawScreenLine(GetPosition(close), GetPosition(mParents[GetIndex(close.x, close.y)]), X::Colors::Black);
		}
	}

	//Draw Path
	for (int i = 1; i < mPath.size(); i++)
	{
		X::DrawScreenLine(GetPosition(mParents[GetIndex(mPath[i].x, mPath[i].y)]), GetPosition(mPath[i]), X::Colors::Red);
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
	return AI::Coord{ column,row };
}

bool TileMap::CheckClick() const
{
	if (X::IsMousePressed(X::Mouse::LBUTTON))
		return mClickPos.x < mColumns&&mClickPos.y < mRows;
	else
		return false;
}

void TileMap::ShowDebugUI()
{
	//Start ImGui
	ImGui::SetNextWindowPos({ X::GetScreenWidth() - 300.0f,0.0f });
	ImGui::SetNextWindowSize({ 300.0f, 400.0f });
	ImGui::Begin("Pathfinding", nullptr, ImGuiWindowFlags_NoResize);
	//Show current search mode
	ImGui::Text("Current Search Mode: %s", mSearchModeText);
	//Buttons
		//Choose BFS or DFS
	if (ImGui::Button("BFS", { 60,30 }))
		mSearchMode = eBFS;
	ImGui::SameLine();
	if (ImGui::Button("DFS", { 60,30 }))
		mSearchMode = eDFS;
	ImGui::SameLine();
	if (ImGui::Button("Dijkstars", { 60,30 }))
		mSearchMode = eDijkstars;
	ImGui::SameLine();
	if (ImGui::Button("AStar", { 60,30 }))
		mSearchMode = eAStar;
	//Set start point and end point
	ImGui::Separator();
	ImGui::Text("Start Point: %d,%d", mStartPoint.x + 1, mStartPoint.y + 1);
	ImGui::Text("End Point: %d,%d", mEndPoint.x + 1, mEndPoint.y + 1);
	if (ImGui::Button("Set Start Point", { 120,30 }))
	{
		mMouseClick = eSetStart;
	}
	ImGui::SameLine();
	if (ImGui::Button("Set End Point", { 120,30 }))
	{
		mMouseClick = eSetEnd;
	}

	//Draw Path
	ImGui::Separator();
	if (ImGui::Button("Draw", { 60,30 }))
		mDraw = true;
	ImGui::SameLine();
	//Clear Path
	if (ImGui::Button("Clear", { 60,30 }))
	{
		mDraw = false;
		mPath.clear();
		mCloseList.clear();
		mParents.clear();
		mTiles.clear();
		mTiles.resize(mColumns*mRows, 0);
	}

	//Show the image that I choose currently
	ImGui::Separator();
	ImGui::Text("Current: %s", mCurrentClickText);
	ImGui::SameLine();
	if (mMouseClick == eSetTile)
	{
		ImGui::Image(X::GetSprite(mTextureIds[mCurrentTile]), { 32.0,32.0 });
		ImGui::SameLine();
		if (mCurrentTile<=3)
			ImGui::Text("Cost: %d", mCurrentTile+1);
	}
		
	ImGui::Separator();

	//Show tiles can be choose
	for (int i = 0; i < (int)mTextureIds.size(); i++)
	{
		if (ImGui::ImageButton(X::GetSprite(mTextureIds[i]), { 32.0f,32.0f }))
		{
			mCurrentTile = i;
			mMouseClick = eSetTile;
		}
		if (i % 3 != 2)
			ImGui::SameLine();
	}
	ImGui::End();
}
