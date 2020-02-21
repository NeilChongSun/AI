#pragma once
#include"CatState.h"

class Run :public CatState
{
public:
	~Run() = default;
	void Load() override;
	void Unload() override;
	void Update(float deltaTime) override;
	void Render() override;
};