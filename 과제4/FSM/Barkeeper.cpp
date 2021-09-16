#include "Barkeeper.h"

#include "BarkeeperStates.h"

Barkeeper::Barkeeper(int id)
	: BaseEntity(id)
	, mLiquorStock(3)
	, mGold(0)
{
	SetLocation(eLocation::Saloon);
	mStateMachine = new StateMachine<Barkeeper>(this);
	mStateMachine->SetGlobalState(BarkeeperGlobalState::Instance());
	mStateMachine->SetCurrentState(CleanUpShop::Instance());
}

Barkeeper::~Barkeeper()
{
	if (mStateMachine)
	{
		delete mStateMachine;
	}
}

void Barkeeper::Update()
{
	mStateMachine->Update();
}

bool Barkeeper::IsMessageHandled(const Telegram& telegram)
{
	return mStateMachine->IsMessageHandled(telegram);
}
