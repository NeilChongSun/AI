#include "Precompiled.h"
#include "AvoidObsBehavior.h"

using namespace AI;

X::Math::Vector2 AviodObsBehavior::Calculate(Agent & agent)
{
	auto aheadVector = agent.position + X::Math::Normalize(agent.velocity) * 50.0f;
	auto aheadVector2 = agent.position + X::Math::Normalize(agent.velocity) + 50.0f * 0.5f;
	float length = X::Math::Magnitude(agent.position - aheadVector);

	X::Math::Matrix3 worldToLocal = X::Math::Inverse(agent.LocalToWorld());
	
	X::Math::Circle* nearest = nullptr;
	float minDistance = std::numeric_limits<float>::infinity();
	X::Math::Vector2 force;
	X::Math::Vector2 localObsPos = X::Math::Vector2();
	float obsExpandRadius = 0.0f;
	for (auto& obs : agent.world.GetObstacles())
	{
		// Find the nearest obstacle
		float distance = X::Math::Distance(obs.center, agent.position);
		if (distance < minDistance)
		{
			minDistance = distance;
			auto obstacle = obs;
			bool collision = lineIntersectsCircle(obstacle, aheadVector, aheadVector2);

			// Calculate the nearest obstacle's position in local space
			if (collision && (nearest == nullptr || X::Math::Distance(agent.position, obstacle.center) < X::Math::Distance(agent.position, nearest->center)))
			{
				nearest = &obstacle;
				localObsPos = X::Math::TransformCoord(nearest->center, worldToLocal);
				obsExpandRadius = nearest->radius + X::Math::Magnitude(aheadVector); // Expand remaining obstacles by width of bounding box
				if (localObsPos.x > 0.0f) // except for behind
				{
					if (fabs(localObsPos.y) < obsExpandRadius) // Eliminate obstacles whose abs(local y) < expanded radius
					{
						X::Math::Vector2 steeringForce;
						steeringForce.y = (nearest->radius - localObsPos.y) * (1.0f + (length - localObsPos.x) / length);
						steeringForce.x = (nearest->radius - localObsPos.x) * 0.2f;
						// Transform normal with x axis and localToWorld, then added agent's speed

						force += X::Math::Normalize((X::Math::TransformNormal({ steeringForce }, agent.LocalToWorld()))) * agent.maxSpeed * 2.0f;
						return force;
					}
				}
				X::DrawScreenCircle(nearest->center.x, nearest->center.y, nearest->radius + 5.0f, X::Colors::Magenta);
			}
		}
	}
	X::DrawScreenLine(agent.position, aheadVector, X::Colors::Red);
	return X::Math::Vector2();
}
// Physics Engine
// 1) World representation - proxy shapes(AABB, OBB, Sphere, Capsule, etc) - Particles(i.e. point mess) - Can be hierarchical - Can have constraints (e.g. joints)
// 2) Simulation - For object motion - Applies physics formulas(e.g. Kinematics) - Preserves rules of physics(e.g. Newton's Laws, Energy/Momentum conservation)
// 3) Collision Detection - Math/Geometry - Can be hierarchical(e.g. spatial partitioning, compound shapes)
// 4) Collision Resolution - Physics formulas - Preserves rules of physics(e.g. Newton's Laws, Energy/Momentum conservation)