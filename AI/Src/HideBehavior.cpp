#include "Precompiled.h"
#include "HideBehavior.h"

using namespace AI;

X::Math::Vector2 HideBehavior::Calculate(Agent & agent)
{
	if (agent.world.GetObstacles().size() == 0)
	{
		return X::Math::Vector2::Zero();
	}

	float minDistance = std::numeric_limits<float>::infinity();
	X::Math::Circle circle;

	for (const auto& obstacle : agent.world.GetObstacles())
	{
		float distance = X::Math::Distance(obstacle.center, agent.position);
		if (distance < minDistance)
		{
			circle = obstacle;
			minDistance = distance;
		}
	}
	float distAway = circle.radius + 30.0f;
	X::Math::Vector2 toSafeArea = circle.center - agent.threat->position;
	X::Math::Vector2 toSafeAreaDirection = X::Math::Normalize(toSafeArea);

	X::Math::Vector2 desireDestination = agent.position + (toSafeAreaDirection * distAway * 10.0f);
	agent.destination = desireDestination;

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
}
