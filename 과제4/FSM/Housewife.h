// ***********************************************
// **            인공지능 과제4. FSM				**
// **            2016180007김명규               **
// ***********************************************

#pragma once

#include "BaseEntity.h"
#include "StateMachine.h"

class Housewife : public BaseEntity
{
public:
	Housewife(int id);
	virtual ~Housewife();

	virtual void Update() override;
	virtual bool IsMessageHandled(const Telegram& telegram) override;

	StateMachine<Housewife>* GetFSM() const { return mStateMachine; }

	bool IsCooking() const { return bIsCooking; }
	void SetCooking(bool val) { bIsCooking = val; }

private:
	StateMachine<Housewife>* mStateMachine;

	bool bIsCooking;
};