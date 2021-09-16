// ***********************************************
// **            인공지능 과제4. FSM				**
// **            2016180007김명규               **
// ***********************************************

#include <cassert>

#include "Miner.h"
#include "MinerStates.h"

Miner::Miner(int id)
	: BaseEntity(id)
	, mGoldCarried(0)
	, mMoneyInBank(0)
	, mThirst(0)
	, mFatigue(0)
{
	SetLocation(eLocation::Shack);
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

bool Miner::IsMessageHandled(const Telegram& telegram)
{
	return mStateMachine->IsMessageHandled(telegram);
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
