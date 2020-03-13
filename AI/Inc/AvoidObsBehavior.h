#pragma once
#include "SteeringBehavior.h"
#include "Agent.h"
#include "AIWorld.h"

namespace AI
{
	class AIWorld;

	class AviodObsBehavior : public AI::SteeringBehavior
	{
	public:
		X::Math::Vector2 Calculate(Agent& agent) override;
		AIWorld* mAIWorld;
	private:
		bool lineIntersectsCircle(X::Math::Circle& obs, X::Math::Vector2 ahead, X::Math::Vector2 ahead2)
		{
			return X::Math::Distance(obs.center, ahead) <= obs.radius || X::Math::Distance(obs.center, ahead2) <= obs.radius;
		}

	};
}