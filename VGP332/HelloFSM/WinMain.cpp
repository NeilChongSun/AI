#include<XEngine.h>
#include"Cat.h"
Cat cat;
void GameInit()
{
	cat.Load();
}

void GameCleanup()
{
}

bool GameLoop(float deltaTime)
{
	cat.Update(deltaTime);
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