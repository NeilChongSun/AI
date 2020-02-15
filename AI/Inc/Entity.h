#pragma once
namespace AI
{
	class AIWorld;

	class Entity
	{
	public:
		Entity(AIWorld& world, uint32_t typeId);
		virtual ~Entity();

		X::Math::Matrix3 LocalToWorld() const;

		const uint32_t GetTypeId() const { return mUniqueId >> 32; }
		const uint64_t GetUniqueId() const { return mUniqueId; }

		AIWorld& world;
		X::Math::Vector2 position = X::Math::Vector2::Zero();
		X::Math::Vector2 heading = X::Math::Vector2::YAxis();
		const int id = 0;
		float radius = 1.0f;
	private:
		const uint64_t mUniqueId = 0;
	};
	using Entities = std::vector<Entity*>;
}