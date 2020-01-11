#include<XEngine.h>

void GameInit()
{

}

void GameCleanup()
{

}

bool GameLoop(float deltaTime)
{
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