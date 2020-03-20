#include "Precompiled.h"
#include "WanderBehavior.h"

using namespace AI;

X::Math::Vector2 WanderBehavior::Calculate(Agent & agent)
{
	
	X::Math::Vector2 circle = (agent.position + (agent.heading * wanderDistance));

	X::Math::Vector2 random; // WanderJitter
	random.x = X::RandomFloat(-1.0f, 1.0f) * wanderJitter;
	random.y = X::RandomFloat(-1.0f, 1.0f) * wanderJitter;

	targetPos += random;
	targetPos = X::Math::Normalize(targetPos);
	targetPos *= wanderRadius;

	agent.destination = targetPos + circle;

	X::Math::Vector2 desiredVel = X::Math::Normalize(agent.destination - agent.position) * agent.maxSpeed;
	desiredVel -= agent.velocity;

	X::DrawScreenCircle(circle.x,circle.y, wanderRadius, X::Colors::Green);
	X::DrawScreenCircle(agent.destination, 2.0f, X::Colors::Gold);

	return desiredVel;
}
