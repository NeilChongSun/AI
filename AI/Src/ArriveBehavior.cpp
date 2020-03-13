#include"Precompiled.h"
#include"ArriveBehavior.h"

using namespace AI;

X::Math::Vector2 ArriveBehavior::Calculate(Agent & agent)
{
	X::Math::Vector2 toTarget = agent.destination - agent.position;
	float distance = X::Math::Magnitude(toTarget);
	float decel = 3.0f;
	if (distance > 0.0f)
	{
		float decelTweaker = 0.3f;
		float speed = distance / decel * decelTweaker;
		speed = X::Math::Min(speed, agent.maxSpeed);
		X::Math::Vector2 velocity = toTarget * speed / distance;
		return velocity - agent.velocity;
	}

	return X::Math::Vector2{ 0,0 };
}
