#include "Precompiled.h"
#include "WanderBehavior.h"

using namespace AI;

X::Math::Vector2 WanderBehavior::Calculate(Agent & agent)
{
	float wanderDistance = 100.0f;
	const float wanderJitter = 5.0f;
	X::Math::Vector2 circle = (agent.position + (agent.heading * wanderDistance));

	X::Math::Vector2 random; // WanderJitter
	random.x = X::RandomFloat(-1.0f, 1.0f) * wanderJitter;
	random.y = X::RandomFloat(-1.0f, 1.0f) * wanderJitter;

	targetPos += random;
	targetPos = X::Math::Normalize(targetPos);
	targetPos *= agent.radius;

	agent.destination = targetPos + circle;

	X::Math::Vector2 desiredVel = X::Math::Normalize(agent.destination - agent.position) * agent.maxSpeed;
	desiredVel -= agent.velocity;

	X::DrawScreenCircle(circle.x,circle.y, agent.radius, X::Colors::Green);
	X::DrawScreenCircle(agent.destination, agent.radius* 0.25f, X::Colors::Gold);

	return desiredVel;
}
