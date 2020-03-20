#pragma once
#include "Entity.h"

namespace AI
{
	class Agent;
	using AgentList = std::vector<Agent*>;
	class Agent :public Entity
	{
	public: 
		Agent(AIWorld& world, uint32_t typeId);
		~Agent() override = default;

		Agent* threat = nullptr;

		AgentList neighbors;
		X::Math::Vector2 velocity = X::Math::Vector2::Zero();
		X::Math::Vector2 destination = X::Math::Vector2::YAxis();
		float maxSpeed = 1.0f;
		float mass = 1.0f;
	};
}