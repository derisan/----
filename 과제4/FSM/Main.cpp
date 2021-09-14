#include "Log.h"
#include "Random.h"
#include "Miner.h"
#include "Housewife.h"

int main()
{
	Log::Init();
	Random::Init();

	Miner miner(eEntityID::MinerBob);
	Housewife wife(eEntityID::HousewifeElsa);

	for (int i = 0; i < 20; i++)
	{
		miner.Update();
		wife.Update();

		Sleep(800);
	}

	return 0;
}