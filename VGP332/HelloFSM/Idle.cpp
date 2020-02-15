#include "Idle.h"

void Idle::Load()
{
	mCatTexture = X::LoadTexture("cat.png");
	mPosition = (30.0f, 20.0f);
}

void Idle::Unload()
{
}

void Idle::Update(float deltaTime)
{
}

void Idle::Render()
{
	X::DrawSprite(mCatTexture, mPosition);
}
