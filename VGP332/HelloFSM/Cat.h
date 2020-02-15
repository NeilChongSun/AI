#pragma once
#include<XEngine.h>
#include<AI.h>
class Cat
{
public:
	void Load();
	void Update(float deltaTime);
	void ChangeState(std::string stateName);
private:
	std::unique_ptr<AI::StateMachine<Cat>> mStateMachine;

};