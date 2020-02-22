#pragma once
#include"Cat.h"
#include <AI.h>

class Meow :public AI::State<Cat>
{
public:
	~Meow() = default;
	void Enter(Cat& agent) override;
	void Update(Cat& agent, float deltaTime) override;
	void Exit(Cat& agent)override;
private:
	X::SoundId mMeowId;
};