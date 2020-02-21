#pragma once
#include"CatState.h"

class Meow :public CatState
{
public:
	~Meow() = default;
	void Load() override;
	void Unload() override;
	void Update(float deltaTime) override;
	void Render() override;
};