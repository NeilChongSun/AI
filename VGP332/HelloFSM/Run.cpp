#include "Run.h"

void Run::Enter(Cat & agent)
{
	mPosition = agent.GetPosition();
	mTarget = agent.GetTarget();
	mSpeed = 300.0f;
}

void Run::Update(Cat & agent, float deltaTime)
{
	mHeading = X::Math::Normalize(mTarget - mPosition);
	mPosition += mHeading * mSpeed*deltaTime;
	agent.SetPosition(mPosition);
	if (X::Math::Distance(mPosition,mTarget)<=1.0f)
	{
		mSpeed = 0.0f;
		agent.ChangeState("Meow");
	}
}

void Run::Exit(Cat & agent)
{
	
}
