#include "Precompiled.h"
#include "PursuitBehavior.h"

using namespace AI;

X::Math::Vector2 PursuitBehavior::Calculate(Agent& agent)
{

	X::Math::Vector2 distance = agent.threat->position + agent.threat->velocity - agent.position;
	X::Math::Vector2 futurePosition = X::Math::Normalize(distance) * agent.maxSpeed;
	return futurePosition - agent.velocity;
}
