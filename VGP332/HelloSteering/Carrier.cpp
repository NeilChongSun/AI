#include "Carrier.h"

void Carrier::Load()
{
	mTextureIds[0] = X::LoadTexture("carrier_01.png");
}

void Carrier::Unload()
{
}

void Carrier::Update(float dletaTime)
{

	//World wrapping
	const auto width = static_cast<float>(X::GetScreenWidth());
	const auto height = static_cast<float>(X::GetScreenHeight());

	if (position.x<0.0f)
		position.x += width;
	if (position.x >= width)
		position.x -= width;
	if (position.y < 0.0f)
		position.y += height;
	if (position.y >= height)
		position.y -= height;
}

void Carrier::Render()
{
	const float angle = atan2(-heading.x, heading.y) + X::Math::kPi;

}
