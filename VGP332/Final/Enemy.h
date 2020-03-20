#pragma once
#include<XEngine.h>
#include<AI.h>

class Enemy :public AI::Agent
{
public:
	static void StaticInitialize();
	static void StaticTerminate();
	static Enemy& Get();

public:
	Enemy(AI::AIWorld& world):
		Agent(world,world.GetNextId()){}

	void Load();
	void Update(float deltaTime);
	void Render();

	const X::Math::Vector2 GetPosition() const { return position; }

private:
	std::unique_ptr<AI::SteeringModule> mSteering;
	X::Math::Vector2 mAcceleration;
	std::array<X::TextureId, 16> mTextureIds;
	X::Math::Circle mCircle;
	float mRange = 200.0f;
	X::Math::Vector2 mShipPosition;
	AI::WanderBehavior* mWanderBehavior;
	AI::SeekBehavior* mSeekBehavior;
};