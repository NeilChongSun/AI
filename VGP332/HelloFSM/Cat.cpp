#include "Cat.h"
#include"Idle.h"
#include"Run.h"
#include"Meow.h"
void Cat::Load()
{
	mStateMachine = std::make_unique<AI::StateMachine<Cat>>(*this);
	mStateMachine->AddState<Idle>("Idle");
	mStateMachine->AddState<Run>("Run");
	mStateMachine->AddState<Meow>("Meow");
	mPosition = X::Math::Vector2(100.0f, 100.0f);
	mCatTexture = X::LoadTexture("Cat.png");
	mStateMachine->ChangeState("Idle");
}

void Cat::Update(float deltaTime)
{
	mStateMachine->Update(deltaTime);
}

void Cat::Render()
{
	X::DrawSprite(mCatTexture, mPosition);
}

void Cat::ChangeState(std::string stateName)
{
	mStateMachine->ChangeState(stateName);
}

void Cat::SetPosition(X::Math::Vector2 pos)
{
	mPosition=pos;
}

void Cat::SetTarget(X::Math::Vector2 target)
{
	mTarget = target;
}

