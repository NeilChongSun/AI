#pragma once
#include <XEngine.h>
#include"Cat.h"
class CatState
{
public:
	virtual ~CatState() = default;

	virtual void Load() = 0;

	virtual void Unload() = 0;

	virtual void Update(float deltaTime) = 0;

	virtual void Render() = 0;
protected:

	X::TextureId mCatTexture = 0;
	X::Math::Vector2 mPosition;
	X::SoundId mMeowId;
	float mSpeed;
	Cat mCat;

};