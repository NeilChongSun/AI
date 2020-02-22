#pragma once
#include<XEngine.h>
#include<AI.h>
class Cat
{
public:
	void Load();
	void Update(float deltaTime);
	void ChangeState(std::string stateName);
	void Render();
	const X::Math::Vector2 GetPosition() const { return mPosition; }
	void SetPosition(X::Math::Vector2 pos);
	const X::Math::Vector2 GetTarget() const { return mTarget; }
	void SetTarget(X::Math::Vector2 target);
private:
	std::unique_ptr<AI::StateMachine<Cat>> mStateMachine;


	X::TextureId mCatTexture = 0;
	X::Math::Vector2 mPosition;
	X::Math::Vector2 mTarget;
};