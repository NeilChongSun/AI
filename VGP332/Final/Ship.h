#pragma once
#include<AI.h>
#include<XEngine.h>
#include"Pickups.h"

class Ship : public AI::Agent
{
public:
	static void StaticInitialize();
	static void StaticTerminate();
	static Ship& Get();
public:
	Ship(AI::AIWorld& world) :
		Agent(world,world.GetNextId()){}
	void Load();
	void Update(float deltaTime);
	void Render();

	const X::Math::Circle GetCircle() const { return mCircle; }
	const X::Math::Vector2 GetPosition()const { return position; }
	void Resize(int size);
private:
	std::unique_ptr<AI::SteeringModule> mSteering;
	std::array<X::TextureId, 32> mTextureIds;
	X::Math::Vector2 mAcceleration;
	std::vector<X::Math::Vector2> mPickupsPositions;
	std::vector<X::Math::Vector2> mEnemiesPositions;
	std::vector<float> mDistanceToPickups;
	std::vector<float> mDistanceToEnemies;
	X::Math::Circle mCircle;
	AI::SeekBehavior* mSeekBehavior;
	AI::FleeBehavior* mFleeBehavior;
	float mRange=200.0f;
	int mEnemyMinIndex;
	int mPickupMinIndex;
	bool mIsSeek = true;
};