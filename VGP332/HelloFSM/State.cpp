#include "State.h"
void State::Enter(CatState & catState)
{
	catState.Load();
}

void State::Update(CatState & catState, float deltaTime)
{
	catState.Update(deltaTime);
	catState.Render();
}

void State::Exit(CatState & catState)
{
	catState.Unload();
}
