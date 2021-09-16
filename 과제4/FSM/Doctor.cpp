// ***********************************************
// **            인공지능 과제4. FSM				**
// **            2016180007김명규               **
// ***********************************************

#include "Doctor.h"

#include "DoctorStates.h"

Doctor::Doctor(int id)
	: BaseEntity(id)
{
	SetLocation(eLocation::Hospital);
	mStateMachine = new StateMachine<Doctor>(this);
	mStateMachine->SetCurrentState(WritePaper::Instance());
	mStateMachine->SetGlobalState(DoctorGlobalState::Instance());
}

Doctor::~Doctor()
{
	if (mStateMachine)
	{
		delete mStateMachine;
	}
}

void Doctor::Update()
{
	mStateMachine->Update();
}

bool Doctor::IsMessageHandled(const Telegram& telegram)
{
	return mStateMachine->IsMessageHandled(telegram);
}

bool Doctor::IsBusy() const
{
	return mStateMachine->IsInState(*TreatPatient::Instance());
}
