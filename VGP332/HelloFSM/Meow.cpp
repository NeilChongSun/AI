#include "Meow.h"

void Meow::Load()
{
	mMeowId = X::LoadSound("Meow.wmn");
}

void Meow::Unload()
{
}

void Meow::Update(float deltaTime)
{
	X::PlaySoundOneShot(mMeowId);
	mCat.ChangeState("Idle");
}

void Meow::Render()
{
	X::DrawSprite(mCatTexture, mPosition);
}
