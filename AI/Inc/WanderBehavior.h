#pragma once
#include "SteeringBehavior.h"
#include "Agent.h"

namespace AI
{
	class WanderBehavior : public AI::SteeringBehavior
	{
	public:
		X::Math::Vector2 Calculate(Agent& agent) override;
		float wanderDistance = 30.0f;
		float wanderJitter = 10.0f;
		float wanderRadius = 20.0f;

	private:
		X::Math::Vector2 targetPos = X::Math::Vector2::Zero();
	};
}