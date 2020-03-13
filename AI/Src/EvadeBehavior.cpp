#include "Precompiled.h"
#include "EvadeBehavior.h"

using namespace AI;

X::Math::Vector2 EvadeBehavior::Calculate(Agent & agent)
{
	X::Math::Vector2 distance = agent.threat->destination - agent.position;
	float ahead = X::Math::Magnitude(distance) / agent.maxSpeed;
	X::Math::Vector2 futurePosition = agent.threat->destination + agent.threat->velocity* ahead;

	X::Math::Vector2 desiredVel = X::Math::Normalize(agent.position - futurePosition) * agent.maxSpeed;
	return desiredVel - agent.velocity;
}
