// ***********************************************
// **            인공지능 과제4. FSM				**
// **            2016180007김명규               **
// ***********************************************

#pragma once

#include "BaseEntity.h"
#include "StateMachine.h"

class Teller : public BaseEntity
{
public:
	Teller(int id);
	virtual ~Teller();

	virtual void Update() override;
	virtual bool IsMessageHandled(const Telegram& telegram) override;

	bool IsBusy() const { return bIsDoingBankingWork; }
	void SetBusy(bool val) { bIsDoingBankingWork = val; }

	bool IsHungry() const { return mHunger > kHungerLevel; }
	void SetHunger(int val) { mHunger = val; }

	StateMachine<Teller>* GetFSM() const { return mStateMachine; }

private:
	const int kHungerLevel = 5;

	StateMachine<Teller>* mStateMachine;

	bool bIsDoingBankingWork;
	int mHunger;
};

