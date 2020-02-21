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
	if (X::IsMousePressed(X::Mouse::LBUTTON))
	{
		int mouseX = X::GetMouseScreenX();
		int mouseY = X::GetMouseScreenY();
		mTarget = X::Math::Vector2(static_cast<float>(mouseX), static_cast<float>(mouseY));
		mCat.ChangeState("Run");
	}
}

void Idle::Render()
{
	X::DrawSprite(mCatTexture, mPosition);
}
