#pragma once
#include<XEngine.h>
#include<AI.h>
class Pickups : public AI::Agent
{
public:
	Pickups(AI::AIWorld& world):
		Agent(world,world.GetNextId()){}
	void Load();
	void Update(float deltaTime);
	void Render();

	const X::Math::Vector2 GetPosition()const { return position; }
	bool Destroy();
private:
	std::unique_ptr<AI::SteeringModule> mSteering;
	X::Math::Vector2 mAcceleration;
	X::TextureId mTextureId;
	X::Math::Circle mCircle;
	bool mDrawDebugLine = false;
	AI::WanderBehavior* mWanderBehavior;
};