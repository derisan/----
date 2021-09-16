#include "Teller.h"

#include "TellerStates.h"

Teller::Teller(int id)
	: BaseEntity(id),
	bIsDoingBankingWork(false)
{
	SetLocation(eLocation::Bank);
	mStateMachine = new StateMachine<Teller>(this);
	mStateMachine->SetGlobalState(TellerGlobalState::Instance());
	mStateMachine->SetCurrentState(OrganizeDocuments::Instance());
}

Teller::~Teller()
{
	if (mStateMachine)
	{
		delete mStateMachine;
	}
}

void Teller::Update()
{
	mHunger++;

	mStateMachine->Update();
}

bool Teller::IsMessageHandled(const Telegram& telegram)
{
	return mStateMachine->IsMessageHandled(telegram);
}
