#include <iostream>

#include "Log.h"
#include "Random.h"
#include "CrudeTimer.h"
#include "EntityManager.h"
#include "MessageDispatcher.h"

int main()
{
	Log::Init();
	Random::Init();

	EntityMgr->CreateEntity(eEntityID::MinerBob);
	EntityMgr->CreateEntity(eEntityID::HousewifeElsa);
	EntityMgr->CreateEntity(eEntityID::DoctorSmith);
	EntityMgr->CreateEntity(eEntityID::TellerJane);

	for (int i = 0; i < 20; i++)
	{
		std::cout << "------Tick : " << i + 1 << "------" << std::endl;
		Timer->Update();
		EntityMgr->Update();
		Dispatcher->Update();

		Sleep(800);
	}

	return 0;
}