// ***********************************************
// **            인공지능 과제4. FSM				**
// **            2016180007김명규               **
// ***********************************************

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
	EntityMgr->CreateEntity(eEntityID::BarkeeperJohn);

	for (int i = 0; i < 30; i++)
	{
		std::cout << "\n------Tick : " << i + 1 << "------" << std::endl;
		Timer->Update();
		EntityMgr->Update();
		Dispatcher->Update();

		Sleep(800);
	}

	std::cout << "\n***********************************************" << std::endl;
	std::cout << "****************2016180007 김명규**************" << std::endl;
	std::cout << "***********************************************" << std::endl;

	return 0;
}