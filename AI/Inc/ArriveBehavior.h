#pragma once

#include "SteeringBehavior.h"
#include "Agent.h"


namespace AI
{

	class ArriveBehavior : public AI::SteeringBehavior
	{
	public:
		X::Math::Vector2 Calculate(Agent& agent) override;
	};
}