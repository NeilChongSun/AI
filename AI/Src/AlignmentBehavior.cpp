#include "Precompiled.h"
#include "AlignmentBehavior.h"

using namespace AI;

X::Math::Vector2 AI::AlignmentBehavior::Calculate(Agent & agent)
{
	X::Math::Vector2 averageHeading = agent.heading;

	for (auto& neighbor : agent.neighbors)
	{
		averageHeading += neighbor->heading;
	}
	averageHeading /= (agent.neighbors.size() + 1.0f);

	return averageHeading - agent.heading;
}
