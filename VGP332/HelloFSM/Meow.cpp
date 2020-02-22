#include "Meow.h"

void Meow::Enter(Cat& anget)
{
	mMeowId = X::LoadSound("photongun1.wav");
}

void Meow::Update(Cat& agent, float deltaTime)
{
	X::PlaySoundOneShot(mMeowId);
	agent.ChangeState("Idle");
}

void Meow::Exit(Cat & agent)
{
}
