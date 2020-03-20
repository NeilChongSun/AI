#pragma once
#include<XEngine.h>
#include"Pickups.h"

class PickupManager
{
public:
	static void StaticInitialize();
	static void StaticTerminate();
	static PickupManager& Get();
public:
	void Load();
	void Unload();
	void Update(float deltaTime);
	void Render();

	const std::vector<X::Math::Vector2> GetPosition()const { return mPositions; }
	const int GetPicksCount() const { return mPickupsCount; }
	void SetPickupsCount(int count) { mPickupsCount = count; }
private:
	std::vector<Pickups*> mPickups;
	std::vector<X::Math::Vector2> mPositions;
	int mPickupsCount = 10;
};