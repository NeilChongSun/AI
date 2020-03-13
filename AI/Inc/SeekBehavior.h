#pragma once

#include "SteeringBehavior.h"
#include "Agent.h"


namespace AI
{
	class SeekBehavior : public AI::SteeringBehavior
	{
	public:
		X::Math::Vector2 Calculate(Agent& agent) override;

	};
}