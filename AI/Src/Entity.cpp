#include "Precompiled.h"
#include "Entity.h"

#include "AIWorld.h"

using namespace AI;

Entity::Entity(AIWorld & world, uint16_t typeId)
	: world(world),
	mUniqueId((static_cast<uint64_t>(typeId) << 32) | world.GetNextId())
{
	world.RegisterEnetity(this);
}

Entity::~Entity()
{
	world.UnregisterEnetity(this);
}

X::Math::Matrix3 AI::Entity::LocalToWorld() const
{
	auto f = X::Math::Normalize(heading);
	auto s = X::Math::PerpendicularRH(f);
	auto p = position;
	return
	{
		s.x,s.y,0.0f,
		f.x,f.y,0.0f,
		p.x,p.y,1.0f
	};
}
