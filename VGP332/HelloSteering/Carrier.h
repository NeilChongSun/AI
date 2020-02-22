#pragma once

#include<AI.h>
#include<XEngine.h>

class Carrier : public AI::Agent
{
public:
	Carrier(AI::AIWorld& aiWorld);

	void Load();
	void Unload();
	void Update(float dletaTime);
	void Render();

private:
	std::unique_ptr<AI::SteeringModule> mSteering;
	std::array<X::TextureId, 32> mTextureIds;
};