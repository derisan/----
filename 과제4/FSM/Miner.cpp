#include <cassert>

#include "Miner.h"
#include "MinerStates.h"

Miner::Miner(int id)
	: BaseEntity(id)
	, mLocation(eLocation::Shack)
	, mGoldCarried(0)
	, mMoneyInBank(0)
	, mThirst(0)
	, mFatigue(0)
{
	mStateMachine = new StateMachine<Miner>(this);
	mStateMachine->SetCurrentState(EnterMineAndDigForNugget::Instance());
}

Miner::~Miner()
{
	if (mStateMachine)
	{
		delete mStateMachine;
	}
}

void Miner::Update()
{
	mThirst++;

	mStateMachine->Update();
}

void Miner::AddToGoldCarried(int val)
{
	mGoldCarried += val;

	if (mGoldCarried < 0)
	{
		mGoldCarried = 0;
	}
}

void Miner::AddToMoneyInBank(int val)
{
	mMoneyInBank += val;

	if (mMoneyInBank < 0)
	{
		mMoneyInBank = 0;
	}
}
