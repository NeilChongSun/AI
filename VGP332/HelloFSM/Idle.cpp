#include "Idle.h"
void Idle::Enter(Cat& agent)
{
}

void Idle::Exit(Cat& agent)
{
}

void Idle::Update(Cat& agent, float deltaTime)
{
	if (X::IsMousePressed(X::Mouse::LBUTTON))
	{
		int mouseX = X::GetMouseScreenX();
		int mouseY = X::GetMouseScreenY();
		auto target = X::Math::Vector2(static_cast<float>(mouseX), static_cast<float>(mouseY));
		agent.SetTarget(target);
		agent.ChangeState("Run");
	}
}
