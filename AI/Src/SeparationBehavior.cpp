#include "Precompiled.h"
#include "SeparationBehavior.h"

using namespace AI;

X::Math::Vector2 AI::SeparationBehavior::Calculate(Agent & agent)
{
	X::Math::Vector2 totalForce;
	for (auto& neighbor : agent.neighbors)
	{
		auto neighborToAgent = agent.position - neighbor->position;
		auto distanceToAgent = X::Math::Magnitude(neighborToAgent);
		if (distanceToAgent <= 0.0f)
		{
			totalForce += agent.heading * agent.maxSpeed;
		}
		else
		{
			auto seperationDirection = neighborToAgent / distanceToAgent;
			auto sepaerationForce = agent.maxSpeed * (1.0f - X::Math::Min(distanceToAgent, 100.0f) / 100.0f);
			totalForce += seperationDirection * sepaerationForce;
		}

	}
	return totalForce;
}
