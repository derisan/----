#include <cassert>

#include "Miner.h"
#include "States.h"

Miner::Miner(int id)
	: BaseEntity(id)
	, mLocation(eLocation::Shack)
	, mGoldCarried(0)
	, mMoneyInBank(0)
	, mThirst(0)
	, mFatigue(0)
{
	mCurrentState = EnterMineAndDigForNugget::Instance();
}

Miner::~Miner()
{

}

void Miner::Update()
{
	mThirst++;

	if (mCurrentState)
	{
		mCurrentState->Execute(this);
	}
}

void Miner::ChangeState(State* newState)
{
	assert(mCurrentState && newState);

	mCurrentState->Exit(this);
	mCurrentState = newState;
	mCurrentState->Enter(this);
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
