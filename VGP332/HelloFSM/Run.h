#pragma once
#include"Cat.h"
#include<AI.h>

class Run :public AI::State<Cat>
{
public:
	~Run() = default;
	void Enter(Cat& agent) override;
	void Update(Cat& agent, float deltaTime) override;
	void Exit(Cat& agent)override;
private:
	float mSpeed;
	X::Math::Vector2 mHeading;
	X::Math::Vector2 mPosition;
	X::Math::Vector2 mTarget;
};