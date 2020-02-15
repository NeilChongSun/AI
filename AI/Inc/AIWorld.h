#pragma once

#include"Entity.h"

namespace AI
{
	class AIWorld
	{
	public:
		void RegisterEnetity(Entity* eneity);
		void UnregisterEnetity(Entity* enetity);

		int GetNextId()
		{
			XASSERT(mNextId<UINT32_MAX,"Run out of ids!");
			return mNextId++;
		}

	private:
		Entities mEntities;
		int mNextId = 0;
	};
}