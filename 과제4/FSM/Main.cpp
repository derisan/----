#include "Log.h"
#include "Miner.h"

int main()
{
	Log::Init();

	Miner miner(eEntityID::MinerBob);

	for (int i = 0; i < 20; i++)
	{
		miner.Update();

		Sleep(800);
	}

	return 0;
}