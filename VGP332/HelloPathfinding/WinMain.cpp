#include<XEngine.h>
#include"TileMap.h"

TileMap tileMap;

void GameInit()
{
	tileMap.Load();
}

void GameCleanup()
{
	tileMap.Unload();
}

bool GameLoop(float deltaTime)
{
	tileMap.Update(deltaTime);
	tileMap.Render();
	return X::IsKeyPressed(X::Keys::ESCAPE);
}

int WinMain(HINSTANCE,HINSTANCE,LPSTR,int)
{
	X::Start();
	GameInit();
	X::Run(GameLoop);
	GameCleanup();
	X::Stop();
	return 0;
}