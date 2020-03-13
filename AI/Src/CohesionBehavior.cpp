#include "Precompiled.h"
#include "CohesionBehavior.h"

using namespace AI;

X::Math::Vector2 AI::CohesionBehavior::Calculate(Agent & agent)
{

	X::Math::Vector2 averagePosition = agent.position;
	for (auto& neighbor : agent.neighbors)
	{
		averagePosition += neighbor->position;
	}

	averagePosition /= (agent.neighbors.size() + 1.0f);

	return averagePosition;
}
