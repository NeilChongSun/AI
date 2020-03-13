#include "Precompiled.h"
#include "FleeBehavior.h"

using namespace AI;

X::Math::Vector2 FleeBehavior::Calculate(Agent & agent)
{
	const double PanicDistanceSq = 500.0f * 500.0f;
	if (X::Math::DistanceSqr(agent.position, agent.destination) > PanicDistanceSq)
		return X::Math::Vector2{ 0,0 };

	return ((X::Math::Normalize(agent.position - agent.destination) *agent.maxSpeed) - agent.velocity) / agent.mass;
}
