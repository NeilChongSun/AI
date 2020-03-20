#pragma once
#include<XEngine.h>
#include"Enemy.h"

class EnemyManager
{
public:
	static void StaticInitialize();
	static void StaticTerminate();
	static EnemyManager& Get();
public:
	void Load();
	void Unload();
	void Update(float deltaTime);
	void Render();

	const std::vector<X::Math::Vector2> GetPosition()const { return mPositions; }
	const int GetEnemiesCount() const { return mEnemiesCount; }
	void SetEnemyiesCount(int count) { mEnemiesCount = count; }
private:
	std::vector<Enemy*> mEnemies;
	std::vector<X::Math::Vector2> mPositions;
	int mEnemiesCount = 5;
};