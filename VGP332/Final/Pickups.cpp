#include "Pickups.h"
#include"Ship.h"
void Pickups::Load()
{
	const auto width = static_cast<float>(X::GetScreenWidth());
	const auto height = static_cast<float>(X::GetScreenHeight());
	maxSpeed = 50.0f;
	position = { X::RandomFloat(0.0f,width),X::RandomFloat(0.0f,height)};
	mSteering = std::make_unique<AI::SteeringModule>(*this);
	mWanderBehavior = mSteering->AddBehavior<AI::WanderBehavior>("wander");
	mWanderBehavior->SetActive(true);
	mTextureId = X::LoadTexture("bullet2.png");
}


void Pickups::Update(float deltaTime)
{
	mAcceleration = mSteering->Calculate();
	velocity += mAcceleration * deltaTime;
	position += velocity * deltaTime;
	heading = X::Math::Normalize(velocity);
	radius=10.0f;

	mCircle = X::Math::Circle{ position,radius };
	//World wrapping
	const auto width = static_cast<float>(X::GetScreenWidth());
	const auto height = static_cast<float>(X::GetScreenHeight());
	if (position.x < 0.0f)
		position.x += width;
	if (position.x >= width)
		position.x -= width;
	if (position.y < 0.0f)
		position.y += height;
	if (position.y >= height)
		position.y -= height;
	if (X::IsMousePressed(X::Mouse::LBUTTON))
	{
		mDrawDebugLine = !mDrawDebugLine;		
		mWanderBehavior->drawDebugLine = !mWanderBehavior->drawDebugLine;
	}
}

void Pickups::Render()
{
	X::DrawSprite(mTextureId, position);
	if (mDrawDebugLine)
		X::DrawScreenCircle(position, radius,X::Colors::Green);
}

bool Pickups::Destroy()
{
	const X::Math::Circle& shipCircle = Ship::Get().GetCircle();
	if (X::Math::Intersect(mCircle,shipCircle))
	{
		return true;
	}
	return false;
}
