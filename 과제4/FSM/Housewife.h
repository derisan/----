#pragma once

#include "BaseEntity.h"
#include "StateMachine.h"

class Housewife : public BaseEntity
{
public:
	Housewife(int id);
	virtual ~Housewife();

	virtual void Update() override;

	StateMachine<Housewife>* GetFSM() const { return mStateMachine; }

private:
	StateMachine<Housewife>* mStateMachine;
};