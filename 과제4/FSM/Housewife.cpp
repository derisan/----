#include "Housewife.h"

#include "HousewifeStates.h"


Housewife::Housewife(int id)
	: BaseEntity(id)
	, bIsCooking(false)
{
	SetLocation(eLocation::Shack);
	mStateMachine = new StateMachine<Housewife>(this);
	mStateMachine->SetCurrentState(DoHouseWork::Instance());
	mStateMachine->SetGlobalState(WifeGlobalState::Instance());
}

Housewife::~Housewife()
{
	if (mStateMachine)
	{
		delete mStateMachine;
	}
}

void Housewife::Update()
{
	mStateMachine->Update();
}

bool Housewife::IsMessageHandled(const Telegram& telegram)
{
	return mStateMachine->IsMessageHandled(telegram);
}
