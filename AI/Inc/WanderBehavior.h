#pragma once
#include "SteeringBehavior.h"
#include "Agent.h"

namespace AI
{
	class WanderBehavior : public AI::SteeringBehavior
	{
	public:
		X::Math::Vector2 Calculate(Agent& agent) override;

	private:
		X::Math::Vector2 targetPos = X::Math::Vector2::Zero();
	};
}