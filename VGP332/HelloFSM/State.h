#pragma once
#include<AI.h>
#include"CatState.h"
class State : public AI::State<CatState>
{
public: 
	void Enter(CatState& cat) override;
	void Update(CatState& cat,float deltaTime)override;
	void Exit(CatState& cat)override;
private:

};