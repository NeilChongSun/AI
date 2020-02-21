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
}

void Cat::Update(float deltaTime)
{
	mStateMachine->Update(deltaTime);
}

void Cat::ChangeState(std::string stateName)
{
	mStateMachine->ChangeState(stateName);
}
