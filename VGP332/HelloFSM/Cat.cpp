#include "Cat.h"
#include"Idle.h"
void Cat::Load()
{
	mStateMachine = std::make_unique<AI::StateMachine<Cat>>(*this);
	//mStateMachine->AddState<Idle>("Idle");
}

void Cat::Update(float deltaTime)
{
	mStateMachine->Update(deltaTime);
}

void Cat::ChangeState(std::string stateName)
{
	mStateMachine->ChangeState(stateName);
}
