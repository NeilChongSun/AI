#include "Precompiled.h"
#include "SeekBehavior.h"

using namespace AI;

X::Math::Vector2 SeekBehavior::Calculate(Agent & agent)
{
	return ((X::Math::Normalize(agent.destination - agent.position) *agent.maxSpeed) - agent.velocity);
}
