#include"Ship.h"
#include"PickupManager.h"
#include"EnemyManager.h"
namespace
{
	Ship* sInstance = nullptr;
	AI::AIWorld aiWorld;
}
void Ship::StaticInitialize()
{
	XASSERT(sInstance == nullptr, "Already initialized!");
	sInstance = new Ship(aiWorld);
}

void Ship::StaticTerminate()
{
	delete sInstance;
	sInstance = nullptr;
}

Ship & Ship::Get()
{
	XASSERT(sInstance != nullptr, "No created!");
	return *sInstance;
}

void Ship::Load()
{
	maxSpeed = 180.0f;
	position = { 100.0f,100.0f };
	destination = { 500.0f,500.0f };
	mSteering = std::make_unique<AI::SteeringModule>(*this);
	mSeekBehavior = mSteering->AddBehavior<AI::SeekBehavior>("Seek");
	mFleeBehavior = mSteering->AddBehavior<AI::FleeBehavior>("Flee");
	mSeekBehavior->SetActive(true);
	for (int i = 0; i < std::size(mTextureIds); i++)
	{
		char name[256];
		sprintf_s(name, "interceptor_%02zu.png", i + 1);
		mTextureIds[i] = X::LoadTexture(name);
	}
	mDistanceToEnemies.resize(2);
}

void Ship::Update(float deltaTime)
{
	mAcceleration = mSteering->Calculate();
	velocity += mAcceleration * deltaTime;
	position += velocity * deltaTime;
	heading = X::Math::Normalize(velocity);
	radius = 12.0f;
	mCircle = X::Math::Circle{ position,radius };
	mPickupsPositions = PickupManager::Get().GetPosition();
	mEnemiesPositions = EnemyManager::Get().GetPosition();

	for (int i = 0; i < mEnemiesPositions.size(); i++)
	{
		mDistanceToEnemies[i] = X::Math::Distance(mEnemiesPositions[i], position);
		mEnemyMinIndex = std::min_element(mDistanceToEnemies.begin(), mDistanceToEnemies.end()) - mDistanceToEnemies.begin();
		if (mRange >= mDistanceToEnemies[mEnemyMinIndex])
			mIsSeek = false;			
		else
			mIsSeek = true;
	}

	if (!mPickupsPositions.empty()&&mIsSeek)
	{
		mSeekBehavior->SetActive(true);
		mFleeBehavior->SetActive(false);
		for (int i = 0; i < mPickupsPositions.size(); i++)
		{
			mDistanceToPickups[i] = X::Math::Distance(mPickupsPositions[i], position);
		}
		mPickupMinIndex = std::min_element(mDistanceToPickups.begin(), mDistanceToPickups.end()) - mDistanceToPickups.begin();
		destination = mPickupsPositions[mPickupMinIndex];
	}
	else
	{
		mSeekBehavior->SetActive(false);
		mFleeBehavior->SetActive(true);
		destination = mEnemiesPositions[mEnemyMinIndex];
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
}

void Ship::Render()
{
	const float angle = atan2(-heading.x, heading.y) + X::Math::kPi;
	int frame = (int)(angle / X::Math::kTwoPi * std::size(mTextureIds)) % std::size(mTextureIds);
	X::DrawSprite(mTextureIds[frame], position);
	X::DrawScreenCircle(position, radius, X::Colors::Blue);
	X::DrawScreenCircle(position, mRange, X::Colors::Purple);
}

void Ship::Resize(int size)
{
	mDistanceToPickups.resize(size);
}
