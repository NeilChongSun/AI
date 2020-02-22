#pragma once
#include"Cat.h"
#include"AI.h"
class Idle :public AI::State<Cat>
{
public:
	~Idle() = default;
	void Enter(Cat& agent) override;
	void Update(Cat& agent, float deltaTime) override;
	void Exit(Cat& agent)override;
};