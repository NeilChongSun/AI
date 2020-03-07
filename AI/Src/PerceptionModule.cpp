#include"Precompiled.h"
#include"PerceptionModule.h"

using namespace AI;

perceptionModule::perceptionModule(Agent& agent, ImportanceCalculator importanceCalculator)
	: mAgent(agent), mImportanceCalculator(importanceCalculator) {}

void perceptionModule::Update(float deltaTime)
{
	//Update sensors and refresh/add memory records
	for (auto&[name, Sensor] : mSensors)
		Sensor->Update(mAgent, mMemory, deltaTime);
	//calculate importance on new records
	for (auto iter = mMemory.begin(); iter != mMemory.end();)
	{
		if (iter->lastRecordedTime + mMemorySpan < X::GetTime())
			iter = mMemory.erase(iter);
		else
			++iter;	
	}
	//sort record by importance
	mMemory.sort([](const MemoryRecord& a, const MemoryRecord& b)
	{
		return a.importance > b.importance;
	});
}

