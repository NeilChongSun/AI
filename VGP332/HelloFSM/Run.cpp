#include "Run.h"

void Run::Load()
{
}

void Run::Unload()
{
}

void Run::Update(float deltaTime)
{
	mPosition += mHeading * mSpeed*deltaTime;
	if (mPosition.x == mTarget.x&&mPosition.y == mTarget.y)
	{
		mSpeed = 0.0f;
		mCat.ChangeState("Meow.wav");
	}
}

void Run::Render()
{
	X::DrawSprite(mCatTexture, mPosition);
}
