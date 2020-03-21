#include "Enemy.h"
#include"Ship.h"
namespace
{
	Enemy* sInstance = nullptr;
	AI::AIWorld aiWorld;
}

void Enemy::StaticInitialize()
{
	XASSERT(sInstance == nullptr, "Already initialized!");
	sInstance = new Enemy(aiWorld);
}

void Enemy::StaticTerminate()
{
	delete sInstance;
	sInstance = nullptr;
}

Enemy & Enemy::Get()
{
	XASSERT(sInstance != nullptr, "No created!");
	return *sInstance;
}

void Enemy::Load()
{
	const auto width = static_cast<float>(X::GetScreenWidth());
	const auto height = static_cast<float>(X::GetScreenHeight());
	maxSpeed = 100.0f;
	position = { X::RandomFloat(0.0f,width),X::RandomFloat(0.0f,height) };
	mSteering = std::make_unique<AI::SteeringModule>(*this);

	mWanderBehavior = mSteering->AddBehavior<AI::WanderBehavior>("wander");
	mWanderBehavior->wanderDistance = 50.0f;
	mWanderBehavior->wanderJitter = 5.0f;
	mWanderBehavior->wanderRadius = 25.0f;
	mWanderBehavior->SetActive(true);

	mSeekBehavior = mSteering->AddBehavior<AI::SeekBehavior>("Seek");
	for (int i = 0; i < std::size(mTextureIds); i++)
	{
		char name[256];
		sprintf_s(name, "scv_%02zu.png", i + 1);
		mTextureIds[i] = X::LoadTexture(name);
	}
}

void Enemy::Update(float deltaTime)
{
	mAcceleration = mSteering->Calculate();
	velocity += mAcceleration * deltaTime;
	position += velocity * deltaTime;
	heading = X::Math::Normalize(velocity);
	radius = 20.0f;
	mCircle = X::Math::Circle{ position,radius };
	mShipPosition = Ship::Get().GetPosition();
	float distance = X::Math::Distance(position, mShipPosition);
	if (distance <= mRange)
	{
		mWanderBehavior->SetActive(false);
		mSeekBehavior->SetActive(true);
		destination = mShipPosition;
	}
	else
	{
		mWanderBehavior->SetActive(true);
		mSeekBehavior->SetActive(false);
	}
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
	const X::Math::Circle& shipCircle = Ship::Get().GetCircle();
	if (X::Math::Intersect(mCircle, shipCircle) || X::IsMouseDown(X::Mouse::RBUTTON))
		mIsGameOver = true;
	if (mIsGameOver)
		X::DrawScreenText("Enemy Win", width / 2, height / 2, 55, X::Colors::Red);

}

void Enemy::Render()
{
	const float angle = atan2(-heading.x, heading.y) + X::Math::kPi;
	int frame = (int)(angle / X::Math::kTwoPi * std::size(mTextureIds)) % std::size(mTextureIds);
	X::DrawSprite(mTextureIds[frame], position);
	if (mDrawDebugLine)
	{
		X::DrawScreenCircle(position, radius, X::Colors::Yellow);
		X::DrawScreenCircle(position, mRange, X::Colors::White);
	}
}
