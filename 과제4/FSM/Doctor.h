#pragma once

#include <deque>

#include "BaseEntity.h"
#include "StateMachine.h"

class Doctor : public BaseEntity
{
public:
	Doctor(int id);
	virtual ~Doctor();

	virtual void Update() override;
	virtual bool IsMessageHandled(const Telegram& telegram) override;

	bool IsBusy() const;

	StateMachine<Doctor>* GetFSM() const { return mStateMachine; }


private:
	StateMachine<Doctor>* mStateMachine;
};

