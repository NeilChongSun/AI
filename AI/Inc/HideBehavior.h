#pragma once
#include "SteeringBehavior.h"
#include "Agent.h"
#include "AIWorld.h"
#include "ArriveBehavior.h"
namespace AI
{
	class AIWorld;

	class HideBehavior : public AI::SteeringBehavior
	{
	public:
		X::Math::Vector2 Calculate(Agent& agent) override;

		AIWorld* mAIWorld;
		
	};
}