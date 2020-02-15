#pragma once
#include"CatState.h"

class Idle :public CatState
{
public:
	~Idle() = default;
	void Load() override;
	void Unload() override;
	void Update(float deltaTime) override;
	void Render() override;
};